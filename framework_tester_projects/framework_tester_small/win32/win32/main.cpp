#include <Windows.h>
#include <stdint.h>
#include <iostream>

int width = 100;
int height = 100;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        SetBkColor(hdc, RGB(0, 0, 0));
        EndPaint(hWnd, &ps);
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_LBUTTONDOWN:
    {
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(255, 255, 255)));
        RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
    }
    break;
    case WM_LBUTTONUP:
    {
        SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(0, 0, 0)));
        RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_INVALIDATE);
    }
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"framework";

    RegisterClass(&wc);

    HWND hWnd = CreateWindowEx(0, L"framework", L"framework", WS_POPUP, 0, 0, width, height, NULL, NULL, hInstance, NULL);
    if (!hWnd) return 0;
    ShowWindow(hWnd, nCmdShow);

    MSG msg = { 0 };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}