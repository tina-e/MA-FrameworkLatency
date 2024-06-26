// based on: https://github.com/bmharper/WindowsDesktopDuplicationSample

#include "windup.h"
#include "WinDesktopDup.h"
#include <iostream>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace chrono;

WinDesktopDup dup;


void SetupDpiAwareness() {
	if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
		cerr << "SetProcessDpiAwarenessContext failed" << endl;
}

int main() {
	SetupDpiAwareness();
	auto err = dup.Initialize();

	// is fullscreen exclusive?
	/*QUERY_USER_NOTIFICATION_STATE nstate;
	SHQueryUserNotificationState(&nstate);
	printf("mode:%d\n", nstate);
	fflush(stdout);*/

	int pixelColor = 0;
	while (true) {
		int  result    = dup.GetColorValueAt(5, 5);
		long timestamp = (long) (duration_cast<microseconds>(system_clock::now().time_since_epoch())).count();
		printf("got color at:%ld:%d\n", timestamp, pixelColor == result);
		fflush(stdout);
		pixelColor = result;
	}

	return 0;
}





