// based on: https://github.com/bmharper/WindowsDesktopDuplicationSample

#include "windup.h"
#include "WinDesktopDup.h"
#include <iostream>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace chrono;

WinDesktopDup dup;

void waitForWhite() {
	while (1) {
		int color = dup.GetColorValueAt(5, 5);
		if (color > 0) {
			break;
		}/* else {
			cerr << "color: " << color << endl;
		}*/
	}
}

void SetupDpiAwareness() {
	if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
		cerr << "SetProcessDpiAwarenessContext failed" << endl;
}

int main() {
	//self.start()
	//time.sleep(4.5)
	Sleep(4000);
	SetupDpiAwareness();
	auto err = dup.Initialize();
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
	while (1) {
		SHORT currentState = GetKeyState(VK_LBUTTON);
		if (currentState != state && currentState < 0) {
			state = currentState;

			uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			waitForWhite();
			uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

			Beep(880, 300);
			printf("%d\n", end_time - start_time);
			fflush(stdout);
		}
	}

	return 0;
}





