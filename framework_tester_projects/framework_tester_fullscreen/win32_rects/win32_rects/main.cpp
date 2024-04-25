// based on tutorial: https://samulinatri.com/things/win32-drawing-rectangles/
#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <random>

typedef uint32_t u32;

void* BitmapMemory;

int BitmapWidth;
int BitmapHeight;

int ClientWidth;
int ClientHeight;

const int n_rects = 1000;
bool isPressed = false;


int randint(int low, int high)
{
    return low + rand() % (high - low);
}


void DrawRects() {
    int rectW = ClientWidth / 5;
    int rectH = ClientHeight / 5;
    for (int i = 0; i < n_rects; i++) {
        int rectX = (rand() % (ClientWidth / 2 - rectW)) + ClientWidth / 2;
        int rectY = rand() % (ClientHeight - rectH);

        int r = randint(0, 255);
        int g = randint(0, 255);
        int b = randint(0, 255);
        u32 color = (255 << 24) + (int(r) << 16) + (int(g) << 8) + int(b);

        u32* pixel = (u32*)BitmapMemory;
        pixel += rectY * BitmapWidth + rectX;

        for (int y = 0; y < rectH; ++y) {
            for (int x = 0; x < rectW; ++x) {
                *pixel++ = color;
            }
            pixel += BitmapWidth - rectW;
        }
    }
    // draw white rect
    u32* pixel = (u32*)BitmapMemory;
    for (int y = 0; y < rectH; ++y) {
        for (int x = 0; x < rectW; ++x) {
            *pixel++ = 0xffffff;
        }
        pixel += BitmapWidth - rectW;
    }
    //OutputDebugStringW(L"rects done\n");
}

void clear() {
    u32* pixel = (u32*)BitmapMemory;
    for (int i = 0; i < BitmapWidth * BitmapHeight; ++i) {
        *pixel++ = 0x000000;
    }
}

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam) {
    switch (Message) {
        case WM_KEYDOWN: {
            switch (WParam) {
            case 'O': {
                DestroyWindow(Window);
            }; break;
            }
        } break;
        case WM_LBUTTONDOWN: {
            //OutputDebugStringW(L"down\n");
            isPressed = true;
            DrawRects();
        }; break;
        case WM_LBUTTONUP: {
            //OutputDebugStringW(L"up\n");
            isPressed = false;
        }; break;
        case WM_DESTROY: {
            PostQuitMessage(0);
        } break;
        default: {
            return DefWindowProc(Window, Message, WParam, LParam);
        }
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow) {

    WNDCLASS WindowClass = {};
    const wchar_t ClassName[] = L"framework";
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = ClassName;
    RegisterClass(&WindowClass);

    /*int w = (int) (GetSystemMetrics(SM_CXSCREEN) * 0.8);
    int h = (int) (GetSystemMetrics(SM_CYSCREEN) * 0.8);*/
    int w = GetSystemMetrics(SM_CXSCREEN);
    int h = GetSystemMetrics(SM_CYSCREEN);

    HWND Window = CreateWindow(ClassName, L"framework", WS_POPUP, 0, 0, w, h, 0, 0, Instance, 0);
    if (!Window) return 0;
    ShowWindow(Window, SW_SHOW);
    //ShowWindow(Window, SW_SHOWMAXIMIZED);


    // Get client area dimensions 

    RECT ClientRect;
    GetClientRect(Window, &ClientRect);
    ClientWidth = ClientRect.right - ClientRect.left;
    ClientHeight = ClientRect.bottom - ClientRect.top;

    BitmapWidth = ClientWidth;
    BitmapHeight = ClientHeight;

    // Allocate memory for the bitmap

    int BytesPerPixel = 4;

    BitmapMemory = VirtualAlloc(0,
        BitmapWidth * BitmapHeight * BytesPerPixel,
        MEM_RESERVE | MEM_COMMIT,
        PAGE_READWRITE
    );

    // BitmapInfo struct for StretchDIBits

    BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = BitmapWidth;
    BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    HDC DeviceContext = GetDC(Window);

    bool Running = true;
    while (Running) {
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
            if (Message.message == WM_QUIT) Running = false;
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
        // OutputDebugStringW(L"here\n");
        if (!isPressed) {
            clear();
        }
        StretchDIBits(DeviceContext,
            0, 0,
            BitmapWidth, BitmapHeight,
            0, 0,
            ClientWidth, ClientHeight,
            BitmapMemory, &BitmapInfo,
            DIB_RGB_COLORS, SRCCOPY);
    }

    return 0;
}