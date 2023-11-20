#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <conio.h>
#include <chrono>
#include <zconf.h>

using namespace std;
using namespace std::chrono;


int getPixelData(HDC hdc)
{
    COLORREF _color = GetPixel(hdc, 100, 100);
    return int(GetRValue(_color));
}

void waitForWhite(HDC hdcScreen)
{
    while (getPixelData(hdcScreen) != 255)
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
    }

    HDC hdcScreen = GetDC(NULL);
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
            waitForWhite(hdcScreen);
            uint64_t end_time = duration_cast<microseconds>(
                    system_clock::now().time_since_epoch())
                    .count();

            cout << end_time - start_time << endl;
        }
    }
    return 0;
}

