#include "windup.h"
#include "WinDesktopDup.h"
#include <iostream>
#include <chrono>
#include <windows.h>

using namespace std;
using namespace chrono;

WinDesktopDup dup;

void waitForWhite() {
	//uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	////cout << "start waiting" << endl;
	//while (1) {
	//	//uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	//	int      color      = dup.GetColorValueAt(5, 5);
	//	//cout << color << endl;
	//	//cout << "color: " << color << endl;
	//	//
	//	/*if (color != 0) {
	//		cout << "color: " << color << endl;
	//	}*/
	//	
	//	if (color == 255) {
	//		//cout << "WHITEEEEEEEEEEEEEEEEEEEEEEE" << endl;
	//		uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	//		cout << end_time - start_time << endl;
	//		return;
	//	} else if ((duration_cast<microseconds>(system_clock::now().time_since_epoch()).count()) - start_time > 5000000) {
	//		//cout << "5s um" << endl;
	//		cout << -1 << endl;
	//		return;
	//	}

	//	//uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	//	//cout << end_time - start_time << endl;
	//	//if (color == 255) {
	//	//	cout << "color: " << color << "########################################################" << endl;
	//	//}
		
	//}
	
	while (1) {
		//uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		int color = dup.GetColorValueAt(5, 5);
		
		//
		/*if (color != 0) {
			cout << "color: " << color << endl;
		}*/

		if (color == 255) {
			break;
		} else {
			cerr << "color: " << color << endl;
		}

		//uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
		//cout << end_time - start_time << endl;
		//if (color == 255) {
		//	cout << "color: " << color << "########################################################" << endl;
		//}
	}
}

void SetupDpiAwareness() {
	if (!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
		cerr << "SetProcessDpiAwarenessContext failed" << endl;
}

int main() {
	/* HWND frameworkWindow = FindWindow(NULL, L"framework");
	if (frameworkWindow != NULL) {
		BringWindowToTop(frameworkWindow);
		SetForegroundWindow(frameworkWindow);
		ShowWindow(frameworkWindow, SW_RESTORE);
		SetFocus(frameworkWindow);
	} else {
		cerr << "no window named framework" << endl;
	}*/

	LONGLONG start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
	cerr << start_time << endl;

	start_time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
	cerr << start_time << endl;

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

	
	SHORT state = GetKeyState(VK_LBUTTON);

	//bool readerInitialized = false;
	//while (!readerInitialized) {
	//	SHORT currentState = GetKeyState(VK_LBUTTON);
	//	if (currentState != state && currentState < 0) {
	//		state = currentState;
	//		// init white: start as soon as first time white recognized
	//		waitForWhite();
	//		Beep(600, 300);
	//		readerInitialized = true;
	//		printf("%d\n", -1);
	//		fflush(stdout);
	//	}
	//}
	//readerInitialized = false;
	//while (!readerInitialized) {
	//	SHORT currentState = GetKeyState(VK_LBUTTON);
	//	if (currentState != state && currentState < 0) {
	//		state = currentState;
	//		// init white: start as soon as first time white recognized
	//		waitForWhite();
	//		Beep(700, 300);
	//		readerInitialized = true;
	//		printf("%d\n", -1);
	//		fflush(stdout);
	//	}
	//}
	//readerInitialized = false;
	//while (!readerInitialized) {
	//	SHORT currentState = GetKeyState(VK_LBUTTON);
	//	if (currentState != state && currentState < 0) {
	//		state = currentState;
	//		// init white: start as soon as first time white recognized
	//		waitForWhite();
	//		Beep(800, 300);
	//		readerInitialized = true;
	//		printf("%d\n", -1);
	//		fflush(stdout);
	//	}
	//}

	while (1) {
		SHORT currentState = GetKeyState(VK_LBUTTON);
		if (currentState != state && currentState < 0) {
			state = currentState;

			//waitForWhite();
			////uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			////cout << end_time - start_time << endl;
			uint64_t start_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			waitForWhite();
			uint64_t end_time = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
			Beep(880, 300);
			cerr << start_time << endl;
			cerr << end_time << endl;
			printf("%d\n", end_time - start_time);
			fflush(stdout);
			//cout << end_time - start_time << endl;
			//Beep(1000, 100);
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





