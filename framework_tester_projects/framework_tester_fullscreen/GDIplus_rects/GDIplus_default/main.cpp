#include <windows.h>
#include <gdiplus.h>
#include <vector>

using namespace Gdiplus;


const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const int NUM_RECTS = 999;

bool isPressed = false;
Pen pen(Color(0, 0, 0, 0), 0);
std::vector<Rect> rectangles;
std::vector<Color> colors;


int randint(int low, int high)
{
    return low + rand() % (high - low);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Graphics graphics(hdc);
        if (isPressed) {
            for (int i = 0; i < NUM_RECTS+1; i++) {
                SolidBrush brush(colors[i]);
                graphics.FillRectangle(&brush, rectangles[i]);
                graphics.DrawRectangle(&pen, rectangles[i]);
            }
        }
        else {
            graphics.Clear(Color(0, 0, 0));
        }

        EndPaint(hwnd, &ps);
    } break;

    case WM_LBUTTONDOWN: {
        isPressed = true;
        for (int i = 0; i < NUM_RECTS; i++) {
            int w = randint(100, 500);
            int h = randint(100, 500);
            int x = randint(100, WIDTH - w);
            int y = randint(0, HEIGHT - h);
            int r = randint(0, 255);
            int g = randint(0, 255);
            int b = randint(0, 255);
            colors.push_back(Color(255, r, g, b));
            rectangles.push_back(Rect(x, y, w, h));
        }
        colors.push_back(Color(255, 255, 255, 255));
        rectangles.push_back(Rect(0, 0, 100, 100));
        InvalidateRect(hwnd, NULL, TRUE);
    } break;

    case WM_LBUTTONUP: {
        isPressed = false;
        rectangles.clear();
        colors.clear();
        InvalidateRect(hwnd, NULL, TRUE);
    } break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Initialize GDI+
    GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Register the window class
    const wchar_t CLASS_NAME[] = L"framework";
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    // Create the window
    HWND hwnd = CreateWindowEx(0, L"framework", L"framework", WS_POPUP, 0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
    if (hwnd == nullptr) {
        return 0;
    }

    ShowWindow(hwnd, SW_SHOWMAXIMIZED);  

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Shutdown GDI+
    GdiplusShutdown(gdiplusToken);

    return 0;
}
