#include <iostream>
#include <windef.h>
#include <wingdi.h>
#include <winuser.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
    HDC hdcScreen = GetDC(NULL);

    // is fullscreen exclusive?
    /*QUERY_USER_NOTIFICATION_STATE nstate;
    SHQueryUserNotificationState(&nstate);
    printf("fullscreen-mode:%d\n", nstate);
    fflush(stdout);*/

    int pixelColor = 0;
    while (true)
    {
        int result = int(GetRValue(GetPixel(hdcScreen, 5, 5)));
        long timestamp = (long) (duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();
        printf("got color at:%ld:%d\n", timestamp, pixelColor == result);
        fflush(stdout);
        pixelColor = result;
    }
    return 0;
}

