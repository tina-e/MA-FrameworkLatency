#include <windows.h>
#include <cairo/cairo.h>
#include <cairo/cairo-win32.h>

bool isPressed = false;
const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        cairo_surface_t* surface = cairo_win32_surface_create(hdc);
        cairo_t* cr = cairo_create(surface);

        if (isPressed) {
            cairo_set_source_rgb(cr, 1, 1, 1);
        }
        else {
            cairo_set_source_rgb(cr, 0, 0, 0);
        }

        cairo_paint(cr);

        cairo_destroy(cr);
        cairo_surface_destroy(surface);

        EndPaint(hwnd, &ps);
        break;
    }
    case WM_LBUTTONDOWN:
    {
        isPressed = true;
        InvalidateRect(hwnd, NULL, TRUE);
    };
    break;
    case WM_LBUTTONUP:
    {
        isPressed = false;
        InvalidateRect(hwnd, NULL, TRUE);
    };
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)0x000000;
    wc.lpszClassName = L"framework";
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(0, L"framework", L"framework", WS_POPUP,
        0, 0, WIDTH, HEIGHT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
