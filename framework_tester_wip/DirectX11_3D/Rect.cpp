#include "Rect.h"
#include <fstream>
#include <vector>
#include <random>
#include <iostream>
using namespace std;

struct Vertex {
	float x, y, z;
	float r, g, b;
};

float getRandomBoundedFloat(float min, float max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> distribution(min, max);
	return distribution(gen);
}

Vertex vertices[72] = {};

Rect::Rect(Renderer& renderer) {
	createMesh(renderer);
	createShaders(renderer);
	//createRenderStates(renderer);
}

Rect::~Rect() {
	m_vertexBuffer->Release();
	m_vertexShader->Release();
	m_pixelShader->Release();
	m_inputLayout->Release();
	/*m_rasterizerState->Release();
	m_depthState->Release();
	m_blendState->Release();*/
}

void Rect::draw(Renderer& renderer) {
	//createMesh(renderer);
	auto deviceContext = renderer.getDeviceContext();

	// Set render states
	/*deviceContext->RSSetState(m_rasterizerState);
	deviceContext->OMSetBlendState(m_blendState, NULL, 0xffffffff);
	deviceContext->OMSetDepthStencilState(m_depthState, 1);*/

	// Bind the triangle shaders
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	// Bind the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	// Draw
	for (int i = 0; i < 2; i++) {
		std::cout << i << std::endl;
		deviceContext->Draw(36, i * 36);
	}
}

void Rect::createRandomVertices() {
	Vertex vertices[72] = {};
	/*for (int i = 0; i < 5994; i += 6) {
		float x = getRandomBoundedFloat(-0.7, 1);
		float y = getRandomBoundedFloat(-0.7, 1);
		float r = getRandomBoundedFloat(0, 1);
		float g = getRandomBoundedFloat(0, 1);
		float b = getRandomBoundedFloat(0, 1);

		vertices[i] = { x, x, r, g, b };
		vertices[i + 1] = { x, y, r, g, b };
		vertices[i + 2] = { y, x, r, g, b };
		vertices[i + 3] = { y, x, r, g, b };
		vertices[i + 4] = { x, y, r, g, b };
		vertices[i + 5] = { y, y, r, g, b };
	}*/
	for (int i = 0; i < 72; i += 36) {
		float x = getRandomBoundedFloat(-0.7, 1);
		float y = getRandomBoundedFloat(-0.7, 1);
		float z = getRandomBoundedFloat(-0.7, 1);
		float r = getRandomBoundedFloat(0, 1);
		float g = getRandomBoundedFloat(0, 1);
		float b = getRandomBoundedFloat(0, 1);

		// Front face
		vertices[i] = { x, y, z, r, g, b };
		vertices[i + 1] = { x, y + 0.1f, z, r, g, b };
		vertices[i + 2] = { x + 0.1f, y + 0.1f, z, r, g, b };
		vertices[i + 3] = { x + 0.1f, y + 0.1f, z, r, g, b };
		vertices[i + 4] = { x + 0.1f, y, z, r, g, b };
		vertices[i + 5] = { x, y, z, r, g, b };

		// Back face
		vertices[i + 6] = { x, y, z + 0.1f, r, g, b };
		vertices[i + 7] = { x, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 8] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 9] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 10] = { x + 0.1f, y, z + 0.1f, r, g, b };
		vertices[i + 11] = { x, y, z + 0.1f, r, g, b };

		// Top face
		vertices[i + 12] = { x, y + 0.1f, z, r, g, b };
		vertices[i + 13] = { x, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 14] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 15] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 16] = { x + 0.1f, y + 0.1f, z, r, g, b };
		vertices[i + 17] = { x, y + 0.1f, z, r, g, b };

		// Bottom face
		vertices[i + 18] = { x, y, z, r, g, b };
		vertices[i + 19] = { x, y, z + 0.1f, r, g, b };
		vertices[i + 20] = { x + 0.1f, y, z + 0.1f, r, g, b };
		vertices[i + 21] = { x + 0.1f, y, z + 0.1f, r, g, b };
		vertices[i + 22] = { x + 0.1f, y, z, r, g, b };
		vertices[i + 23] = { x, y, z, r, g, b };

		// Left face
		vertices[i + 24] = { x, y, z, r, g, b };
		vertices[i + 25] = { x, y + 0.1f, z, r, g, b };
		vertices[i + 26] = { x, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 27] = { x, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 28] = { x, y, z + 0.1f, r, g, b };
		vertices[i + 29] = { x, y, z, r, g, b };

		// Right face
		vertices[i + 30] = { x + 0.1f, y, z, r, g, b };
		vertices[i + 31] = { x + 0.1f, y + 0.1f, z, r, g, b };
		vertices[i + 32] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 33] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		vertices[i + 34] = { x + 0.1f, y, z + 0.1f, r, g, b };
		vertices[i + 35] = { x + 0.1f, y, z, r, g, b };
	}

	/*vertices[5994] = { -1, 1, 1, 1, 1 };
	vertices[5995] = { -0.5, 1, 1, 1, 1 };
	vertices[5996] = { -1, 0.5, 1, 1, 1 };
	vertices[5997] = { -1, 0.5, 1, 1, 1 };
	vertices[5998] = { -0.5, 1, 1, 1, 1 };
	vertices[5999] = { -0.5, 0.5, 1, 1, 1 };*/
}

void Rect::createMesh(Renderer& renderer) {
	auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;

	renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
}

void Rect::createShaders(Renderer& renderer) {
	// Create shaders
	ifstream vsFile("rectVertexShader.cso", ios::binary);
	vector<char> vsData = { istreambuf_iterator<char>(vsFile), istreambuf_iterator<char>() };

	ifstream psFile("rectPixelShader.cso", ios::binary);
	vector<char> psData = { istreambuf_iterator<char>(psFile), istreambuf_iterator<char>() };

	renderer.getDevice()->CreateVertexShader(vsData.data(), vsData.size(), nullptr, &m_vertexShader);
	renderer.getDevice()->CreatePixelShader(psData.data(), psData.size(), nullptr, &m_pixelShader);

	// Create input layout
	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	renderer.getDevice()->CreateInputLayout(layout, 2, vsData.data(), vsData.size(), &m_inputLayout);
}

//void Rect::createRenderStates(Renderer& renderer) {
//	// Rasterizer state
//	auto rasterizerDesc = CD3D11_RASTERIZER_DESC(
//		D3D11_FILL_SOLID,
//		D3D11_CULL_NONE,
//		false,
//		0, 0, 0, 0,
//		false, false, false);
//	renderer.getDevice()->CreateRasterizerState(&rasterizerDesc, &m_rasterizerState);
//
//	// Blend state
//	auto blendDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
//	renderer.getDevice()->CreateBlendState(&blendDesc, &m_blendState);
//
//	// Depth state
//	auto depthDesc = CD3D11_DEPTH_STENCIL_DESC(
//		FALSE, D3D11_DEPTH_WRITE_MASK_ZERO, D3D11_COMPARISON_LESS, 
//		FALSE, D3D11_DEFAULT_STENCIL_READ_MASK, D3D11_DEFAULT_STENCIL_WRITE_MASK, 
//		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS, 
//		D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_STENCIL_OP_KEEP, D3D11_COMPARISON_ALWAYS);
//	renderer.getDevice()->CreateDepthStencilState(&depthDesc, &m_depthState);
//}
