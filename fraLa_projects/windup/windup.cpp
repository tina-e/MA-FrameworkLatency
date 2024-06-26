// based on: https://github.com/bmharper/WindowsDesktopDuplicationSample

#include "windup.h"
#include "WinDesktopDup.h"
#include <iostream>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace chrono;

WinDesktopDup dup;

void waitForChange() {
	while (1) {
		int color = dup.GetColorValueAt(5, 5);
		if (color > 0) {
			break;
		}
	}
}

void SetupDpiAwareness() {
	if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
		cerr << "SetProcessDpiAwarenessContext failed" << endl;
}

int main() {
	SetupDpiAwareness();
	auto err = dup.Initialize();

	SHORT state = GetKeyState(VK_LBUTTON);
	while (1) {
		SHORT currentState = GetKeyState(VK_LBUTTON);
		if (currentState != state && currentState < 0) {
			state = currentState;

			uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			waitForChange();
			uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();

			printf("%d\n", end_time - start_time);
			fflush(stdout);
		}
	}

	return 0;
}





