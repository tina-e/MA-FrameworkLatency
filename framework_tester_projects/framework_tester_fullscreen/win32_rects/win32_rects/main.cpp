#include <Windows.h>
#include <stdint.h>
#include <iostream>
#include <random>

const int WIDTH = GetSystemMetrics(SM_CXSCREEN);
const int HEIGHT = GetSystemMetrics(SM_CYSCREEN);
const int NUM_RECTS = 999;
bool isPressed = false;
RECT rects[1000] = {};
COLORREF colors[1000] = {};


int randint(int low, int high)
{
    return low + rand() % (high - low);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
    {
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
    }
    break;
    case WM_PAINT: {
        if (isPressed) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            for (int i = 0; i < NUM_RECTS+1; i++) {
                Rectangle(hdc, rects[i].left, rects[i].top, rects[i].right, rects[i].bottom);
                HBRUSH hBrush = CreateSolidBrush(colors[i]);
                HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
                FillRect(hdc, &rects[i], hBrush);
                SelectObject(hdc, hOldBrush);
                DeleteObject(hBrush);
            }
            EndPaint(hWnd, &ps);
        }
        
    }
    break;
    case WM_LBUTTONDOWN:
    {
        isPressed = true;
        for (int i = 0; i < NUM_RECTS; i++) {
            int w = randint(100, 500);
            int h = randint(100, 500);
            int x = randint(100, WIDTH - w);
            int y = randint(0, HEIGHT - h);
            int r = randint(0, 255);
            int g = randint(0, 255);
            int b = randint(0, 255);

            rects[i] = { x, y, x+w, y+h };
            colors[i] = RGB(r, g, b);
        }
        rects[999] = { 0, 0, 100, 100 };
        colors[999] = RGB(255, 255, 255);

        RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
    }
    break;
    case WM_LBUTTONUP:
    {
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
        RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
        isPressed = false;
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"framework";
    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0, L"framework", L"framework", WS_POPUP, 0, 0, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
    if (!hWnd) return 0;
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


