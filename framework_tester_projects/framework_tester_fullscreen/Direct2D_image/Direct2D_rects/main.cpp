// based on chatgpt
#include <windows.h>
#include <d2d1.h>
#include <wincodec.h>
#include <vector>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")


const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

bool isPressed = false;
ID2D1Factory* g_pD2DFactory = nullptr;
ID2D1HwndRenderTarget* g_pRenderTarget = nullptr;
IWICImagingFactory* g_pWICFactory = nullptr;
ID2D1Bitmap* g_pBitmap = nullptr;


void LoadImage(LPCWSTR uri, ID2D1Bitmap** ppBitmap) {
    IWICBitmapDecoder* pDecoder = nullptr;
    IWICBitmapFrameDecode* pSource = nullptr;
    IWICStream* pStream = nullptr;
    IWICFormatConverter* pConverter = nullptr;
    IWICBitmapScaler* pScaler = nullptr;

    HRESULT hr = g_pWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );

    hr = pDecoder->GetFrame(0, &pSource);
    hr = g_pWICFactory->CreateFormatConverter(&pConverter);
    hr = pConverter->Initialize(
        pSource,
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        NULL,
        0.0f,
        WICBitmapPaletteTypeMedianCut
    );

    hr = g_pRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, ppBitmap);
}

HRESULT InitializeDirect2D(HWND hwnd) {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);

    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        (LPVOID*)&g_pWICFactory
    );

    RECT rc;
    GetClientRect(hwnd, &rc);
    hr = g_pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
        &g_pRenderTarget
    );

    return hr;
}

void Cleanup() {
    if (g_pRenderTarget) {
        g_pRenderTarget->Release();
        g_pRenderTarget = nullptr;
    }
    if (g_pD2DFactory) {
        g_pD2DFactory->Release();
        g_pD2DFactory = nullptr;
    }
    if (g_pWICFactory) {
        g_pWICFactory->Release();
        g_pWICFactory = nullptr;
    }
    if (g_pBitmap) {
        g_pBitmap->Release();
        g_pBitmap = nullptr;
    }
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        if (FAILED(InitializeDirect2D(hwnd))) {
            return -1;
        }
        LoadImage(L"noise.png", &g_pBitmap);
        break;

    case WM_PAINT: {
        if (g_pRenderTarget) {
            g_pRenderTarget->BeginDraw();
            g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
            if (isPressed && g_pBitmap) {
                g_pRenderTarget->DrawBitmap(g_pBitmap);
            }
            g_pRenderTarget->EndDraw();
        } 
        ValidateRect(hwnd, NULL);
        break;
    }

    case WM_LBUTTONDOWN:
        isPressed = true;
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_LBUTTONUP:
        isPressed = false;
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_DESTROY:
        Cleanup();
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {   
    HRESULT hr = CoInitialize(NULL);
    
    WNDCLASSEX wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WindowProc, 0, 0, hInstance, nullptr, nullptr, nullptr, nullptr, L"framework", nullptr };
    RegisterClassEx(&wcex);

    HWND hwnd = CreateWindowEx(0, L"framework", L"framework", WS_POPUP, 0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
    if (!hwnd) return -1;

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hwnd);

    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
