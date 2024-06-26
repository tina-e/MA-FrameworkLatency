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

int getPixelData(HDC hdcCompatible, HDC hdcScreen, BYTE *bitPointer)
{
    BitBlt(hdcCompatible, 0, 0, 1, 1, hdcScreen, 5, 5, SRCCOPY);
    return (int)bitPointer[2];
}

void waitForChange(HDC hdcScreen, HDC hdcCompatible, BYTE *bitPointer)
{
    while(true) {
        int color = getPixelData(hdcCompatible, hdcScreen, bitPointer);
        if (color > 0) {
            break;
        }
    }
}

int main(int argc, char **argv)
{
    BITMAPINFO bitmapinfo = createBitmapInfo();
    BYTE *bitPointer = new BYTE[bitmapinfo.bmiHeader.biSizeImage];
    HDC hdcScreen = GetDC(NULL);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);
    HBITMAP hBitmap = CreateDIBSection(hdcCompatible, &bitmapinfo, DIB_RGB_COLORS, (void **)(&bitPointer), NULL, 0);
    SelectObject(hdcCompatible, hBitmap);

    SHORT state = GetKeyState(VK_LBUTTON);
    while (true)
    {
        SHORT currentState = GetKeyState(VK_LBUTTON);
        if (currentState != state && currentState < 0)
        {
            state = currentState;

            uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            waitForChange(hdcScreen, hdcCompatible, bitPointer);
            uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            printf("%d\n", end_time - start_time);
            fflush(stdout);
        }
    }
    return 0;
}

