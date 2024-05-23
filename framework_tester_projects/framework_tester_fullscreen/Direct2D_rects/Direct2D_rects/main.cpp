// based on chatgpt
#include <windows.h>
#include <d2d1.h>
#include <vector>

#pragma comment(lib, "d2d1.lib")


const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const int NUM_RECTS = 999;

bool isPressed = false;
ID2D1Factory* g_pD2DFactory = nullptr;
ID2D1HwndRenderTarget* g_pRenderTarget = nullptr;
ID2D1SolidColorBrush* pBrush = nullptr;
std::vector<D2D1_RECT_F> rectangles;
std::vector<D2D1::ColorF> colors;


int randint(int low, int high)
{
    return low + rand() % (high - low);
}

void CreateRectangles() {
    for (int i = 0; i < NUM_RECTS; i++) {
        int w = randint(100, 500);
        int h = randint(100, 500);
        int x = randint(100, WIDTH - w);
        int y = randint(0, HEIGHT - h);
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        rectangles.push_back(D2D1::RectF(x, y, x+w, y+h));
        colors.push_back(D2D1::ColorF(r, g, b, 1.0f));
    }
    rectangles.push_back(D2D1::RectF(0, 0, 100, 100));
    colors.push_back(D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
}

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


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        if (FAILED(InitializeDirect2D(hwnd))) {
            return -1;
        }
        break;

    case WM_PAINT: {
        if (g_pRenderTarget) {
            g_pRenderTarget->BeginDraw();
            if (isPressed) {
                for (int i = 0; i < NUM_RECTS + 1; i++) {
                    g_pRenderTarget->CreateSolidColorBrush(colors[i], &pBrush);
                    g_pRenderTarget->FillRectangle(rectangles[i], pBrush);
                }  
            }
            else {
                g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
            }
            g_pRenderTarget->EndDraw();
        } 
        ValidateRect(hwnd, NULL);
        break;
    }

    case WM_LBUTTONDOWN:
        isPressed = true;
        CreateRectangles();
        InvalidateRect(hwnd, NULL, TRUE);
        break;

    case WM_LBUTTONUP:
        isPressed = false;
        InvalidateRect(hwnd, NULL, TRUE);
        rectangles.clear();
        colors.clear();
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
