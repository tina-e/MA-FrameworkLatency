
#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <conio.h>
#include <chrono>
#include <zconf.h>
#include <vector>

using namespace std;
using namespace chrono;

BITMAPINFO createBitmapInfo()
{
    BITMAPINFO bitmap;
    bitmap.bmiHeader.biSize = sizeof(bitmap.bmiHeader);
    bitmap.bmiHeader.biWidth = 1;
    bitmap.bmiHeader.biHeight = -1;
    bitmap.bmiHeader.biPlanes = 1;
    bitmap.bmiHeader.biBitCount = 24;
    bitmap.bmiHeader.biCompression = BI_RGB;
    bitmap.bmiHeader.biSizeImage = 0;
    bitmap.bmiHeader.biClrUsed = 0;
    bitmap.bmiHeader.biClrImportant = 0;
    return bitmap;
}

int getPixelData(HDC hdcCompatible, HDC hdcScreen, HBITMAP hBitmap, BYTE *bitPointer, BITMAPINFO bitmapinfo)
{
    StretchBlt(hdcCompatible, 0, 0, 1, 1, hdcScreen, 0, 0, 1, 1, SRCCOPY);
    GetDIBits(hdcCompatible, hBitmap, 0, 1, bitPointer, (BITMAPINFO *)&bitmapinfo, DIB_RGB_COLORS);
    //cout << (int)bitPointer[2] << endl;
    return (int)bitPointer[2];
}

void waitForWhite(HDC hdcCompatible, HDC hdcScreen, HBITMAP hBitmap, BYTE *bitPointer, BITMAPINFO bitmapinfo)
{
    while (getPixelData(hdcCompatible, hdcScreen, hBitmap, bitPointer, bitmapinfo) != 255)
    {
        usleep(1);
    }
}

int main(int argc, char **argv)
{
    HWND frameworkWindow = FindWindow(NULL, "framework");
    if (frameworkWindow != NULL) {
        BringWindowToTop(frameworkWindow);
        SetForegroundWindow(frameworkWindow);
        ShowWindow(frameworkWindow, SW_RESTORE);
        SetFocus(frameworkWindow);
    } else {
        cerr << "no window named framework" << endl;
    }

    BITMAPINFO bitmapinfo = createBitmapInfo();
    BYTE *bitPointer = new BYTE[bitmapinfo.bmiHeader.biSizeImage];

    HDC hdcScreen = GetDC(NULL);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);

    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, 1, 1);
    SelectObject(hdcCompatible, hBitmap);

    SHORT state = GetKeyState(VK_LBUTTON);

    while (true)
    {
        SHORT currentState = GetKeyState(VK_LBUTTON);
        if (currentState != state && currentState < 0)
        {
            state = currentState;
            uint64_t start_time = duration_cast<microseconds>(
                    system_clock::now().time_since_epoch())
                    .count();
            waitForWhite(hdcCompatible, hdcScreen, hBitmap, bitPointer, bitmapinfo);

            uint64_t end_time = duration_cast<microseconds>(
                    system_clock::now().time_since_epoch())
                    .count();

            cout << end_time - start_time << endl;
        }
    }
    return 0;
}

