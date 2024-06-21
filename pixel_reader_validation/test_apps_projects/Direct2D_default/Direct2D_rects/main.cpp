#include <windows.h>
#include <d2d1.h>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

#pragma comment(lib, "d2d1.lib")


const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

int numClicks = 0;
float color = 0.0f;
bool started = false;
bool isTransitioning = false;

bool isPressed = false;
ID2D1Factory* g_pD2DFactory = nullptr;
ID2D1HwndRenderTarget* g_pRenderTarget = nullptr;


HRESULT InitializeDirect2D(HWND hwnd) {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
    if (FAILED(hr)) {
        return hr;
    }

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
}

void UpdateColor(HWND hwnd) {
    color += 0.1f;
    if (color >= 1.0f) {
        color = 1.0f;
        isTransitioning = false;
        PostQuitMessage(0);
    }
    InvalidateRect(hwnd, NULL, TRUE);
    if (isTransitioning) {
        SetTimer(hwnd, 1, 50, NULL);
    }
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE: {
        if (FAILED(InitializeDirect2D(hwnd))) {
            return -1;
        }
        break;
    }
    case WM_PAINT: {
        printf("render_start:%d:%ld\n", (int)color*100, (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count());
        fflush(stdout);
        if (g_pRenderTarget) {
            g_pRenderTarget->BeginDraw();
            g_pRenderTarget->Clear(D2D1::ColorF(color, color, color));
            g_pRenderTarget->EndDraw();
        }
        ValidateRect(hwnd, NULL);
        printf("render_stop:%d:%ld\n", (int)color*100, (long)(duration_cast<microseconds>(system_clock::now().time_since_epoch())).count());
        fflush(stdout);
        break;
    }

    case WM_LBUTTONDOWN: {
        if (++numClicks == 3) {
            isTransitioning = true;
            SetTimer(hwnd, 1, 50, NULL);
        }
        break;
    }
    case WM_TIMER: {
        if (isTransitioning) {
            KillTimer(hwnd, 1);
            UpdateColor(hwnd);
        }
        break;
    }
    case WM_DESTROY: {
        Cleanup();
        PostQuitMessage(0);
        break;
    }
    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
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
