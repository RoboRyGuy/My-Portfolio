// Start
// Define main class, instantiate, maintain

#include <iostream>
#include "Windows.h"

extern LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int main(HINSTANCE hInstance) {
	WNDCLASS wc = { };

	wc.lpszClassName = "Main";
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;

	RegisterClass(&wc);

	// Create the window
	HWND hwnd = CreateWindowEx(
		0,
		"Main",
		"Cat Petter 9000",
		WS_OVERLAPPEDWINDOW,

		// Size and pos
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL) {
		std::cout << "Failed";
	system("pause");
		return 1;
	}

	ShowWindow(hwnd, 1);

	MSG msg = { };
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}


	return msg.wParam;


}