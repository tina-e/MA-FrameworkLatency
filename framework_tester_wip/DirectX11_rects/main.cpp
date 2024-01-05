#include <Windows.h>
#include "Window.h"
#include "Renderer.h"
#include "Rect.h"

int CALLBACK WinMain(HINSTANCE appInstance, HINSTANCE prevInstance, LPSTR cmdLine, int cmdCount) {

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	Window window(width, height);
	Renderer renderer(window);
	Rect rect(renderer);

	MSG msg = { 0 };
	while (true) {
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (msg.message == WM_QUIT) {
				break;
			}
		}

		renderer.beginFrame();
		if (pressed) {
			rect.draw(renderer);
		}		
		renderer.endFrame();
	}

	return 0;
}
