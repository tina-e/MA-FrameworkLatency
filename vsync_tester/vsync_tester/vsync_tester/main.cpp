#include <Windows.h>
#include <iostream>

using namespace std;

typedef BOOL(APIENTRY* PFNWGLSWAPINTERVALFARPROC)(int);
typedef int(APIENTRY* PFNWGLGETSWAPINTERVALEXTPROC)();
PFNWGLSWAPINTERVALFARPROC wglSwapIntervalEXT = nullptr;
PFNWGLGETSWAPINTERVALEXTPROC wglGetSwapIntervalEXT = nullptr;


int main() {
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALFARPROC)wglGetProcAddress("wglSwapIntervalEXT");
    wglGetSwapIntervalEXT = (PFNWGLGETSWAPINTERVALEXTPROC)wglGetProcAddress("wglGetSwapIntervalEXT");

    if (wglSwapIntervalEXT == nullptr) {
        std::cerr << "wglSwapIntervalEXT not supported!" << std::endl;
        return 1;
    }

    Sleep(5000);

    HWND frameworkWindow = FindWindow(NULL, L"framework");
    HDC hdc = GetDC(frameworkWindow);
    HGLRC hglrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, hglrc);

    int vsyncEnabled = wglGetSwapIntervalEXT();
    //std::cout << "Vsync is currently " << (vsyncEnabled == 1 ? "enabled" : "disabled") << std::endl;

    //wglSwapIntervalEXT(1);

    //vsyncEnabled = wglGetSwapIntervalEXT();
    std::cout << "Vsync is currently " << (vsyncEnabled == 1 ? "enabled" : "disabled") << std::endl;
    Sleep(1000);
    
}


//
//#include <Windows.h>
//#include <d3d11.h>
//#include <iostream>
//
//using namespace std;
//
//// Function to check if VSync is enabled
//bool isVSyncEnabled() {
//    HWND hWnd = FindWindow(NULL, L"framework");
//    if (hWnd == NULL) {
//        std::cerr << "Window not found!" << std::endl;
//        return false;
//    }
//
//    HRESULT hr;
//
//    // Create a DXGI factory
//    IDXGIFactory* dxgiFactory;
//    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&dxgiFactory);
//    if (FAILED(hr)) {
//        std::cerr << "Failed to create DXGI factory!" << std::endl;
//        return false;
//    }
//
//    // Create a DXGI adapter
//    IDXGIAdapter* dxgiAdapter;
//    hr = dxgiFactory->EnumAdapters(0, &dxgiAdapter);
//    if (FAILED(hr)) {
//        dxgiFactory->Release();
//        std::cerr << "Failed to enumerate DXGI adapter!" << std::endl;
//        return false;
//    }
//
//    // Create a device
//    ID3D11DeviceContext* d3dDeviceContext;
//    IDXGISwapChain* swapChain;
//    DXGI_SWAP_CHAIN_DESC swapChainDesc;
//    ID3D11Device* d3dDevice;
//
//    D3D_FEATURE_LEVEL featureLevel;
//    hr = D3D11CreateDeviceAndSwapChain(
//        dxgiAdapter,
//        D3D_DRIVER_TYPE_UNKNOWN,
//        NULL,
//        D3D11_CREATE_DEVICE_DEBUG,
//        NULL,
//        0,
//        D3D11_SDK_VERSION,
//        &swapChainDesc,
//        &swapChain,
//        &d3dDevice,
//        &featureLevel,
//        &d3dDeviceContext
//    );
//    if (FAILED(hr)) {
//        dxgiAdapter->Release();
//        dxgiFactory->Release();
//        std::cerr << "Failed to create D3D11 device!" << std::endl;
//        return false;
//    }
//
//    // Check if VSync is enabled
//    hr = swapChain->GetDesc(&swapChainDesc);
//    d3dDevice->GetCreationFlags();
//
//    // Assuming VSync is enabled if the presentation interval is set to 1
//    bool vsyncEnabled = (swapChainDesc.BufferDesc.RefreshRate.Numerator != 0) && (swapChainDesc.BufferDesc.RefreshRate.Denominator != 0);
//
//    // Release resources
//    d3dDevice->Release();
//    dxgiAdapter->Release();
//    dxgiFactory->Release();
//
//    return vsyncEnabled;
//}
//
//int main() {
//    if (isVSyncEnabled()) {
//        std::cout << "VSync is enabled for the application." << std::endl;
//    }
//    else {
//        std::cout << "VSync is not enabled for the application." << std::endl;
//    }
//    return 0;
//}


