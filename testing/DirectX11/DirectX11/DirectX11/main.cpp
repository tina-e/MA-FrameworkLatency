#include <Windows.h>
#include <winerror.h>
#include <dxgi1_2.h>
#include <d3d11.h>
#include <iostream>
#include <vector>

using namespace std;

IDXGIFactory1* pFactory;
IDXGIAdapter1* pAdapter;
IDXGIOutput* pOutput;
ID3D11Texture2D* pBackBuffer;
ID3D11Device* pDevice;
ID3D11DeviceContext* pContext;
IDXGISwapChain* pSwapChain;
IDXGIOutput1* pOutput1;
ID3D11Texture2D* pStagingTexture;
IDXGIOutputDuplication* pDeskDupl;

void InitDXGI() {
	// init DXGI
	CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&pFactory);
	pFactory->EnumAdapters1(0, &pAdapter);
	pAdapter->EnumOutputs(0, &pOutput);
}

void CreateDevice() {
	//DXGI_SWAP_CHAIN_DESC swapChainDesc;
	//ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	//swapChainDesc.BufferCount = 1;
	//swapChainDesc.BufferDesc.Width = 1920;
	//swapChainDesc.BufferDesc.Height = 1080; // TODO: anpassen!
	//swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	//swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	//swapChainDesc.OutputWindow = nullptr;
	//swapChainDesc.SampleDesc.Count = 1;
	//swapChainDesc.SampleDesc.Quality = 0;
	//swapChainDesc.Windowed = TRUE; // for sure?

	D3D_FEATURE_LEVEL featureLevel;
	HRESULT hr = D3D11CreateDevice(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &pDevice, &featureLevel, &pContext);
	if (FAILED(hr)) {
		cout << "err" << endl;
	}
	/*HRESULT hr = D3D11CreateDeviceAndSwapChain(pAdapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &swapChainDesc, &pSwapChain, &pDevice, NULL, &pContext);
	if (FAILED(hr)) {
		cout << "err" << endl;
	}*/
	//pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
}

void PerformDuplication() {
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = 1920;
	desc.Height = 1080;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_STAGING;
	desc.BindFlags = 0;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
	desc.MiscFlags = 0;
	pDevice->CreateTexture2D(&desc, NULL, &pStagingTexture);

	// Capture screen
	pOutput->QueryInterface(__uuidof(IDXGIOutput1), (void**)&pOutput1);
	
	pOutput1->DuplicateOutput(pDevice, &pDeskDupl);
}

void CleanUp() {
	pStagingTexture->Release();
	pDeskDupl->Release();
	pOutput->Release();
	pOutput1->Release();
	pAdapter->Release();
	pFactory->Release();
	pSwapChain->Release();
	pContext->Release();
	pDevice->Release();
}

void doStuff() {
	InitDXGI();
	CreateDevice();
	PerformDuplication();

	// read pixel data
	D3D11_MAPPED_SUBRESOURCE resource;
	pContext->CopyResource(pStagingTexture, pBackBuffer);
	pContext->Map(pStagingTexture, 0, D3D11_MAP_READ, 0, &resource);

	std::vector<BYTE> pixelData(4);
	memcpy(&pixelData, resource.pData, sizeof(BYTE) * 4 * 200);
	cout << resource.pData << endl;

	pContext->Unmap(pStagingTexture, 0);

	
}

int main() {
	doStuff();
	CleanUp();
}






//#include <Windows.h>
//#include <d3d11.h>
//#include <DirectXMath.h>
//#include <dxgi1_2.h>
//#include <iostream>
//
//using namespace std;
//
//ID3D11Device* device = nullptr;
//ID3D11DeviceContext* deviceContext = nullptr;
//IDXGISwapChain* swapChain = nullptr;
//
//ID3D11RenderTargetView* renderTargetView = nullptr;
//ID3D11Texture2D* texture = nullptr;
//
//IDXGIFactory* factory = nullptr;
//
//void DefineTexture(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11Texture2D*& texture, int x, int y);
//DirectX::XMFLOAT4 GetPixelColor(ID3D11Texture2D* texture, int x, int y);
//
////int main() {
////	D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
////
////	Init();
////	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 2, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);
////	
////	DefineTexture(device, deviceContext, backBuffer, 5, 5);
////	GetPixelColor(backBuffer, 0, 0);
////
////	// TODO: add loop and capture click, timestamps, prints
////}
//
//void InitDevice() {
//	
//	CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&factory);
//
//	IDXGIAdapter* adapter = nullptr;
//	factory->EnumAdapters(0, &adapter);
//
//	D3D11CreateDevice(adapter, D3D_DRIVER_TYPE_UNKNOWN, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &device, nullptr, &deviceContext);
//}
//
//void InitSwapChain() {
//	
//	DXGI_SWAP_CHAIN_DESC swapChainDesc;
//	ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
//	swapChainDesc.BufferCount = 1;
//	swapChainDesc.BufferDesc.Width = 1920;
//	swapChainDesc.BufferDesc.Height = 1080; // TODO: anpassen!
//	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	swapChainDesc.OutputWindow = nullptr;
//	swapChainDesc.SampleDesc.Count = 1;
//	swapChainDesc.SampleDesc.Quality = 0;
//	swapChainDesc.Windowed = TRUE; // for sure?
//
//	factory->CreateSwapChain(device, &swapChainDesc, &swapChain);
//	factory->Release();
//}
//
//void InitTexture() {
//	D3D11_TEXTURE2D_DESC textureDesc;
//	ZeroMemory(&textureDesc, sizeof(textureDesc));
//	textureDesc.Width = 1920;
//	textureDesc.Height = 1080;
//	textureDesc.MipLevels = 1;
//	textureDesc.ArraySize = 1;
//	textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	textureDesc.SampleDesc.Count = 1;
//	textureDesc.SampleDesc.Quality = 0;
//	textureDesc.Usage = D3D11_USAGE_STAGING;
//	textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
//
//	device->CreateTexture2D(&textureDesc, nullptr, &texture);
//}
//
//void ReadPixel(int x, int y) {
//	ID3D11Texture2D* backBuffer = nullptr;
//    swapChain->GetBuffer(0, __uuidof(ID3D10Texture2D), reinterpret_cast<void**>(&backBuffer));
//	deviceContext->CopyResource(texture, backBuffer);
//	backBuffer->Release();
//
//	D3D11_MAPPED_SUBRESOURCE mappedResource;
//	deviceContext->Map(texture, 0, D3D11_MAP_READ, 0, &mappedResource);
//
//	int i = y * mappedResource.RowPitch + x * 4;
//	unsigned char* pixel = static_cast<unsigned char*>(mappedResource.pData) + i;
//	unsigned char r = pixel[0];
//	unsigned char g = pixel[1];
//	unsigned char b = pixel[2];
//	unsigned char a = pixel[3];
//
//	deviceContext->Unmap(texture, 0);
//
//	cout << r << endl;
//	cout << g << endl;
//	cout << b << endl;
//}
//
//int main() {
//	InitDevice();
//	
//	InitTexture();
//	InitSwapChain();
//	
//	ReadPixel(100, 100);
//}
//
////void DefineTexture(ID3D11Device* device, ID3D11DeviceContext* context, ID3D11Texture2D*& texture, int x, int y) {
////	IDXGIDevice* dxgiDevice = nullptr;
////	IDXGIAdapter* dxgiAdapter = nullptr;
////	IDXGIOutput* dxgiOutput = nullptr;
////	IDXGIOutput1* dxgiOutput1 = nullptr;
////	IDXGIOutputDuplication* dxgiOutputDuplication = nullptr;
////
////	device->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDevice);
////	dxgiDevice->GetParent(__uuidof(IDXGIAdapter), (void**)&dxgiAdapter);
////	dxgiAdapter->EnumOutputs(0, &dxgiOutput);
////	dxgiOutput->QueryInterface(__uuidof(IDXGIOutput1), (void**)&dxgiOutput1);
////	HRESULT hr = dxgiOutput1->DuplicateOutput(device, &dxgiOutputDuplication);
////
////	DXGI_OUTDUPL_FRAME_INFO frameInfo;
////	IDXGIResource* desktopResource = nullptr;
////
////	dxgiOutputDuplication->AcquireNextFrame(INFINITE, &frameInfo, &desktopResource);
////
////	ID3D11Texture2D* desktopTexture = nullptr;
////	desktopResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&desktopTexture);
////
////	D3D11_TEXTURE2D_DESC desc;
////	desktopTexture->GetDesc(&desc);
////
////	D3D11_TEXTURE2D_DESC capturedDesc = desc;
////	capturedDesc.Width = 1;
////	capturedDesc.Height = 1;
////	capturedDesc.Usage = D3D11_USAGE_STAGING;
////	capturedDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
////	capturedDesc.BindFlags = 0;
////
////	device->CreateTexture2D(&capturedDesc, nullptr, &texture);
////
////	// TODO ?
////	// Copy the specific region of the desktop texture to the captured texture
////	D3D11_BOX sourceRegion;
////	sourceRegion.left = x;
////	sourceRegion.right = x + 1;
////	sourceRegion.top = y;
////	sourceRegion.bottom = y + 1;
////	sourceRegion.front = 0;
////	sourceRegion.back = 1;
////
////	context->CopySubresourceRegion(texture, 0, 0, 0, 0, desktopTexture, 0, &sourceRegion);
////
////
////	// Release resources
////	desktopTexture->Release();
////	desktopResource->Release();
////	dxgiOutputDuplication->ReleaseFrame();
////
////	// Release DXGI interfaces
////	dxgiDevice->Release();
////	dxgiAdapter->Release();
////	dxgiOutput->Release();
////	dxgiOutput1->Release();
////	dxgiOutputDuplication->Release();
////
////}
//
////DirectX::XMFLOAT4 GetPixelColor(ID3D11Texture2D* texture, int x, int y) {
////	D3D11_TEXTURE2D_DESC desc;
////	texture->GetDesc(&desc);
////
////	D3D11_MAPPED_SUBRESOURCE mappedResource;
////	HRESULT result = deviceContext->Map(texture, 0, D3D11_MAP_READ, 0, &mappedResource);
////	if (SUCCEEDED(result)) {
////		UINT8* pixel = reinterpret_cast<UINT8*>(mappedResource.pData) + y * mappedResource.RowPitch + x * 4;
////		DirectX::XMFLOAT4 color;
////		color.x = static_cast<float>(pixel[0]) / 255.0f;
////		color.y = static_cast<float>(pixel[1]) / 255.0f;
////		color.z = static_cast<float>(pixel[2]) / 255.0f;
////		color.w = static_cast<float>(pixel[3]) / 255.0f;
////		deviceContext->Unmap(texture, 0);
////		return color;
////	}
////	return DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);
////}
