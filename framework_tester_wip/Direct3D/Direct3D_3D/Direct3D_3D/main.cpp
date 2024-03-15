#include <Windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <iterator>
#include <random>
#include <DirectXMath.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

using namespace DirectX;
using namespace std;


struct Vertex {
	float x, y, z;
	float r, g, b;
};

struct ConstantBuffer
{
	XMMATRIX transform;
};


//const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
//const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

const int WIDTH = 800;
const int HEIGHT = 800;
const int NUM_RECTS = 166;
const int NUM_VERTICES = 8;
const int X_RECT = -WIDTH / 2 + 300;
const int Y_RECT = -HEIGHT / 2 + 300;

const unsigned short indices[] =
{
	0, 2, 1, 2, 3, 1,
	1, 3, 5, 3, 7, 5,
	2, 6, 3, 3, 6, 7,
	4, 5, 7, 4, 7, 6,
	0, 4, 2, 2, 4, 6,
	0, 1, 4, 1, 5, 4

};

Vertex rectVertices[4] = {
	{ -WIDTH / 2, HEIGHT / 2, 1, 1, 1, 1 },
	{ X_RECT, HEIGHT / 2, 1, 1, 1, 1 },
	{ X_RECT, -Y_RECT, 1, 1, 1, 1 },
	{ -WIDTH / 2, -Y_RECT, 1, 1, 1, 1 }
};

unsigned short rectIndices[6] = {
	0, 1, 2, 0, 3, 2
};

Vertex vertices[8] = {};

float reds[NUM_RECTS];
float greens[NUM_RECTS];
float blues[NUM_RECTS];

float positionX[NUM_RECTS];
float positionY[NUM_RECTS];
float positionZ[NUM_RECTS];

float rotationX[NUM_RECTS];
float rotationY[NUM_RECTS];
float rotationZ[NUM_RECTS];
float rotationXTemp[NUM_RECTS];
float rotationYTemp[NUM_RECTS];
float rotationZTemp[NUM_RECTS];

float scalingX[NUM_RECTS];
float scalingY[NUM_RECTS];
float scalingZ[NUM_RECTS];

ID3D11Device* pDevice = nullptr;
IDXGISwapChain* pSwapChain = nullptr;
ID3D11DeviceContext* pContext = nullptr;
ID3D11RenderTargetView* pTarget = nullptr;

ID3D11Buffer* pRectVertexBuffer;
D3D11_BUFFER_DESC rectVertexBufferDesc = {};
ID3D11Buffer* pRectIndexBuffer;
D3D11_BUFFER_DESC rectIndexBufferDesc = {};
//D3D11_BUFFER_DESC constantBufferRectDesc = {};

ID3D11Buffer* pConstantBuffer = nullptr;
bool wasPressed = false;


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
	sd.Windowed = TRUE; //TODO
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

	pSwapChain->SetFullscreenState(0, NULL);

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
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
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

void SetupRectBuffers()
{
	rectVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	rectVertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	rectVertexBufferDesc.CPUAccessFlags = 0;
	rectVertexBufferDesc.MiscFlags = 0;
	rectVertexBufferDesc.ByteWidth = sizeof(rectVertices);
	rectVertexBufferDesc.StructureByteStride = sizeof(Vertex);

	rectIndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	rectIndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	rectIndexBufferDesc.CPUAccessFlags = 0;
	rectIndexBufferDesc.MiscFlags = 0;
	rectIndexBufferDesc.ByteWidth = sizeof(rectIndices);
	rectIndexBufferDesc.StructureByteStride = sizeof(unsigned short);

	//constantBufferRectDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//constantBufferRectDesc.Usage = D3D11_USAGE_DYNAMIC;
	//constantBufferRectDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	//constantBufferRectDesc.MiscFlags = 0;
	//constantBufferRectDesc.ByteWidth = sizeof(ConstantBuffer);
	//constantBufferRectDesc.StructureByteStride = 0;
}


void SetupRandomCubeValues()
{
	for (int i = 0; i < NUM_RECTS; i++) {
		reds[i] = (float)rand() / RAND_MAX;
		greens[i] = (float)rand() / RAND_MAX;
		blues[i] = (float)rand() / RAND_MAX;

		positionX[i] = (rand() % (WIDTH / 2 - (X_RECT)+1)) + X_RECT;
		positionY[i] = (rand() % (HEIGHT / 2 - (-HEIGHT / 2) + 1)) - HEIGHT / 2;
		positionZ[i] = rand() % 100;

		rotationX[i] = ((float)rand() / RAND_MAX) / 100;
		rotationY[i] = ((float)rand() / RAND_MAX) / 100;
		rotationZ[i] = ((float)rand() / RAND_MAX) / 100;

		scalingX[i] = rand() % 100;
		scalingY[i] = rand() % 100;
		scalingZ[i] = rand() % 100;
	}
}


void CreateVertexBuffer()
{
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
	pVertexBuffer->Release();
}

void CreateIndexBuffers() {
	ID3D11Buffer* pIndexBuffer;
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.ByteWidth = sizeof(indices);
	indexBufferDesc.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = indices;

	pDevice->CreateBuffer(&indexBufferDesc, &indexSubresourceData, &pIndexBuffer);
	pContext->IASetIndexBuffer(pIndexBuffer, DXGI_FORMAT_R16_UINT, 0);	
	pIndexBuffer->Release();
}

void CreateConstantBuffer(int index) {
	rotationXTemp[index] += rotationX[index];
	rotationYTemp[index] += rotationY[index];
	rotationZTemp[index] += rotationZ[index];
	const ConstantBuffer constantBuffer =
	{
		{
			XMMatrixTranspose(
				XMMatrixScaling(scalingX[index], scalingY[index], scalingZ[index]) *
				XMMatrixRotationX(rotationXTemp[index]) *
				XMMatrixRotationY(rotationYTemp[index]) *
				XMMatrixRotationZ(rotationZTemp[index]) *
				XMMatrixTranslation(positionX[index], positionY[index], positionZ[index]) *
				XMMatrixOrthographicLH(WIDTH, HEIGHT, 0.1, 1000)
			)
		}
	};
	
	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.ByteWidth = sizeof(constantBuffer);
	constantBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA constantSubresourceData = {};
	constantSubresourceData.pSysMem = &constantBuffer;

	pDevice->CreateBuffer(&constantBufferDesc, &constantSubresourceData, &pConstantBuffer);
	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);

	pConstantBuffer->Release();
}

void SwitchToRectBuffers()
{
	D3D11_SUBRESOURCE_DATA subresourceData = {};
	subresourceData.pSysMem = rectVertices;
	pDevice->CreateBuffer(&rectVertexBufferDesc, &subresourceData, &pRectVertexBuffer);
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	pContext->IASetVertexBuffers(0, 1, &pRectVertexBuffer, &stride, &offset);

	D3D11_SUBRESOURCE_DATA indexSubresourceData = {};
	indexSubresourceData.pSysMem = rectIndices;
	pDevice->CreateBuffer(&rectIndexBufferDesc, &indexSubresourceData, &pRectIndexBuffer);
	pContext->IASetIndexBuffer(pRectIndexBuffer, DXGI_FORMAT_R16_UINT, 0);

	const ConstantBuffer constantBuffer =
	{
		{
			XMMatrixTranspose(
				XMMatrixOrthographicLH(WIDTH, HEIGHT, 0.1f, 1000.0f) *
				XMMatrixTranslation(-WIDTH / 2.0f, HEIGHT / 2.0f, 0.0f)
			)
		}
	};

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.ByteWidth = sizeof(constantBuffer);
	constantBufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA constantSubresourceData = {};
	constantSubresourceData.pSysMem = &constantBuffer;

	pDevice->CreateBuffer(&constantBufferDesc, &constantSubresourceData, &pConstantBuffer);
	pContext->VSSetConstantBuffers(0, 1, &pConstantBuffer);

	pConstantBuffer->Release();
}

void DefineCubeVertices(int index)
{
	vertices[0] = { -1, -1, -1, reds[index], greens[index], blues[index]};
	vertices[1] = { 1, -1, -1, reds[index], greens[index], blues[index]};
	vertices[2] = { -1, 1, -1, reds[index], greens[index], blues[index]};
	vertices[3] = { 1, 1, -1, reds[index], greens[index], blues[index]};
	vertices[4] = { -1, -1, 1, reds[index], greens[index], blues[index]};
	vertices[5] = { 1, -1, 1, reds[index], greens[index], blues[index]};
	vertices[6] = { -1, 1, 1, reds[index], greens[index], blues[index]};
	vertices[7] = { 1, 1, 1, reds[index], greens[index], blues[index]};
}

void DrawCubes()
{
	for (int i = 0; i < NUM_RECTS; i++) {
		DefineCubeVertices(i);
		CreateVertexBuffer();
		CreateIndexBuffers();
		CreateConstantBuffer(i);
		pContext->DrawIndexed(36, 0, 0);
	}
	SwitchToRectBuffers();
	pContext->DrawIndexed(6, 0, 0);
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
	pConstantBuffer->Release();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_LBUTTONDOWN:
		wasPressed = true;
		SetupRandomCubeValues();
		break;
	case WM_LBUTTONUP:
		wasPressed = false;
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
		1000, 100, WIDTH, HEIGHT,
		nullptr, nullptr, hInstance, nullptr
	);

	CreateGraphics(hWnd);
	SetupRenderer();
	SetupRectBuffers();

	ShowWindow(hWnd, SW_SHOW);

	MSG msg;
	BOOL gResult;
	while (true) {
		if (gResult = (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) > 0) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}

		ClearBuffer(0, 0, 0);
		if (wasPressed) {
			DrawCubes();
		}
		EndFrame();
	}

	Cleanup();
	if (gResult == -1) return -1;
	else return msg.wParam;

	return 0;
}