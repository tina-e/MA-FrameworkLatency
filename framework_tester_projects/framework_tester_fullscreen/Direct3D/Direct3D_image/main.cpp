// based on https://samulinatri.com/blog/directx-11-textures


#define WIN32_LEAN_AND_MEAN
#define UNICODE
#include <assert.h>
#include <d3d11_1.h>
#include <windows.h>
#include <d3dcompiler.h>
#include <float.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTex.lib")
#pragma comment(lib, "D3DCompiler.lib")

const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
bool wasPressed = false;


LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch (Message) {
        case WM_LBUTTONDOWN:
        {
            wasPressed = true;
        };
        break;
        case WM_LBUTTONUP:
        {
            wasPressed = false;
        };
        break;
        case WM_KEYDOWN: {
            switch (WParam) {
            case 'O': { DestroyWindow(Window); };
            }
        }
        break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        }
        break;
        default: {
            return DefWindowProc(Window, Message, WParam, LParam);
        }
    }

    return 0;
}

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    // Create Window
    WNDCLASS WindowClass = {};

    const wchar_t ClassName[] = L"framework";
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = ClassName;
    WindowClass.hCursor = LoadCursor(0, IDC_ARROW);

    if (!RegisterClass(&WindowClass)) {
        MessageBox(0, L"RegisterClass failed", 0, 0);
        return GetLastError();
    }

    HWND Window = CreateWindowEx(0, ClassName, L"framework", WS_VISIBLE | WS_POPUP , 0, 0, WIDTH, HEIGHT, 0, 0, Instance, 0);
    if (!Window) {
        MessageBox(0, L"CreateWindowEx failed", 0, 0);
        return GetLastError();
    }

    // Viewport
    D3D11_VIEWPORT Viewport = { 0.0f, 0.0f, (float)WIDTH, (float)HEIGHT, 0.0f, 1.0f };

    // Device & Context
    ID3D11Device* BaseDevice;
    ID3D11DeviceContext* BaseContext;

    UINT CreationFlags = 0;
    //#ifdef _DEBUG
        CreationFlags = D3D11_CREATE_DEVICE_DEBUG;
    //#endif

    D3D_FEATURE_LEVEL FeatureLevels[] = {
        D3D_FEATURE_LEVEL_11_0
    };

    HRESULT Result = D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0,
        CreationFlags, FeatureLevels,
        ARRAYSIZE(FeatureLevels),
        D3D11_SDK_VERSION, &BaseDevice, 0,
        &BaseContext);

    if (FAILED(Result)) {
        MessageBox(0, L"D3D11CreateDevice failed", 0, 0);
        return GetLastError();
    }

    ID3D11Device1* Device;
    ID3D11DeviceContext1* Context;

    Result = BaseDevice->QueryInterface(__uuidof(ID3D11Device1), (void**)&Device);
    assert(SUCCEEDED(Result));
    BaseDevice->Release();

    Result = BaseContext->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&Context);
    assert(SUCCEEDED(Result));
    BaseContext->Release();

    // Swap chain
    DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};

    SwapChainDesc.BufferDesc.Width = 0; 
    SwapChainDesc.BufferDesc.Height = 0;
    SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    SwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
    SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
    SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    SwapChainDesc.BufferCount = 1; 
    SwapChainDesc.OutputWindow = Window;
    SwapChainDesc.SampleDesc.Count = 1;
    SwapChainDesc.SampleDesc.Quality = 0;
    SwapChainDesc.Windowed = FALSE; 
    SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    SwapChainDesc.Flags = 0;

    //SwapChainDesc.Width = 0;
    //SwapChainDesc.Height = 0;
    //SwapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    //SwapChainDesc.SampleDesc.Count = 1;
    //SwapChainDesc.SampleDesc.Quality = 0;
    //SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    ///*SwapChainDesc.BufferCount = 2;
    //SwapChainDesc.Scaling = DXGI_SCALING_NONE;
    //SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    //SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;*/
    //SwapChainDesc.BufferCount = 1;
    //SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    //SwapChainDesc.Flags = 0;

    //DXGI_SWAP_CHAIN_FULLSCREEN_DESC FullscreenDesc = {};
    //FullscreenDesc.RefreshRate.Numerator = 0;
    //FullscreenDesc.RefreshRate.Denominator = 1;
    //FullscreenDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
    //FullscreenDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    //FullscreenDesc.Windowed = FALSE;

    IDXGISwapChain* SwapChain;
    
    IDXGIDevice2* DxgiDevice;
    Result = Device->QueryInterface(__uuidof(IDXGIDevice2), (void**)&DxgiDevice);
    assert(SUCCEEDED(Result));

    IDXGIAdapter* DxgiAdapter;
    Result = DxgiDevice->GetAdapter(&DxgiAdapter);
    assert(SUCCEEDED(Result));
    DxgiDevice->Release();

    IDXGIFactory2* DxgiFactory;
    Result = DxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&DxgiFactory);
    assert(SUCCEEDED(Result));
    DxgiAdapter->Release();

    //Result = DxgiFactory->CreateSwapChainForHwnd(Device, Window, &SwapChainDesc, &FullscreenDesc, 0, &SwapChain);
    Result = DxgiFactory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain);
    assert(SUCCEEDED(Result));
    DxgiFactory->Release();

    SwapChain->SetFullscreenState(TRUE, nullptr);
    

    // Frame buffer
    ID3D11Texture2D* FrameBuffer;
    Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&FrameBuffer);
    assert(SUCCEEDED(Result));

    ID3D11RenderTargetView* FrameBufferView;
    Result = Device->CreateRenderTargetView(FrameBuffer, 0, &FrameBufferView);
    assert(SUCCEEDED(Result));
    FrameBuffer->Release();

    // Shaders
    ID3D10Blob* VSBlob;
    Result = D3DCompileFromFile(L"vertex_shader.hlsl", 0, 0, "main", "vs_5_0", 0, 0, &VSBlob, 0);
    assert(SUCCEEDED(Result));

    ID3D11VertexShader* VertexShader;
    Result = Device->CreateVertexShader(VSBlob->GetBufferPointer(), VSBlob->GetBufferSize(), 0, &VertexShader);
    assert(SUCCEEDED(Result));

    ID3D10Blob* PSBlob;
    Result = D3DCompileFromFile(L"pixel_shader.hlsl", 0, 0, "main", "ps_5_0", 0, 0, &PSBlob, 0);
    assert(SUCCEEDED(Result));

    ID3D11PixelShader* PixelShader;
    Result = Device->CreatePixelShader(PSBlob->GetBufferPointer(), PSBlob->GetBufferSize(), 0, &PixelShader);
    assert(SUCCEEDED(Result));
    PSBlob->Release();

    // Input layout
    D3D11_INPUT_ELEMENT_DESC InputElementDesc[] = {
        {
            "POSITION", 0,
            DXGI_FORMAT_R32G32_FLOAT,
            0, 0,
            D3D11_INPUT_PER_VERTEX_DATA, 0
        },
        {
            "UV", 0,
            DXGI_FORMAT_R32G32_FLOAT,
            0, D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA, 0
        }
    };

    ID3D11InputLayout* InputLayout;
    Result = Device->CreateInputLayout(InputElementDesc,
        ARRAYSIZE(InputElementDesc),
        VSBlob->GetBufferPointer(),
        VSBlob->GetBufferSize(),
        &InputLayout
    );
    assert(SUCCEEDED(Result));
    VSBlob->Release();

    // Vertex data, x,y position & uv coords
    float VertexData[] = {
        -1.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 1.0f
    };

    // Vertex buffer
    D3D11_BUFFER_DESC VertexDataDesc = {
        sizeof(VertexData),
        D3D11_USAGE_DEFAULT,
        D3D11_BIND_VERTEX_BUFFER,
        0, 0, 0
    };
    D3D11_SUBRESOURCE_DATA VertexDataInitial = { VertexData };
    ID3D11Buffer* VertexDataBuffer;
    Result = Device->CreateBuffer(&VertexDataDesc,
        &VertexDataInitial,
        &VertexDataBuffer);
    assert(SUCCEEDED(Result));

    UINT Stride = 4 * sizeof(float);
    UINT Offset = 0;
    UINT NumVertices = sizeof(VertexData) / Stride;

    // Load image
    int ImageWidth;
    int ImageHeight;
    int ImageChannels;
    int ImageDesiredChannels = 4;

    unsigned char* ImageData = stbi_load("noise.png", &ImageWidth, &ImageHeight, &ImageChannels, ImageDesiredChannels);
    assert(ImageData);

    int ImagePitch = ImageWidth * 4;

    // Texture
    D3D11_TEXTURE2D_DESC ImageTextureDesc = {};

    ImageTextureDesc.Width = ImageWidth;
    ImageTextureDesc.Height = ImageHeight;
    ImageTextureDesc.MipLevels = 1;
    ImageTextureDesc.ArraySize = 1;
    ImageTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
    ImageTextureDesc.SampleDesc.Count = 1;
    ImageTextureDesc.SampleDesc.Quality = 0;
    ImageTextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
    ImageTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

    D3D11_SUBRESOURCE_DATA ImageSubresourceData = {};

    ImageSubresourceData.pSysMem = ImageData;
    ImageSubresourceData.SysMemPitch = ImagePitch;

    ID3D11Texture2D* ImageTexture;

    Result = Device->CreateTexture2D(&ImageTextureDesc, &ImageSubresourceData, &ImageTexture);
    assert(SUCCEEDED(Result));
    free(ImageData);

    // Shader resource view
    ID3D11ShaderResourceView* ImageShaderResourceView;

    Result = Device->CreateShaderResourceView(ImageTexture, nullptr, &ImageShaderResourceView);
    assert(SUCCEEDED(Result));

    // Sampler
    D3D11_SAMPLER_DESC ImageSamplerDesc = {};

    ImageSamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    ImageSamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    ImageSamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    ImageSamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    ImageSamplerDesc.MipLODBias = 0.0f;
    ImageSamplerDesc.MaxAnisotropy = 1;
    ImageSamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    ImageSamplerDesc.BorderColor[0] = 0;
    ImageSamplerDesc.BorderColor[1] = 0;
    ImageSamplerDesc.BorderColor[2] = 0;
    ImageSamplerDesc.BorderColor[3] = 0;
    ImageSamplerDesc.MinLOD = -FLT_MAX;
    ImageSamplerDesc.MaxLOD = FLT_MAX;

    ID3D11SamplerState* ImageSamplerState;

    Result = Device->CreateSamplerState(&ImageSamplerDesc, &ImageSamplerState);
    assert(SUCCEEDED(Result));

    bool Running = true;
    float Color[4] = { 0, 0, 0, 1 };

    Context->ClearRenderTargetView(FrameBufferView, Color);
    Context->RSSetViewports(1, &Viewport);
    Context->OMSetRenderTargets(1, &FrameBufferView, 0);
    Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    Context->IASetInputLayout(InputLayout);
    Context->VSSetShader(VertexShader, 0, 0);
    Context->PSSetShader(PixelShader, 0, 0);
    Context->PSSetShaderResources(0, 1, &ImageShaderResourceView);
    Context->PSSetSamplers(0, 1, &ImageSamplerState);
    Context->IASetVertexBuffers(0, 1, &VertexDataBuffer, &Stride, &Offset);

    while (Running) {
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
            if (Message.message == WM_QUIT) Running = false;
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

        if (wasPressed) {
            Context->Draw(NumVertices, 0);
        }
        else {
            Context->ClearRenderTargetView(FrameBufferView, Color);
        }
        SwapChain->Present(0, 0);
    }

    return 0;
}