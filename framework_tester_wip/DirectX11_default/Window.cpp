#include "Window.h"


bool pressed = false;

LRESULT CALLBACK WinProc(HWND handle, UINT msg, WPARAM wparam, LPARAM lparam) {
	if (msg == WM_DESTROY ||
		msg == WM_CLOSE) {
		PostQuitMessage(0);
		return 0;
	}

	if (msg == WM_LBUTTONDOWN) {
		pressed = true;
	} else if (msg == WM_LBUTTONUP) {
		pressed = false;
	}

	return DefWindowProc(handle, msg, wparam, lparam);
}

Window::Window(int width, int height) {
	// Define window style
	WNDCLASS wc = { 0 };
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WinProc;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.lpszClassName = "DX11Tutorial";
	RegisterClass(&wc);

	// Create the window
	m_handle = CreateWindow("DX11Tutorial", "C++11 and DX11 Tutorial",
		WS_POPUP | WS_VISIBLE,
		0, 0, width, height,
		nullptr, nullptr, nullptr, nullptr);
}

HWND Window::getHandle() {
	return m_handle;
}

