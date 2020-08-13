// This file includes all the boring startup n stuff
#include "Dependencies.h"
#include <iostream>

using std::cout;

// Shell function, starts and ends program
INT main(HINSTANCE hInstance) {
    ATOM wndAtom = registerWindows(hInstance);
    INT returnValue = createAndMaintainWindow(hInstance, wndAtom);
    cout << "\n\nReturn Value: " << returnValue;
    getchar();
    return returnValue;
}

ATOM registerWindows(HINSTANCE hInstance) {
    const char CLASS_NAME[] = "Main";

    WNDCLASSEX wc = { };

    wc.lpszClassName = CLASS_NAME;      // Name of the class
    wc.lpfnWndProc = MainWndProc;       // Window Procedure
    wc.hInstance = hInstance;           // The instance of this program

    wc.lpszMenuName = NULL;				// Name of the menu, of which we have none
    wc.cbSize = sizeof(WNDCLASSEX);		// Size of the class
    wc.cbClsExtra = 0;					// Extra bytes allocated after this structure
    wc.cbWndExtra = 0;					// Extra bytes allocated after each instance
    wc.style = CS_HREDRAW | CS_VREDRAW;	// Some special window properties
    wc.hbrBackground = HBRUSH(2);		// BG color
    wc.hIcon = NULL;					// An icon for this window. We're using a default right now
    wc.hIconSm = NULL;					// A small icon for this window. Windows will autosearch right now
    wc.hCursor = NULL;					// The cursor we use. We've set to have it explicitly define each update

    ATOM wndAtom = RegisterClassEx(&wc);
    // Put error checking here
    return wndAtom;
}

INT createAndMaintainWindow(HINSTANCE hInstance, ATOM wndAtom) {
    // First we'll calculate the size of this window
    const unsigned int WIDTH = 1280, HEIGHT = 720;
    const long WINSTYLE = WS_SYSMENU | WS_CAPTION;

    RECT area;
    area.top = 0;
    area.left = 0;
    area.bottom = HEIGHT;
    area.right = WIDTH;

    AdjustWindowRect(
        &area,
        WINSTYLE,
        FALSE
    );

    HWND hwnd = CreateWindowEx(
        0,				        // Optional window class styles
        MAKEINTATOM(wndAtom),	// Which class to make
        "Crimson Loop",	        // Title bar name
        WINSTYLE,		        // Window styles

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT,
        area.right - area.left, area.bottom - area.top,

        NULL,		// Parent Window
        NULL,		// Menu
        hInstance,	// Instance handle
        NULL		// Additional application data
    );

    if (hwnd == NULL) {
        // Error handling here
        return 1;
    }

    ShowWindow(hwnd, 1);

    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    DestroyWindow(hwnd);

    return msg.wParam;
}