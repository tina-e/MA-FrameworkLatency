#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iterator>
#include <random>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

using namespace std;


struct Vertex {
	float x, y;
	float r, g, b;
};

//const Vertex verticesTemplate[] =
//{
//	{-0.5, 0.5},
//	{0.5, -0.5},
//	{-0.5, -0.5},
//
//	{-0.5, 0.5},
//	{0.5, 0.5},
//	{0.5, -0.5},
//};
//
//const Vertex verticesTopRect[] =
//{
//	{-1, 1},
//	{-0.75, 0.75},
//	{-1, 0.75},
//
//	{-1, 1}, 
//	{-0.75, 1}, 
//	{-0.75, 0.75}, 
//};

float getRandomBoundedFloat(float min, float max) {
	return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}

const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

const int NUM_RECTS = 999;
const int NUM_VERTICES = NUM_RECTS * 6 + 6;

bool wasPressed = false;
Vertex vertices[NUM_VERTICES];

ID3D11Device* pDevice = nullptr;
IDXGISwapChain* pSwapChain = nullptr;
ID3D11DeviceContext* pContext = nullptr;
ID3D11RenderTargetView* pTarget = nullptr;


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

	pSwapChain->SetFullscreenState(TRUE, nullptr);

	ID3D11Resource* pBackBuffer = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));
	pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &pTarget);
	pBackBuffer->Release();
}

void SetupRenderer()
{
	ID3DBlob* pBlob;
	ID3D11PixelShader* pPixelShader;
	D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
	pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
	pContext->PSSetShader(pPixelShader, 0, 0);
	ID3D11VertexShader* pVertexShader;
	D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
	pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
	pContext->VSSetShader(pVertexShader, 0, 0);

	ID3D11InputLayout* pInputLayout;
	const D3D11_INPUT_ELEMENT_DESC inputElemDesc[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	pDevice->CreateInputLayout(inputElemDesc, (UINT)std::size(inputElemDesc), pBlob->GetBufferPointer(), pBlob->GetBufferSize(), &pInputLayout);
	pContext->IASetInputLayout(pInputLayout);

	pContext->OMSetRenderTargets(1, &pTarget, nullptr);
	pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	viewport.Width = WIDTH;
	viewport.Height = HEIGHT;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	pContext->RSSetViewports(1, &viewport);
}

void CreateRects() {
	for (int i = 0; i < (NUM_RECTS * 6); i += 6) {
		float x = getRandomBoundedFloat(-0.7, 1);
		float y = getRandomBoundedFloat(-0.7, 1);
		float r = (float)rand() / RAND_MAX;
		float g = (float)rand() / RAND_MAX;
		float b = (float)rand() / RAND_MAX;

		vertices[i] = {x, x, r, g, b};
		vertices[i + 1] = {x, y, r, g, b};
		vertices[i + 2] = {y, x, r, g, b};
		vertices[i + 3] = {y, x, r, g, b};
		vertices[i + 4] = {x, y, r, g, b};
		vertices[i + 5] = {y, y, r, g, b};
	}
	vertices[NUM_VERTICES-6] = { -1, 1, 1, 1, 1 };
	vertices[NUM_VERTICES-5] = { -0.75, 0.75, 1, 1, 1 };
	vertices[NUM_VERTICES-4] = { -1, 0.75, 1, 1, 1 };
	vertices[NUM_VERTICES-3] = { -1, 1, 1, 1, 1 };
	vertices[NUM_VERTICES-2] = { -0.75, 1, 1, 1, 1 };
	vertices[NUM_VERTICES-1] = { -0.75, 0.75, 1, 1, 1 };

	ID3D11Buffer* pVertexBuffer;
	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = vertices;

	pDevice->CreateBuffer(&vertexBufferDesc, &subresourceData, &pVertexBuffer);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &pVertexBuffer, &stride, &offset);
}

void ClearBuffer(float red, float green, float blue)
{
	const float color[] = { red, green, blue, 1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
}

void DrawRect()
{
	pContext->Draw((NUM_VERTICES), 0);
}

void EndFrame()
{
	pSwapChain->Present(0, 0); // 1,0 for vsync on
}

void Cleanup()
{
	pDevice->Release();
	pSwapChain->Release();
	pContext->Release();
	pTarget->Release();
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_LBUTTONDOWN:
			wasPressed = true;
			CreateRects();
			break;
		case WM_LBUTTONUP:
			wasPressed = false;
			ClearBuffer(0, 0, 0);
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
	SetupRenderer();
	ShowWindow(hWnd, SW_SHOWMAXIMIZED);

	MSG msg;
	BOOL gResult;
	while (gResult = (GetMessage(&msg, nullptr, 0, 0)) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		if (wasPressed) DrawRect();
		EndFrame();
	}

	if (gResult == -1) return -1;
	else return msg.wParam;

	Cleanup();
	return 0;
}