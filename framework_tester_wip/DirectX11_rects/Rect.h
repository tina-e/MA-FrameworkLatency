#pragma once

#include <d3d11.h>
#include "Renderer.h"

//struct Vertex {
//	float x, y;
//	float r, g, b;
//};
//
//extern Vertex vertices[6000];

class Rect {
public:
	Rect(Renderer& renderer);
	~Rect();
	void draw(Renderer& renderer);
	void createMesh(Renderer& renderer);
	void createShaders(Renderer& renderer);
	void createRenderStates(Renderer& renderer);
	static void createRandomVertices();	

private:
	ID3D11Buffer* m_vertexBuffer = nullptr;
	ID3D11VertexShader* m_vertexShader = nullptr;
	ID3D11PixelShader* m_pixelShader = nullptr;
	ID3D11InputLayout* m_inputLayout = nullptr;
	ID3D11RasterizerState* m_rasterizerState = nullptr;
	ID3D11DepthStencilState* m_depthState = nullptr;
	ID3D11BlendState* m_blendState = nullptr;
};
