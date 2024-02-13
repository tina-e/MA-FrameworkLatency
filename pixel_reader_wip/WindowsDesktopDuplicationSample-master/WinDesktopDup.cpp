#include "WinDesktopDup.h"

using namespace std;


WinDesktopDup::~WinDesktopDup() {
	Close();
}

Error WinDesktopDup::Initialize() {
	// Get desktop
	HDESK hDesk = OpenInputDesktop(0, FALSE, GENERIC_ALL);
	if (!hDesk) return "Failed to open desktop";

	// Attach desktop to this thread (presumably for cases where this is not the main/UI thread)
	bool deskAttached = SetThreadDesktop(hDesk) != 0;
	CloseDesktop(hDesk);
	hDesk = nullptr;
	if (!deskAttached) return "Failed to attach recording thread to desktop";

	// Initialize DirectX
	HRESULT hr = S_OK;

	// Driver types supported
	D3D_DRIVER_TYPE driverTypes[] = {
	    D3D_DRIVER_TYPE_HARDWARE,
	    D3D_DRIVER_TYPE_WARP,
	    D3D_DRIVER_TYPE_REFERENCE,
	};
	auto numDriverTypes = ARRAYSIZE(driverTypes);

	// Feature levels supported
	D3D_FEATURE_LEVEL featureLevels[] = {
	    D3D_FEATURE_LEVEL_11_0,
	    D3D_FEATURE_LEVEL_10_1,
	    D3D_FEATURE_LEVEL_10_0,
	    D3D_FEATURE_LEVEL_9_1
	};
	auto numFeatureLevels = ARRAYSIZE(featureLevels);

	D3D_FEATURE_LEVEL featureLevel;

	// Create device
	for (size_t i = 0; i < numDriverTypes; i++) {
		hr = D3D11CreateDevice(nullptr, driverTypes[i], nullptr, 0, featureLevels, (UINT) numFeatureLevels, D3D11_SDK_VERSION, &D3DDevice, &featureLevel, &D3DDeviceContext);
		if (SUCCEEDED(hr)) break;
	}
	if (FAILED(hr)) return "D3D11CreateDevice failed: " + hr;

	// Initialize the Desktop Duplication system
	// Get DXGI device
	IDXGIDevice* dxgiDevice = nullptr;
	hr = D3DDevice->QueryInterface(__uuidof(IDXGIDevice), (void**) &dxgiDevice);
	if (FAILED(hr))
		return ("D3DDevice->QueryInterface failed: " + hr);

	// Get DXGI adapter
	IDXGIAdapter* dxgiAdapter = nullptr;
	hr = dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**) &dxgiAdapter);
	dxgiDevice->Release();
	dxgiDevice = nullptr;
	if (FAILED(hr)) {
		return "dxgiDevice->GetParent failed: " + hr;
	}

	// Get output
	IDXGIOutput* dxgiOutput = nullptr;
	hr = dxgiAdapter->EnumOutputs(OutputNumber, &dxgiOutput);
	dxgiAdapter->Release();
	dxgiAdapter = nullptr;
	if (FAILED(hr)) {
		return "dxgiAdapter->EnumOutputs failed: " + hr;
	}

	dxgiOutput->GetDesc(&OutputDesc);

	// QI for Output 1
	IDXGIOutput1* dxgiOutput1 = nullptr;
	hr = dxgiOutput->QueryInterface(__uuidof(dxgiOutput1), (void**) &dxgiOutput1);
	dxgiOutput->Release();
	dxgiOutput = nullptr;
	if (FAILED(hr))
		return "dxgiOutput->QueryInterface failed: " + hr;

	// Create desktop duplication
	hr = dxgiOutput1->DuplicateOutput(D3DDevice, &DeskDupl);
	dxgiOutput1->Release();
	dxgiOutput1 = nullptr;
	if (FAILED(hr)) {
		if (hr == DXGI_ERROR_NOT_CURRENTLY_AVAILABLE) {
			return "Too many desktop recorders already active";
		}
		return "DuplicateOutput failed: " + hr;
	}

	return "";
}

void WinDesktopDup::Close() {
	if (DeskDupl) DeskDupl->Release();
	if (D3DDeviceContext) D3DDeviceContext->Release();
	if (D3DDevice) D3DDevice->Release();
	DeskDupl = nullptr;
	D3DDeviceContext = nullptr;
	D3DDevice = nullptr;
	HaveFrameLock = false;
}

int WinDesktopDup::GetColorValueAt(int x, int y) {
	
	if (!DeskDupl)
		return -1;

	HRESULT hr;

	// according to the docs, it's best for performance if we hang onto the frame for as long as possible,
	// and only release the previous frame immediately before acquiring the next one. Something about
	// the OS coalescing updates, so that it doesn't have to store them as distinct things.
	if (HaveFrameLock) {
		HaveFrameLock = false;
		hr = DeskDupl->ReleaseFrame();
	}
	hr = DeskDupl->ReleaseFrame();

	IDXGIResource* deskRes = nullptr;
	DXGI_OUTDUPL_FRAME_INFO frameInfo;
	hr = DeskDupl->AcquireNextFrame(INFINITE, &frameInfo, &deskRes);
	if (hr == DXGI_ERROR_WAIT_TIMEOUT) {
		return -1;
	}
	if (FAILED(hr)) {
		// perhaps shutdown and reinitialize
		auto msg = "Acquire failed: " + hr;
		//OutputDebugStringA(msg);
		return -1;
	}


	HaveFrameLock = true;

	ID3D11Texture2D* gpuTex = nullptr;
	hr = deskRes->QueryInterface(__uuidof(ID3D11Texture2D), (void**) &gpuTex);
	deskRes->Release();
	deskRes = nullptr;
	if (FAILED(hr)) {
		return -1;
	}

	bool ok = true;

	D3D11_TEXTURE2D_DESC desc;
	gpuTex->GetDesc(&desc);
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ; // D3D11_CPU_ACCESS_WRITE
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.MiscFlags = 0; // D3D11_RESOURCE_MISC_GDI_COMPATIBLE ?

	ID3D11Texture2D* cpuTex = nullptr;
	hr = D3DDevice->CreateTexture2D(&desc, nullptr, &cpuTex);
	if (SUCCEEDED(hr)) {
		D3DDeviceContext->CopyResource(cpuTex, gpuTex);
	} else {
		ok = false;
	}

	D3D11_MAPPED_SUBRESOURCE sr;
	hr = D3DDeviceContext->Map(cpuTex, 0, D3D11_MAP_READ, 0, &sr);

	BYTE* pixels = static_cast<BYTE*>(sr.pData);
	UINT rowPitch   = sr.RowPitch; 
	UINT byteOffset = (x * rowPitch) + (y * sizeof(UINT)); 
	UINT colorValue = *reinterpret_cast<UINT*>(pixels + byteOffset);
	
	if (colorValue != 0) {
		BYTE red   = (colorValue >> 16) & 0xFF;
		BYTE green = (colorValue >> 8) & 0xFF;
		BYTE blue  = colorValue & 0xFF;
		BYTE alpha = (colorValue >> 24) & 0xFF;

		D3DDeviceContext->Unmap(cpuTex, 0);
		cpuTex->Release();
		gpuTex->Release();

		/*cout << "color: " << red << endl;*/
		return static_cast<int>(red);
	}

	D3DDeviceContext->Unmap(cpuTex, 0);
	cpuTex->Release();
	gpuTex->Release();
	return -1;
}
