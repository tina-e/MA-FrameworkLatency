#include <Windows.h>
#include <d3d11.h>
#include <wrl/client.h> // For Microsoft::WRL::ComPtr

#pragma comment(lib, "d3d11.lib")


//D3D11_TEXTURE2D_DESC createTexture()
//{
//    D3D11_TEXTURE2D_DESC desc;
//    desc.Width = 1;
//    desc.Height = 1;
//    desc.MipLevels = 1;
//    desc.ArraySize = 1;
//    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    desc.SampleDesc.Count = 1;
//    desc.Usage = D3D11_USAGE_STAGING;
//    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
//    desc.MiscFlags = 0;
//    return desc;
//}
//
//
//int getPixelData()
//{
//
//}
//
//
//void waitForWhite()
//{
//
//}


#include <Windows.h>
#include <d3d11.h>
#include <wrl/client.h> // For Microsoft::WRL::ComPtr

#pragma comment(lib, "d3d11.lib")

int main() {
    // Initialize COM (Component Object Model)
    CoInitialize(nullptr);

    // Create a window or use an existing one
    HWND hwnd = GetDesktopWindow();

    // Create the Direct3D device and device context
    Microsoft::WRL::ComPtr<ID3D11Device> device;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext;

    D3D_FEATURE_LEVEL featureLevel;
    HRESULT hr = D3D11CreateDevice(
        nullptr,                     // Use the default adapter
        D3D_DRIVER_TYPE_HARDWARE,    // Use hardware acceleration
        nullptr,                     // No software rasterizer
        0,                           // No flags
        nullptr,                     // Use default feature levels
        0,                           // Number of feature levels
        D3D11_SDK_VERSION,           // SDK version
        device.GetAddressOf(),       // Output: pointer to the device
        &featureLevel,               // Output: pointer to the selected feature level
        deviceContext.GetAddressOf() // Output: pointer to the device context
    );

    if (FAILED(hr)) {
        // Handle error
        return 1;
    }

    // Get the DXGI factory
    Microsoft::WRL::ComPtr<IDXGIFactory1> dxgiFactory;
    hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)dxgiFactory.GetAddressOf());
    if (FAILED(hr)) {
        // Handle error
        return 1;
    }

    // Get the primary adapter
    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
    hr = dxgiFactory->EnumAdapters1(0, adapter.GetAddressOf());
    if (FAILED(hr)) {
        // Handle error
        return 1;
    }

    // Get the output (monitor) of the primary adapter
    Microsoft::WRL::ComPtr<IDXGIOutput> output;
    hr = adapter->EnumOutputs(0, output.GetAddressOf());
    if (FAILED(hr)) {
        // Handle error
        return 1;
    }

    // Get the display mode of the primary output
    DXGI_MODE_DESC displayModeDesc;
    hr = output->FindClosestMatchingMode(&displayModeDesc, &displayModeDesc, device.Get());
    if (FAILED(hr)) {
        // Handle error
        return 1;
    }

    // Create a swap chain that covers the entire screen
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 2;                                   // Double buffering
    swapChainDesc.BufferDesc = displayModeDesc;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hwnd;
    swapChainDesc.SampleDesc.Count = 1;                              // No anti-aliasing
    swapChainDesc.Windowed = TRUE;                                   // Windowed mode

    Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
    hr = dxgiFactory->CreateSwapChain(device.Get(), &swapChainDesc, swapChain.GetAddressOf());
    if (FAILED(hr)) {
        // Handle error
        return 1;
    }

    // Get the back buffer of the swap chain
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
    if (FAILED(hr)) {
        // Handle error
        return 1;
    }

    // Map screen coordinates to pixel position
    int x = 100;
    int y = 100;

    // Render a frame to the back buffer
    // ...

    // Create a staging texture to read back data
    D3D11_TEXTURE2D_DESC desc;
    desc.Width = 1;
    desc.Height = 1;
    desc.MipLevels = 1;
    desc.ArraySize = 1;
    desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    desc.SampleDesc.Count = 1;
    desc.Usage = D3D11_USAGE_STAGING;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    desc.MiscFlags = 0;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> stagingTexture;
    device->CreateTexture2D(&desc, nullptr, stagingTexture.GetAddressOf());

    // Copy the pixel data to the staging texture
    deviceContext->CopySubresourceRegion(stagingTexture.Get(), 0, 0, 0, 0, backBuffer.Get(), 0, nullptr);

    // Map the staging texture for reading
    D3D11_MAPPED_SUBRESOURCE mappedResource;
    deviceContext->Map(stagingTexture.Get(), 0, D3D11_MAP_READ, 0, &mappedResource);

    // Get the color of the specified pixel
    UINT8* pixel = static_cast<UINT8*>(mappedResource.pData);
    UINT8 red = pixel[0];
    UINT8 green = pixel[1];
    UINT8 blue = pixel[2];

    // Unmap the staging texture
    deviceContext->Unmap(stagingTexture.Get(), 0);

    // Release resources
    stagingTexture.Reset();
    backBuffer.Reset();
    swapChain.Reset();
    output.Reset();
    adapter.Reset();
    dxgiFactory.Reset();
    deviceContext.Reset();
    device.Reset();

    // Uninitialize COM
    CoUninitialize();

    return 0;
}

