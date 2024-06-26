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

    while (true)
    {
        int result = int(GetRValue(GetPixel(hdcScreen, 5, 5)));
        long long duration = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
        printf("got color at:%lld:%d\n", duration, result);
        fflush(stdout);
    }
    return 0;
}

