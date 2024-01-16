#include "windup.h"
#include "WinDesktopDup.h"
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

WinDesktopDup dup;

void waitForWhite() {
	while (dup.GetColorValueAt(5, 5) != 255) {
		Sleep(1);
	}
}

void SetupDpiAwareness() {
	if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
		cout << "SetProcessDpiAwarenessContext failed" << endl;
}

int main() {
	SetupDpiAwareness();
	auto err = dup.Initialize();

	SHORT state = GetKeyState(VK_LBUTTON);

	while (true) {
		SHORT currentState = GetKeyState(VK_LBUTTON);
		if (currentState != state && currentState < 0) {
			state = currentState;
			uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			waitForWhite();
			uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			cout << end_time - start_time << endl;
		}
	}

	/*while (1) {
		int redValue = dup.GetColorValueAt(5, 5);
		if (redValue != -1 && dup.HaveFrameLock) {
			cerr << redValue << endl;
		}
	}*/
	return 0;
}





