#include <windows.h>
#include <cairo/cairo.h>
#include <cairo/cairo-win32.h>

bool isPressed = false;
const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
cairo_surface_t* imageSurface = nullptr;

void LoadImage() {
    imageSurface = cairo_image_surface_create_from_png("noise.png");
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_CREATE:
    {
        LoadImage();
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        cairo_t* cr = cairo_create(cairo_win32_surface_create(hdc));
        if (isPressed) {
            cairo_set_source_surface(cr, imageSurface, 0, 0);
        }
        else {
            cairo_set_source_rgb(cr, 0, 0, 0);
        }
        cairo_paint(cr);

        cairo_destroy(cr);
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
        CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
