#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <chrono>

using namespace std;
using namespace std::chrono;


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


int main(int argc, char **argv)
{
    BITMAPINFO bitmapinfo = createBitmapInfo();
    BYTE *bitPointer = new BYTE[bitmapinfo.bmiHeader.biSizeImage];
    HDC hdcScreen = GetDC(NULL);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);
    HBITMAP hBitmap = CreateDIBSection(hdcCompatible, &bitmapinfo, DIB_RGB_COLORS, (void **)(&bitPointer), NULL, 0);
    SelectObject(hdcCompatible, hBitmap);

    while (true)
    {
        BitBlt(hdcCompatible, 0, 0, 1, 1, hdcScreen, 5, 5, SRCCOPY);
        int result = (int)bitPointer[2];
        long long timestamp = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        printf("got color at:%lld:%d\n", timestamp, result);
        fflush(stdout);
    }
    return 0;
}
