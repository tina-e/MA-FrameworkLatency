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

int x = 5;
int y = 5;
int initColor = 0;

int getPixelData(HDC hdc)
{
    COLORREF _color = GetPixel(hdc, x, y);
    return int(GetRValue(_color));
}

void waitForChange(HDC hdcScreen)
{
    while(true) {
        int color = getPixelData(hdcScreen);
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

    HDC hdcScreen = GetDC(NULL);
    initColor = getPixelData(hdcScreen);
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
            waitForChange(hdcScreen);
            uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            printf("%d\n", end_time - start_time);
            fflush(stdout);
        }
    }
    return 0;
}

