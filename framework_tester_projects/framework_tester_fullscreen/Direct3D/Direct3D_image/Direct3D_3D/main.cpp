//#include <Windows.h>
//#include <d3d11.h>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//#pragma comment(lib, "d3d11.lib")
//
//const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
//const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
////const int WIDTH = 500;
////const int HEIGHT = 500;
//bool wasPressed = false;
//
//ID3D11Device* pDevice = nullptr;
//IDXGISwapChain* pSwapChain = nullptr;
//ID3D11DeviceContext* pContext = nullptr;
//ID3D11RenderTargetView* pTarget = nullptr;
//ID3D11ShaderResourceView* pTextureView = nullptr;
//
//
//void LoadImage() {
//	int texWidth, texHeight, texChannels;
//	unsigned char* pData = stbi_load("noise.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
//	if (pData) {
//		D3D11_TEXTURE2D_DESC descTex = {};
//		descTex.Width = texWidth;
//		descTex.Height = texHeight;
//		descTex.MipLevels = 1;
//		descTex.ArraySize = 1;
//		descTex.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		descTex.SampleDesc.Count = 1;
//		descTex.SampleDesc.Quality = 0;
//		descTex.Usage = D3D11_USAGE_DEFAULT;
//		descTex.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//		descTex.CPUAccessFlags = 0;
//		descTex.MiscFlags = 0;
//
//		ID3D11Texture2D* pTexture = nullptr;
//		D3D11_SUBRESOURCE_DATA initialData = {};
//		initialData.pSysMem = pData;
//		initialData.SysMemPitch = texWidth * 4; // 4 bytes per pixel (RGBA)
//
//		pDevice->CreateTexture2D(&descTex, &initialData, &pTexture);
//
//		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
//		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//		srvDesc.Texture2D.MostDetailedMip = 0;
//		srvDesc.Texture2D.MipLevels = 1;
//
//		pDevice->CreateShaderResourceView(pTexture, &srvDesc, &pTextureView);
//
//		pTexture->Release();
//		stbi_image_free(pData);
//	}
//}
//
//void CreateGraphics(HWND hWnd) {
//	DXGI_SWAP_CHAIN_DESC sd = {};
//	sd.BufferDesc.Width = 0;
//	sd.BufferDesc.Height = 0;
//	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//	sd.BufferDesc.RefreshRate.Numerator = 0;
//	sd.BufferDesc.RefreshRate.Denominator = 0;
//	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
//	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
//	sd.SampleDesc.Count = 1;
//	sd.SampleDesc.Quality = 0;
//	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
//	sd.BufferCount = 1;
//	sd.OutputWindow = hWnd;
//	sd.Windowed = FALSE;
//	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
//	sd.Flags = 0;
//
//
//	D3D11CreateDeviceAndSwapChain(
//		nullptr,
//		D3D_DRIVER_TYPE_HARDWARE,
//		nullptr,
//		0,
//		nullptr,
//		0,
//		D3D11_SDK_VERSION,
//		&sd,
//		&pSwapChain,
//		&pDevice,
//		nullptr,
//		&pContext
//	);
//
//	//pSwapChain->SetFullscreenState(TRUE, nullptr);
//
//	ID3D11Resource* pBackBuffer = nullptr;
//	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
//	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
//	pBackBuffer->Release();
//}
//
//void DrawImage() {
//	pContext->PSSetShaderResources(0, 1, &pTextureView);
//	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//	pContext->Draw(4, 0);
//}
//
//void EndFrame()
//{
//	pSwapChain->Present(0, 0);
//}
//
//void ClearBuffer(float red, float green, float blue)
//{
//	const float color[] = { red, green, blue, 1.0f };
//	pContext->ClearRenderTargetView(pTarget, color);
//}
//
//void Cleanup()
//{
//	pDevice->Release();
//	pSwapChain->Release();
//	pContext->Release();
//	pTarget->Release();
//	pTextureView->Release();
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
//{
//	switch (msg)
//	{
//	case WM_LBUTTONDOWN:
//		wasPressed = true;
//		//DrawImage();
//		ClearBuffer(1, 1, 1);
//		break;
//	case WM_LBUTTONUP:
//		wasPressed = false;
//		ClearBuffer(0, 0, 0);
//		break;
//	case WM_CLOSE:
//		PostQuitMessage(0);
//		break;
//	}
//
//	return DefWindowProc(hWnd, msg, wParam, lParam);
//}
//
//
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	const auto pClassName = L"framework";
//	WNDCLASSEX wc = { 0 };
//	wc.cbSize = sizeof(wc);
//	wc.style = CS_GLOBALCLASS;
//	wc.lpfnWndProc = WndProc;
//	wc.cbClsExtra = 0;
//	wc.cbWndExtra = 0;
//	wc.hInstance = hInstance;
//	wc.hIcon = nullptr;
//	wc.hCursor = nullptr;
//	//wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
//	wc.lpszMenuName = nullptr;
//	wc.lpszClassName = pClassName;
//	wc.hIconSm = nullptr;
//	RegisterClassEx(&wc);
//
//	HWND hWnd = CreateWindowEx(
//		0, pClassName, L"framework",
//		WS_POPUP | WS_VISIBLE,
//		0, 0, WIDTH, HEIGHT,
//		nullptr, nullptr, hInstance, nullptr
//	);
//
//	CreateGraphics(hWnd);
//	//LoadImage();
//	ShowWindow(hWnd, SW_SHOW);
//
//	MSG msg;
//	BOOL gResult;
//	while (gResult = (GetMessage(&msg, nullptr, 0, 0)) > 0)
//	{
//		TranslateMessage(&msg);
//		DispatchMessage(&msg);
//		EndFrame();
//	}
//
//	/*if (wasPressed) {
//		DrawImage();
//	}
//	else {
//		ClearBuffer(0, 0, 0);
//	}*/
//	
//
//	if (gResult == -1) return -1;
//	else return msg.wParam;
//
//	Cleanup();
//	return 0;
//}

#include <Windows.h>
#include <d3d11.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "d3d11.lib")


const int WIDTH = GetSystemMetrics(SM_CXSCREEN)-100;
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN)-100;
bool wasPressed = false;

ID3D11Device* pDevice = nullptr;
IDXGISwapChain* pSwapChain = nullptr;
ID3D11DeviceContext* pContext = nullptr;
ID3D11RenderTargetView* pTarget = nullptr;
ID3D11ShaderResourceView* pTextureView = nullptr;

void LoadImage() {
	int texWidth, texHeight, texChannels;
	unsigned char* pData = stbi_load("noise.png", &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	if (pData) {
		D3D11_TEXTURE2D_DESC descTex = {};
		descTex.Width = texWidth;
		descTex.Height = texHeight;
		descTex.MipLevels = 1;
		descTex.ArraySize = 1;
		descTex.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		descTex.SampleDesc.Count = 1;
		descTex.SampleDesc.Quality = 0;
		descTex.Usage = D3D11_USAGE_DEFAULT;
		descTex.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		descTex.CPUAccessFlags = 0;
		descTex.MiscFlags = 0;

		ID3D11Texture2D* pTexture = nullptr;
		D3D11_SUBRESOURCE_DATA initialData = {};
		initialData.pSysMem = pData;
		initialData.SysMemPitch = texWidth * 4; // 4 bytes per pixel (RGBA)

		pDevice->CreateTexture2D(&descTex, &initialData, &pTexture);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = 0;
		srvDesc.Texture2D.MipLevels = 1;

		pDevice->CreateShaderResourceView(pTexture, &srvDesc, &pTextureView);

		pTexture->Release();
		stbi_image_free(pData);
	}
}

void CreateGraphics(HWND hWnd) {
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = FALSE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;


	D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&pSwapChain,
		&pDevice,
		nullptr,
		&pContext
	);

	pSwapChain->SetFullscreenState(FALSE, nullptr);

	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	pBackBuffer->Release();
}

void DrawImage() {
	pContext->PSSetShaderResources(0, 1, &pTextureView);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	pContext->Draw(4, 0);
}

void EndFrame()
{
	pSwapChain->Present(0, 0);
}

void ClearBuffer(float red, float green, float blue)
{
	const float color[] = { red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
}

void Cleanup()
{
	pDevice->Release();
	pSwapChain->Release();
	pContext->Release();
	pTarget->Release();
	pTextureView->Release();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		wasPressed = true;
		//ClearBuffer(1, 1, 1);
		break;
	case WM_LBUTTONUP:
		wasPressed = false;
		//ClearBuffer(0, 0, 0);
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const auto pClassName = L"framework";
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_GLOBALCLASS;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	//wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIconSm = nullptr;
	RegisterClassEx(&wc);

	HWND hWnd = CreateWindowEx(
		0, pClassName, L"framework",
		WS_POPUP | WS_VISIBLE,
		0, 0, WIDTH, HEIGHT,
		nullptr, nullptr, hInstance, nullptr
	);
	
	CreateGraphics(hWnd);
	LoadImage();
	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	BOOL gResult;
	while (gResult = (GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		if (msg.message == WM_QUIT) {
			break;
		}

		ClearBuffer(0, 0, 0);
		DrawImage();
		/*if (wasPressed) {
			DrawImage();
		}*/
		EndFrame();
	}

	Cleanup();
	if (gResult == -1) return -1;
	else return msg.wParam;

	return 0;
}