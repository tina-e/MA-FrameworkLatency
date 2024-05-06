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

void waitForWhite(HDC hdcScreen, HDC hdcCompatible, BYTE *bitPointer)
{
    while(1) {
        if (getPixelData(hdcCompatible, hdcScreen, bitPointer) == 255) {
            break;
        }
    }
}

int main(int argc, char **argv)
{
    //self.start()
    //time.sleep(4.5)
    Sleep(4000);
    BITMAPINFO bitmapinfo = createBitmapInfo();
    BYTE *bitPointer = new BYTE[bitmapinfo.bmiHeader.biSizeImage];
    HDC hdcScreen = GetDC(NULL);
    HDC hdcCompatible = CreateCompatibleDC(hdcScreen);
    HBITMAP hBitmap = CreateDIBSection(hdcCompatible, &bitmapinfo, DIB_RGB_COLORS, (void **)(&bitPointer), NULL, 0);
    SelectObject(hdcCompatible, hBitmap);
    Beep(500, 2000); // schmatzer 7 sek, klick

    // time.sleep(4)
    Sleep(2500);
    Beep(500, 200);
    Sleep(500);
    Beep(500, 200);
    //schmatzer obacht

    // is fullscreen exclusive?
    QUERY_USER_NOTIFICATION_STATE nstate;
    SHQueryUserNotificationState(&nstate);
    printf("mode:%d\n", nstate);
    fflush(stdout);

    SHORT state = GetKeyState(VK_LBUTTON);

    while (true)
    {
        SHORT currentState = GetKeyState(VK_LBUTTON);
        if (currentState != state && currentState < 0)
        {
            state = currentState;
            uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            waitForWhite(hdcScreen, hdcCompatible, bitPointer);
            uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            Beep(659, 300); // E
            printf("%d\n", end_time - start_time);
            fflush(stdout);
        }
    }
    return 0;
}
