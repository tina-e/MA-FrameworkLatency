#include <windows.h>
#include "include/core/SkCanvas.h"
#include "include/core/SkPaint.h"

const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // Register window class
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)0x000000;
    wc.lpszClassName = L"frameworok";
    RegisterClassEx(&wc);

    // Create window
    HWND hwnd = CreateWindowEx(0, L"frameworok", L"framework", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
        MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // Create Skia canvas
        sk_sp<SkSurface> surface = SkSurface::MakeRasterN32Premul(ps.rcPaint.right - ps.rcPaint.left,
            ps.rcPaint.bottom - ps.rcPaint.top);
        SkCanvas* canvas = surface->getCanvas();

        // Clear canvas
        canvas->clear(SK_ColorWHITE);

        // Draw rectangle
        SkPaint paint;
        paint.setColor(SK_ColorBLUE);
        paint.setStyle(SkPaint::kFill_Style);
        canvas->drawRect(SkRect::MakeLTRB(50, 50, 200, 200), paint);

        // Flush Skia canvas to device context
        canvas->flush();

        // Copy Skia surface to device context
        SkPixmap pixmap;
        surface->peekPixels(&pixmap);
        memcpy(ps.lpPaint, pixmap.addr(), pixmap.computeByteSize());

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
