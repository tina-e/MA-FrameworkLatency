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

void waitForWhite(HDC hdcScreen)
{
    while(true) {
        if (getPixelData(hdcScreen) > 0) {
            break;
        }
    }
}

int main(int argc, char **argv)
{
    //self.start()
    //time.sleep(4.5)
    Sleep(4000);
    HDC hdcScreen = GetDC(NULL);
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
            waitForWhite(hdcScreen);
            uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

            Beep(523, 300); // C
            printf("%d\n", end_time - start_time);
            fflush(stdout);
            //cout << end_time - start_time << endl;
        }
    }
    return 0;
}

