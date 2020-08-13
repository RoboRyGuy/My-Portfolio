#pragma once

#include "Windows.h"
#include <string>

using std::string;

ATOM registerWindows(HINSTANCE hInstance);
INT createAndMaintainWindow(HINSTANCE hInstance, ATOM wndAtom);
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);