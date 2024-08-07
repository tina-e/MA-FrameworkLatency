// based on chatgpt
#include <windows.h>
#include <blend2d.h>

const int WIDTH = 100;
const int HEIGHT = 100;

BLImage img(WIDTH, HEIGHT, BL_FORMAT_PRGB32);
bool isWhite = false;


void PaintScreen(HDC hdc) {
    BLContext ctx(img);
    if (isWhite) {
        ctx.setFillStyle(BLRgba32(255, 255, 255));
    }
    else {
        ctx.setFillStyle(BLRgba32(0, 0, 0));
    }
    ctx.fillAll();

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
        isWhite = true;
        InvalidateRect(hwnd, NULL, TRUE);
    } break;
    case WM_LBUTTONUP: {
        isWhite = false;
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

    ShowWindow(hwnd, nCmdShow);

    // Run the message loop
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
