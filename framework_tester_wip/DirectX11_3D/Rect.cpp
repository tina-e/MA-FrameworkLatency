#include "Rect.h"
#include <fstream>
#include <vector>
#include <random>
#include <DirectXMath.h>
#include <iostream>

using namespace DirectX;
using namespace std;

struct Vertex {
	float x, y, z;
	float r, g, b;
};

float full = 100;
Vertex vertices[8] = {
	{-full, full, -full, 1, 1, 1},
	{full, full, -full, 1, 1, 1},
	{-full, -full, -full, 1, 1, 1},
	{full, -full, -full, 1, 1, 1},
	{-full, full, full, 1, 1, 1},
	{full, full, full, 1, 1, 1},
	{-full, -full, full, 1, 1, 1},
	{full, -full, full, 1, 1, 1}
};

WORD cubeIndices[] = {
	0, 1, 2, // Front face
	0, 2, 3,
	4, 5, 6, // Back face
	4, 6, 7,
	0, 1, 5, // Left face
	0, 5, 4,
	2, 3, 7, // Right face
	2, 7, 6,
	1, 2, 6, // Top face
	1, 6, 5,
	0, 3, 7, // Bottom face
	0, 7, 4
};



struct ConstantBuffer {
	XMMATRIX WorldViewProjection;
};

float getRandomBoundedFloat(float min, float max) {
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<float> distribution(min, max);
	return distribution(gen);
}

//Vertex vertices[48] = {};
float rotationAngle = 0.0f;
ConstantBuffer constantBufferData;
bool firstDraw = false;

float rotationX = 0.0f;
float rotationY = 0.0f;
float rotationZ = 0.0f;

float rotationAngleX = 0.00005f; // Example rotation angle around X axis
float rotationAngleY = 0.00005f; // Example rotation angle around Y axis
float rotationAngleZ = 0.00005f;

DirectX::XMMATRIX rotationMatrixX;
DirectX::XMMATRIX rotationMatrixY;
DirectX::XMMATRIX rotationMatrixZ;
DirectX::XMMATRIX rotationMatrix;


//XMMATRIX worldMatrix = XMMatrixIdentity();
//XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat3(&eyePosition), XMLoadFloat3(&focusPosition), XMLoadFloat3(&upDirection));
//XMMATRIX projectionMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(fov), aspectRatio, nearPlane, farPlane);
//XMMATRIX worldViewProjectionMatrix = worldMatrix * viewMatrix * projectionMatrix;


Rect::Rect(Renderer& renderer) {
	//createMesh(renderer);
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
	

	createMesh(renderer);
	auto deviceContext = renderer.getDeviceContext();

	// Set render states
	/*deviceContext->RSSetState(m_rasterizerState);
	deviceContext->OMSetBlendState(m_blendState, NULL, 0xffffffff);
	deviceContext->OMSetDepthStencilState(m_depthState, 1);*/

	// Bind the triangle shaders
	deviceContext->IASetInputLayout(m_inputLayout);
	deviceContext->VSSetShader(m_vertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_pixelShader, nullptr, 0);

	//ConstantBuffer cb;
	//cb.rotationMatrix = rotationMatrix;
	//deviceContext->UpdateSubresource(m_vertexBuffer, 0, NULL, &cb, 0, 0);

	ConstantBuffer cb;
	cb.WorldViewProjection = XMMatrixTranspose(rotationMatrix); // Transpose the matrix for HLSL
	renderer.getDeviceContext()->UpdateSubresource(m_constantBuffer, 0, nullptr, &cb, 0, 0);

	// Bind the vertex buffer
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R16_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*for (int i = 0; i < 48; i++) {
		DirectX::XMVECTOR position = DirectX::XMVectorSet(vertices[i].x, vertices[i].y, vertices[i].z, 1);
		position = DirectX::XMVector3Transform(position, rotationMatrix);
		XMFLOAT3 floatthree;
		DirectX::XMStoreFloat3(&floatthree, position);
		vertices[i].x = floatthree.x;
		vertices[i].y = floatthree.y;
		vertices[i].z = floatthree.z;

	}*/
	deviceContext->DrawIndexed(36, 0, 0);
	/*for (int i = 0; i < 1; ++i) {
		
		deviceContext->Draw(24, i * 24);
	}*/

	//for (int i = 0; i < 6; ++i) {
	//	// Draw the face using 4 vertices
	//	deviceContext->Draw(4, i * 4);
	//}
}

void Rect::createRandomVertices() {

	//Vertex cubeVertices[] = {
	//	{ XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) }, // Vertex 0 (Front, Bottom, Left) - Red
	//	{ XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },  // Vertex 1 (Front, Top, Left) - Green
	//	{ XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },   // Vertex 2 (Front, Top, Right) - Blue
	//	{ XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f) },  // Vertex 3 (Front, Bottom, Right) - Yellow
	//	{ XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f) },  // Vertex 4 (Back, Bottom, Left) - Magenta
	//	{ XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f) },   // Vertex 5 (Back, Top, Left) - Cyan
	//	{ XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f) },    // Vertex 6 (Back, Top, Right) - White
	//	{ XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f) }    // Vertex 7 (Back, Bottom, Right) - Gray
	//};

	//const float sideLength = 1.0f;
	//const float halfLength = sideLength / 2.0f;

	//// Front face vertices
	//vertices[0] = { -halfLength, -halfLength, halfLength, 1.0f, 0.0f, 0.0f }; // Bottom left
	//vertices[1] = { halfLength, -halfLength, halfLength, 0.0f, 1.0f, 0.0f };  // Bottom right
	//vertices[2] = { halfLength, halfLength, halfLength, 0.0f, 0.0f, 1.0f };   // Top right
	//vertices[3] = { -halfLength, halfLength, halfLength, 1.0f, 1.0f, 0.0f };  // Top left

	//// Back face vertices
	//vertices[4] = { -halfLength, -halfLength, -halfLength, 1.0f, 0.0f, 1.0f }; // Bottom left
	//vertices[5] = { halfLength, -halfLength, -halfLength, 0.0f, 1.0f, 1.0f };  // Bottom right
	//vertices[6] = { halfLength, halfLength, -halfLength, 1.0f, 1.0f, 1.0f };   // Top right
	//vertices[7] = { -halfLength, halfLength, -halfLength, 0.0f, 0.0f, 0.0f };  // Top left

	//// Top face vertices
	//vertices[8] = { -halfLength, halfLength, halfLength, 1.0f, 1.0f, 0.0f };  // Front left
	//vertices[9] = { halfLength, halfLength, halfLength, 0.0f, 1.0f, 1.0f };   // Front right
	//vertices[10] = { halfLength, halfLength, -halfLength, 1.0f, 0.0f, 1.0f };  // Back right
	//vertices[11] = { -halfLength, halfLength, -halfLength, 0.0f, 0.0f, 0.0f }; // Back left

	//// Bottom face vertices
	//vertices[12] = { -halfLength, -halfLength, halfLength, 1.0f, 0.0f, 1.0f };  // Front left
	//vertices[13] = { halfLength, -halfLength, halfLength, 0.0f, 0.5f, 1.0f };   // Front right
	//vertices[14] = { halfLength, -halfLength, -halfLength, 1.0f, 0.5f, 0.0f };  // Back right
	//vertices[15] = { -halfLength, -halfLength, -halfLength, 0.0f, 0.0f, 0.5f }; // Back left

	//// Right face vertices
	//vertices[16] = { halfLength, -halfLength, halfLength, 1.0f, 0.0f, 1.0f };  // Front bottom
	//vertices[17] = { halfLength, -halfLength, -halfLength, 0.0f, 0.5f, 1.0f }; // Front top
	//vertices[18] = { halfLength, halfLength, -halfLength, 1.0f, 0.5f, 0.0f };  // Back top
	//vertices[19] = { halfLength, halfLength, halfLength, 0.0f, 0.0f, 0.5f };   // Back bottom

	//// Left face vertices
	//vertices[20] = { -halfLength, -halfLength, halfLength, 1.0f, 0.0f, 0.5f }; // Front bottom
	//vertices[21] = { -halfLength, -halfLength, -halfLength, 0.0f, 0.0f, 0.5f }; // Front top
	//vertices[22] = { -halfLength, halfLength, -halfLength, 1.0f, 0.5f, 0.0f };  // Back top
	//vertices[23] = { -halfLength, halfLength, halfLength, 0.0f, 0.5f, 1.0f };   // Back bottom

	//Vertex vertices[72] = {};
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
	/*float r = getRandomBoundedFloat(0, 1);
	float g = getRandomBoundedFloat(0, 1);
	float b = getRandomBoundedFloat(0, 1);

	for (int i = 0; i < 24; i += 24) {*/

	//	float x = getRandomBoundedFloat(-0.7, 1);
	//	float y = getRandomBoundedFloat(-0.7, 1);
	//	float z = getRandomBoundedFloat(-0.7, 1);

	//	int index = i;

		//vertices[i] = { x, y, z, r, g, b };
		//vertices[i + 1] = { x, y + 0.1f, z, r, g, b };
		//vertices[i + 2] = { x + 0.1f, y + 0.1f, z, r, g, b };
		//vertices[i + 3] = { x + 0.1f, y + 0.1f, z, r, g, b };
		//vertices[i + 4] = { x + 0.1f, y, z, r, g, b };
		//vertices[i + 5] = { x, y, z, r, g, b };

		//// Front face
		//vertices[i + 6] = { x, y, z + 0.1f, r, g, b };
		//vertices[i + 7] = { x, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 8] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 9] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 10] = { x + 0.1f, y, z + 0.1f, r, g, b };
		//vertices[i + 11] = { x, y, z + 0.1f, r, g, b };

		//vertices[i + 12] = { x, y + 0.1f, z, r, g, b };
		//vertices[i + 13] = { x, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 14] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 15] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 16] = { x + 0.1f, y + 0.1f, z, r, g, b };
		//vertices[i + 17] = { x, y + 0.1f, z, r, g, b };

		//vertices[i + 18] = { x, y, z, r, g, b };
		//vertices[i + 19] = { x, y, z + 0.1f, r, g, b };
		//vertices[i + 20] = { x + 0.1f, y, z + 0.1f, r, g, b };
		//vertices[i + 21] = { x + 0.1f, y, z + 0.1f, r, g, b };
		//vertices[i + 22] = { x + 0.1f, y, z, r, g, b };
		//vertices[i + 23] = { x, y, z, r, g, b };

		//vertices[i + 24] = { x, y, z, r, g, b };
		//vertices[i + 25] = { x, y + 0.1f, z, r, g, b };
		//vertices[i + 26] = { x, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 27] = { x, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 28] = { x, y, z + 0.1f, r, g, b };
		//vertices[i + 29] = { x, y, z, r, g, b };

		//vertices[i + 30] = { x + 0.1f, y, z, r, g, b };
		//vertices[i + 31] = { x + 0.1f, y + 0.1f, z, r, g, b };
		//vertices[i + 32] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 33] = { x + 0.1f, y + 0.1f, z + 0.1f, r, g, b };
		//vertices[i + 34] = { x + 0.1f, y, z + 0.1f, r, g, b };
		//vertices[i + 35] = { x + 0.1f, y, z, r, g, b };


		//x = 0.5;
		//y = 0.5;
		//z = 0.5;

		/*float full = 0.5f;
		float half = 0.25f;*/

		//vertices = {
		//	{-full, full, -full, 1, 1,1, 1, 1},
		//	{full, full, -full, 1, 1, 1, 1},
		//	{-full, -full, -full, 1, 1, 1, 1},
		//	{full, -full, -full, 1, 1, 1, 1},
		//	{-full, full, full, 1, 1, 1, 1},
		//	{full, full, full, 1, 1, 1, 1},
		//	{-full, -full, full, 1, 1, 1, 1},
		//	{full, -full, full, 1, 1, 1 ,1}
		//}


	//	r = 1;
	//	g = 0;
	//	b = 0;
	//	// front
	//	vertices[i] = { -full, -full, -full, r, g, b };
	//	vertices[i + 1] = { -full, full, -full, r, g, b };
	//	vertices[i + 2] = { full, full, -full, r, g, b };
	//	vertices[i + 3] = { full, -full, -full, r, g, b };

	//	// back
	//	r = 0.8;
	//	g = 0.8;
	//	b = 0.8;
	//	vertices[i + 4] = { -full, -full, full, 1, 0, 0 };
	//	vertices[i + 5] = { -full, full, full, 0, 1, 0 };
	//	vertices[i + 6] = { full, full, full, 0, 0, 1 };
	//	vertices[i + 7] = { full, -full, full, 1, 1, 1 }; 

	//	//left
	//	r = 0;
	//	g = 0;
	//	b = 1;
	//	vertices[i + 8] = { -full, -full, full, 1, 0, 0 };
	//	vertices[i + 9] = {-full, full, full, 0, 1, 0 };
	//	vertices[i + 10] = {-full, full, -full, 0, 0, 1 };
	//	vertices[i + 11] = {-full, -full, -full, 1, 1, 1 };

	//	//right
	//	r = 0;
	//	g = 1;
	//	b = 0;
	//	vertices[i + 12] = {full, -full, -full, r, g, b };
	//	vertices[i + 13] = {full, full, -full, r, g, b };
	//	vertices[i + 14] = {full, full, full, r, g, b };
	//	vertices[i + 15] = { full, -full, full, r, g, b };

	//	//top
	//	r = 1;
	//	g = 1;
	//	b = 1;
	//	vertices[i + 16] = {-full, full, -full , r, g, b };
	//	vertices[i + 17] = { -full, full, full, r, g, b };
	//	vertices[i + 18] = {full, full, full , r, g, b };
	//	vertices[i + 19] = {full, full, -full , r, g, b };

	//	//bottom
	//	r = 0.2;
	//	g = 0.2;
	//	b = 0.2;
	//	vertices[i + 20] = { -full, -full, -full, r, g, b };
	//	vertices[i + 21] = { -full, -full, full, r, g, b };
	//	vertices[i + 22] = { full, -full, full, r, g, b };
	//	vertices[i + 23] = { full, -full, -full, r, g, b };



	//}

	///*rotationAngleX = 0.1f;
	//rotationAngleY = 0.2f;
	//rotationAngleZ = 0.3f;*/
	//rotationMatrixX = DirectX::XMMatrixRotationX(rotationAngleX);
	//rotationMatrixY = DirectX::XMMatrixRotationY(rotationAngleY);
	//rotationMatrixZ = DirectX::XMMatrixRotationZ(rotationAngleZ);
	//rotationMatrix = rotationMatrixX * rotationMatrixY * rotationMatrixZ;



	//



	/*for (int i = 0; i < 72; i++) {
		float x = vertices[i].x;
		float y = vertices[i].y;
		float z = vertices[i].z;

		float rotatedX = x;
		float rotatedY = y * cos(rotationAngleX) - z * sin(rotationAngleX);
		float rotatedZ = y * sin(rotationAngleX) + z * cos(rotationAngleX);

		x = rotatedX * cos(rotationAngleY) + rotatedZ * sin(rotationAngleY);
		y = rotatedY;
		z = -rotatedX * sin(rotationAngleY) + rotatedZ * cos(rotationAngleY);

		rotatedX = x * cos(rotationAngleZ) - y * sin(rotationAngleZ);
		rotatedY = x * sin(rotationAngleZ) + y * cos(rotationAngleZ);
		rotatedZ = z;

		vertices[i].x = rotatedX;
		vertices[i].y = rotatedY;
		vertices[i].z = rotatedZ;
	}*/

	/*vertices[5994] = { -1, 1, 1, 1, 1 };
	vertices[5995] = { -0.5, 1, 1, 1, 1 };
	vertices[5996] = { -1, 0.5, 1, 1, 1 };
	vertices[5997] = { -1, 0.5, 1, 1, 1 };
	vertices[5998] = { -0.5, 1, 1, 1, 1 };
	vertices[5999] = { -0.5, 0.5, 1, 1, 1 };*/
}

void Rect::createMesh(Renderer& renderer) {
	/*auto vertexBufferDesc = CD3D11_BUFFER_DESC(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
	D3D11_SUBRESOURCE_DATA vertexData = { 0 };
	vertexData.pSysMem = vertices;*/

	D3D11_BUFFER_DESC constantBufferDesc = {};
	constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesc.CPUAccessFlags = 0;
	constantBufferDesc.MiscFlags = 0;
	constantBufferDesc.StructureByteStride = 0;
	renderer.getDevice()->CreateBuffer(&constantBufferDesc, nullptr, &m_constantBuffer);

	D3D11_BUFFER_DESC vertexBufferDesc = {};
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(vertices);
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	D3D11_SUBRESOURCE_DATA vertexData = { vertices, 0, 0 };
	renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);

	// hier neu
	D3D11_BUFFER_DESC indexBufferDesc = {};
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(cubeIndices);
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	D3D11_SUBRESOURCE_DATA indexData = { cubeIndices, 0, 0 };
	renderer.getDevice()->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	// ende neu

	//renderer.getDevice()->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
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
