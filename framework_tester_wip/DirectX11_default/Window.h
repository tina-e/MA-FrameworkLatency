#pragma once

#include <Windows.h>

extern bool pressed;

class Window {
public:
	Window(int width, int height);
	HWND getHandle();

private:
	HWND m_handle;
};
