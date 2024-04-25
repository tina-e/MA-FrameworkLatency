#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <wincodec.h> 
#pragma comment(lib, "windowscodecs.lib") 

typedef uint32_t u32;

void* BitmapMemory = nullptr;
int BitmapWidth;
int BitmapHeight;

IWICImagingFactory* pFactory = nullptr;
IWICBitmapDecoder* pDecoder = nullptr;
IWICBitmapFrameDecode* pFrame = nullptr;

void LoadImageFromFile()
{
    CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(&pFactory)
    );

    pFactory->CreateDecoderFromFilename(
        L"noise.png",
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );

    pDecoder->GetFrame(0, &pFrame);

    BitmapMemory = VirtualAlloc(nullptr, BitmapWidth * BitmapHeight * sizeof(u32), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}

void DrawImage()
{
    if (!pFrame) return;

    WICRect rc = { 0, 0, BitmapWidth, BitmapHeight };
    UINT stride = BitmapWidth * sizeof(u32);

    pFrame->CopyPixels(&rc, stride, BitmapWidth * BitmapHeight * sizeof(u32), (BYTE*)BitmapMemory);
}

void fill()
{
    u32* pixel = (u32*)BitmapMemory;
    for (int i = 0; i < BitmapWidth * BitmapHeight; ++i)
    {
        *pixel++ = 0x000000;
    }
}

LRESULT CALLBACK WindowProc(HWND Window, UINT Message, WPARAM WParam, LPARAM LParam)
{
    switch (Message)
    {
    case WM_KEYDOWN:
    {
        switch (WParam)
        {
        case 'O':
        {
            DestroyWindow(Window);
        };
        break;
        }
    }
    break;
    case WM_LBUTTONDOWN:
    {
        DrawImage();
    };
    break;
    case WM_LBUTTONUP:
    {
        fill();
    };
    break;
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;
    default:
    {
        return DefWindowProc(Window, Message, WParam, LParam);
    }
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE Instance, HINSTANCE PrevInstance, PWSTR CmdLine, int CmdShow)
{

    WNDCLASS WindowClass = {};
    const wchar_t ClassName[] = L"framework";
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = Instance;
    WindowClass.lpszClassName = ClassName;
    RegisterClass(&WindowClass);

    BitmapHeight = GetSystemMetrics(SM_CYSCREEN);
    BitmapWidth = GetSystemMetrics(SM_CXSCREEN);

    HWND Window = CreateWindow(ClassName, L"framework", WS_POPUP, 0, 0, BitmapWidth, BitmapHeight, 0, 0, Instance, 0);
    if (!Window) return 0;
    ShowWindow(Window, SW_SHOW);

    // Allocate memory for the bitmap
    int BytesPerPixel = sizeof(u32);
    BitmapMemory = VirtualAlloc(0,
        BitmapWidth * BitmapHeight * BytesPerPixel,
        MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

    // BitmapInfo struct for StretchDIBits
    BITMAPINFO BitmapInfo;
    BitmapInfo.bmiHeader.biSize = sizeof(BitmapInfo.bmiHeader);
    BitmapInfo.bmiHeader.biWidth = BitmapWidth;
    BitmapInfo.bmiHeader.biHeight = -BitmapHeight;
    BitmapInfo.bmiHeader.biPlanes = 1;
    BitmapInfo.bmiHeader.biBitCount = 32;
    BitmapInfo.bmiHeader.biCompression = BI_RGB;

    HDC DeviceContext = GetDC(Window);
    LoadImageFromFile();

    bool Running = true;
    while (Running)
    {
        MSG Message;
        while (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE))
        {
            if (Message.message == WM_QUIT)
                Running = false;
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }

       StretchDIBits(DeviceContext,
            0, 0, BitmapWidth, BitmapHeight,
            0, 0, BitmapWidth, BitmapHeight,
            BitmapMemory, &BitmapInfo,
            DIB_RGB_COLORS, SRCCOPY);
    }

    return 0;
}