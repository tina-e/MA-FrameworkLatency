// based on chatgpt
#include <windows.h>
#include <blend2d.h>

const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const int NUM_RECTS = 999;

BLImage img(WIDTH, HEIGHT, BL_FORMAT_PRGB32);
bool isPressed = false;


int randint(int low, int high)
{
    return low + rand() % (high - low);
}


void PaintScreen(HDC hdc) {
    BLContext ctx(img);
    ctx.setFillStyle(BLRgba32(0, 0, 0));
    ctx.fillAll();

    //BLContext ctx(img);
    if (isPressed) {
        for (int i = 0; i < NUM_RECTS; ++i) {
            int w = randint(100, 500);
            int h = randint(100, 500);
            int x = randint(100, WIDTH - w);
            int y = randint(0, HEIGHT - h);
            int r = randint(0, 255);
            int g = randint(0, 255);
            int b = randint(0, 255);
            ctx.setFillStyle(BLRgba32(r, g, b));
            ctx.fillRect(x, y, w, h);
        }
        ctx.setFillStyle(BLRgba32(255, 255, 255));
        ctx.fillRect(0, 0, 100, 100);
    }

    // Get image data from the Blend2D image
    BLImageData imgData;
    img.getData(&imgData);

    // Create a HBITMAP from the Blend2D image data
    HBITMAP hBitmap = CreateBitmap(imgData.size.w, imgData.size.h, 1, 32, imgData.pixelData);

    HDC hMemDC = CreateCompatibleDC(hdc);
    SelectObject(hMemDC, hBitmap);

    // Copy the memory device context to the window's device context
    BitBlt(hdc, 0, 0, imgData.size.w, imgData.size.h, hMemDC, 0, 0, SRCCOPY);

    // Clean up
    DeleteDC(hMemDC);
    DeleteObject(hBitmap);
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        PaintScreen(hdc);
        EndPaint(hwnd, &ps);
    } break;

    case WM_LBUTTONDOWN: {
        isPressed = true;
        InvalidateRect(hwnd, NULL, TRUE);
    } break;
    case WM_LBUTTONUP: {
        isPressed = false;
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


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow) {
    // Register the window class
    const wchar_t CLASS_NAME[] = L"framework";

    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

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

    return 0;
}
