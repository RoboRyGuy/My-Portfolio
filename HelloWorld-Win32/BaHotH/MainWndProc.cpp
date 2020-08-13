#include "Dependencies.h"

LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_ACTIVATE: {
    }
                      break;

    case WM_TIMER: {
    }
                   break;

    case WM_PAINT: {
        PAINTSTRUCT pc;
        HDC hdcMain = BeginPaint(hwnd, &pc);
        SetBkColor(hdcMain, RGB(0, 0, 0));
        SetTextColor(hdcMain, RGB(255, 255, 255));
        TextOut(hdcMain, 20, 20, "Hello world", 11);
        EndPaint(hwnd, &pc);
        return 1;
    }
                   break;

    case WM_DESTROY:
    case WM_CLOSE: {
        PostQuitMessage(0);
        return 0;
    }
                    break;

    default: {
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
                    break;
    }
}