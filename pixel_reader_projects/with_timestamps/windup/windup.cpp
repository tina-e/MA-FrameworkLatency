// based on: https://github.com/bmharper/WindowsDesktopDuplicationSample

#include "windup.h"
#include "WinDesktopDup.h"
#include <iostream>
#include <chrono>
#include <list>
#include <fstream>
#include <windows.h>

using namespace std;
using namespace chrono;

WinDesktopDup dup;

list<uint64_t> queryColor;
list<uint64_t> white;


void SetupDpiAwareness() {
	if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
		cerr << "SetProcessDpiAwarenessContext failed" << endl;
}

int main(int argc, char* argv[]) {
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

	int   iteration = 0;
	//waitForWhite();
	while (iteration <= 210) {
		int color = dup.GetColorValueAt(5, 5);
		queryColor.push_back(duration_cast<microseconds>(system_clock::now().time_since_epoch()).count());
		if (color == 255) {
			white.push_back(duration_cast<microseconds>(system_clock::now().time_since_epoch()).count());
			iteration++;
		}
	}

	Beep(500, 2000);
	string fwName = argv[1];
	std::ofstream outfileQueryColor;
	string        filename = fwName.append("_queryColor.csv");
	outfileQueryColor.open(filename);
	for (const auto& item : queryColor) {
		outfileQueryColor << item << "\n";
	}
	outfileQueryColor.close();

	fwName = argv[1];
	std::ofstream outfileWhite;
	filename = fwName.append("_white.csv");
	outfileWhite.open(filename);
	for (const auto& item : white) {
		outfileWhite << item << "\n";
	}
	outfileWhite.close();

	return 0;
}

