#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <conio.h>
#include <chrono>
#include <zconf.h>
#include <vector>
#include <windows.h>


using namespace std;
using namespace chrono;

int x = 5;
int y = 5;
int initColor = 0;

BITMAPINFO createBitmapInfo()
{
    BITMAPINFO bitmap;
    bitmap.bmiHeader.biSize = sizeof(bitmap.bmiHeader);
    bitmap.bmiHeader.biWidth = 1;
    bitmap.bmiHeader.biHeight = -1;
    bitmap.bmiHeader.biPlanes = 1;
    bitmap.bmiHeader.biBitCount = 32;
    bitmap.bmiHeader.biCompression = BI_RGB;
    bitmap.bmiHeader.biSizeImage = 0;
    bitmap.bmiHeader.biClrUsed = 0;
    bitmap.bmiHeader.biClrImportant = 0;
    return bitmap;
}

int getPixelData(HDC hdcCompatible, HDC hdcScreen, HBITMAP hBitmap, BYTE *bitPointer, BITMAPINFO bitmapinfo)
{
    StretchBlt(hdcCompatible, 0, 0, 1, 1, hdcScreen, x, y, 1, 1, SRCCOPY);
    GetDIBits(hdcCompatible, hBitmap, 0, 1, bitPointer, (BITMAPINFO *)&bitmapinfo, DIB_RGB_COLORS);
    return (int)bitPointer[2];
}

void waitForChange(HDC hdcCompatible, HDC hdcScreen, HBITMAP hBitmap, BYTE *bitPointer, BITMAPINFO bitmapinfo)
{
    while(true) {
        int color = getPixelData(hdcCompatible, hdcScreen, hBitmap, bitPointer, bitmapinfo);
        if (color != initColor) {
            break;
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        x = atoi(argv[1]);
        y = atoi(argv[1]);
    } else if (argc == 3)
    {
        x = atoi(argv[1]);
        y = atoi(argv[2]);
    }

    BITMAPINFO bitmapinfo = createBitmapInfo();
    BYTE *bitPointer = new BYTE[bitmapinfo.bmiHeader.biSizeImage];
    HDC hdcScreen = GetDC(NULL);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, 1, 1);
    SelectObject(hdcCompatible, hBitmap);

    initColor = getPixelData(hdcCompatible, hdcScreen, hBitmap, bitPointer, bitmapinfo);
    Beep(700, 250);
    Beep(700, 350);

    SHORT state = GetKeyState(VK_LBUTTON);
    while (true)
    {
        SHORT currentState = GetKeyState(VK_LBUTTON);
        if (currentState != state && currentState < 0)
        {
            state = currentState;

            uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            waitForChange(hdcCompatible, hdcScreen, hBitmap, bitPointer, bitmapinfo);
            uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            printf("%d\n", end_time - start_time);
            fflush(stdout);
        }
    }
    return 0;
}

