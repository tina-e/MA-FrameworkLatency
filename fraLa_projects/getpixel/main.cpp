#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <conio.h>
#include <chrono>
#include <zconf.h>
#include <windows.h>

using namespace std;
using namespace std::chrono;

int getPixelData(HDC hdc)
{
    COLORREF _color = GetPixel(hdc, 5, 5);
    return int(GetRValue(_color));
}

void waitForChange(HDC hdcScreen)
{
    while(true) {
        int color = getPixelData(hdcScreen);
        if (color > 0) {
            break;
        }
    }
}

int main(int argc, char **argv)
{
    HDC hdcScreen = GetDC(NULL);

    SHORT state = GetKeyState(VK_LBUTTON);
    while (true)
    {
        SHORT currentState = GetKeyState(VK_LBUTTON);
        if (currentState != state && currentState < 0)
        {
            state = currentState;

            uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
            waitForChange(hdcScreen);
            uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            printf("%d\n", end_time - start_time);
            fflush(stdout);
        }
    }
    return 0;
}

