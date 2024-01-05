#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <conio.h>
#include <windows.h>
#include <iostream>

using namespace std;

int width;
int height;
HDC hdc;

void fill() {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            SetPixel(hdc, x, y, 0xffffff);
        }
    }
}

void clear() {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            SetPixel(hdc, x, y, 0x000000);
        }
    }
}

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch (Message) {
        case WM_KEYDOWN: {
            switch (WParam) {
                case 'O': {
                    DestroyWindow(Window);
                    break;
                }
            }
            break;
        }
        case WM_LBUTTONDOWN: {
            fill();
            break;
        }
        case WM_LBUTTONUP: {
            clear();
            break;
        }
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        default: {
            return DefWindowProc(Window, Message, WParam, LParam);
        }
    }
    return 0;
}

int main() {
    WNDCLASS WindowClass = {0};
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = GetModuleHandle(nullptr);
    WindowClass.lpszClassName = "framework";
    WindowClass.hCursor = LoadCursor(0, IDC_ARROW);

    if (!RegisterClass(&WindowClass)) {
        MessageBox(0, reinterpret_cast<LPCSTR>(L"RegisterClass failed"), 0, 0);
        return GetLastError();
    }

    HWND hwnd = CreateWindowEx(0, "framework", "framework", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                                 CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, GetModuleHandle(nullptr), 0);

    if (!hwnd) {
        MessageBox(0, reinterpret_cast<LPCSTR>(L"CreateWindowEx failed"), 0, 0);
        return GetLastError();
    }

    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    width = clientRect.right - clientRect.left;
    height = clientRect.bottom - clientRect.top;
    hdc = GetDC(hwnd);

    ShowWindow(hwnd, SW_SHOWNORMAL);
    UpdateWindow(hwnd);
    clear();

    bool Running = true;
    while (Running) {
        MSG Message;
        while (GetMessage(&Message, nullptr, 0, 0)) {
            if (Message.message == WM_QUIT) {
                Running = false;
            }
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
    }

    DestroyWindow(hwnd);
    ReleaseDC(hwnd, hdc);
    return 0;
}
