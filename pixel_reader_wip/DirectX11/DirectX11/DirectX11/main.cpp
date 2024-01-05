#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <dxgi1_2.h>

ID3D11Device* device = nullptr;
ID3D11DeviceContext* deviceContext = nullptr;
IDXGISwapChain* swapChain = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;
ID3D11Texture2D* backBuffer = nullptr;

void DefineTexture(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11Texture2D*& texture, int x, int y);

int main() {
	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 2, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);
	
	DefineTexture(device, deviceContext, backBuffer, 5, 5);

	// TODO: add loop and capture click, timestamps, prints
}

void DefineTexture(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11Texture2D*& texture, int x, int y) {
	IDXGIDevice* dxgiDevice = nullptr;
	IDXGIAdapter* dxgiAdapter = nullptr;
	IDXGIOutput* dxgiOutput = nullptr;
	IDXGIOutput1* dxgiOutput1 = nullptr;
	IDXGIOutputDuplication* dxgiOutputDuplication = nullptr;

	device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
	dxgiAdapter->EnumOutputs(0, &dxgiOutput);
	dxgiOutput->QueryInterface(__uuidof(IDXGIOutput1), (void**)&dxgiOutput1);
	HRESULT hr = dxgiOutput1->DuplicateOutput(device, &dxgiOutputDuplication);
	// error here maybe because of hybrid gpu -> maybe device problem

	DXGI_OUTDUPL_FRAME_INFO frameInfo;
	IDXGIResource* desktopResource = nullptr;

	dxgiOutputDuplication->AcquireNextFrame(INFINITE, &frameInfo, &desktopResource);

	ID3D11Texture2D* desktopTexture = nullptr;
	desktopResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&desktopTexture);

	D3D11_TEXTURE2D_DESC desc;
	desktopTexture->GetDesc(&desc);

	D3D11_TEXTURE2D_DESC capturedDesc = desc;
	capturedDesc.Width = 1;
	capturedDesc.Height = 1;
	capturedDesc.Usage = D3D11_USAGE_STAGING;
	capturedDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	capturedDesc.BindFlags = 0;

	device->CreateTexture2D(&capturedDesc, nullptr, &texture);

	// TODO ?
	// Copy the specific region of the desktop texture to the captured texture
	D3D11_BOX sourceRegion;
	sourceRegion.left = x;
	sourceRegion.right = x + 1;
	sourceRegion.top = y;
	sourceRegion.bottom = y + 1;
	sourceRegion.front = 0;
	sourceRegion.back = 1;

	context->CopySubresourceRegion(texture, 0, 0, 0, 0, desktopTexture, 0, &sourceRegion);


	// Release resources
	desktopTexture->Release();
	desktopResource->Release();
	dxgiOutputDuplication->ReleaseFrame();

	// Release DXGI interfaces
	dxgiDevice->Release();
	dxgiAdapter->Release();
	dxgiOutput->Release();
	dxgiOutput1->Release();
	dxgiOutputDuplication->Release();

}

DirectX::XMFLOAT4 GetPixel(ID3D11Texture2D* texture, int x, int y) {
	D3D11_TEXTURE2D_DESC desc;
	texture->GetDesc(&desc);

	D3D11_MAPPED_SUBRESOURCE mappedResource;
	HRESULT result = deviceContext->Map(texture, 0, D3D11_MAP_READ, 0, &mappedResource);
	if (SUCCEEDED(result)) {
		UINT8* pixel = reinterpret_cast<UINT8*>(mappedResource.pData) + y * mappedResource.RowPitch + x * 4;
		DirectX::XMFLOAT4 color;
		color.x = static_cast<float>(pixel[0]) / 255.0f;
		color.y = static_cast<float>(pixel[1]) / 255.0f;
		color.z = static_cast<float>(pixel[2]) / 255.0f;
		color.w = static_cast<float>(pixel[3]) / 255.0f;
		deviceContext->Unmap(texture, 0);
		return color;
	}
	return DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
}
