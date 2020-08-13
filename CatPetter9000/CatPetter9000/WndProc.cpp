// Window Procedure for Main

#include <iostream>
#include "Windows.h"
#include <math.h>

HBITMAP
    CatAndBG,
    CatMask,
    Hand,
    HandMask;

int handX = 0, handY = 0;
double time = 0;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_CREATE: {
		// Let's just start with the timer
		SetTimer(hwnd, 1, 10, NULL);

		CatAndBG = (HBITMAP)LoadImage(NULL, "C:\\Users\\joe\\Downloads\\CatAndBg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);
		if (CatAndBG == NULL) {
			std::cout << "Cat was null";
			std::cout << GetLastError();
		}

		Hand = (HBITMAP)LoadImage(NULL, "C:\\Users\\joe\\Downloads\\Hand.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR);

		if (Hand == NULL) {
			std::cout << "Hand was null";
			std::cout << GetLastError();
		}

		BITMAP infoMap;

		// Create masks //
		GetObject(CatAndBG, sizeof(BITMAP), &infoMap);
		CatMask = CreateBitmap(infoMap.bmWidth, infoMap.bmHeight, 1, 1, NULL);

		// Get some DCs
		HDC imageDC = CreateCompatibleDC(0);
		HDC maskDC = CreateCompatibleDC(0);

		// Setup those DCs
		HGDIOBJ oldImage = SelectObject(imageDC, CatAndBG);
		HGDIOBJ oldMask = SelectObject(maskDC, CatMask);

		// Set our background color
		SetBkColor(imageDC, RGB(0, 0, 0));

		// Math magic
		BitBlt(maskDC, 0, 0, infoMap.bmWidth, infoMap.bmHeight, imageDC, 0, 0, SRCCOPY);
		BitBlt(imageDC, 0, 0, infoMap.bmWidth, infoMap.bmWidth, maskDC, 0, 0, SRCINVERT);

		// Start again, but with the hand
		GetObject(Hand, sizeof(BITMAP), &infoMap);
		HandMask = CreateBitmap(infoMap.bmWidth, infoMap.bmHeight, 1, 1, NULL);

		// Setup the DCs
		SelectObject(imageDC, Hand);
		SelectObject(maskDC, HandMask);

		// Set our background color
		SetBkColor(imageDC, RGB(0, 0, 0));

		// More math magic
		BitBlt(maskDC, 0, 0, infoMap.bmWidth, infoMap.bmHeight, imageDC, 0, 0, SRCCOPY);
		BitBlt(imageDC, 0, 0, infoMap.bmWidth, infoMap.bmWidth, maskDC, 0, 0, SRCINVERT);

		// Cleanup
		SelectObject(imageDC, oldImage);
		SelectObject(maskDC, oldMask);
		DeleteDC(imageDC);
		DeleteDC(maskDC);
	}
					break;


	case WM_TIMER: {
		time += .04;

		handX = 30 * -std::sin(time);
		handY = 20 * std::sin(time) + 10;

		InvalidateRect(hwnd, NULL, TRUE);
	}
				   break;



	case WM_CLOSE:
	case WM_DESTROY: {
		PostQuitMessage(0);
	}
					 break;


	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		// Buffer, I guess
		HDC bufferDC = CreateCompatibleDC(hdc);
		HBITMAP bufferBitmap = CreateCompatibleBitmap(hdc, 1280, 720);
		HGDIOBJ oldBitmap = SelectObject(bufferDC, bufferBitmap);

		// Background
		Rectangle(bufferDC, 0, 0, 1280, 720);

		// Here we do the actual drawing
		// We want to draw in the middle of the screen, so position -> offset
		HDC hdcMem = CreateCompatibleDC(bufferDC);
		BITMAP infoMap;

		// Cat first
		GetObject(CatAndBG, sizeof(BITMAP), &infoMap);
		HGDIOBJ memBitmap = SelectObject(hdcMem, CatMask); // Gotta track that one bitmap
		BitBlt(bufferDC, 640 - infoMap.bmWidth / 2, 360 - infoMap.bmHeight / 2, 
			infoMap.bmWidth, infoMap.bmWidth,
			hdcMem, 0, 0, SRCAND);

		SelectObject(hdcMem, CatAndBG);
		BitBlt(bufferDC, 640 - infoMap.bmWidth / 2, 360 - infoMap.bmHeight / 2,
			infoMap.bmWidth, infoMap.bmWidth,
			hdcMem, 0, 0, SRCPAINT);


		// Then the hand
		GetObject(Hand, sizeof(BITMAP), &infoMap);
		SelectObject(hdcMem, HandMask);
		BitBlt(bufferDC, 640 - infoMap.bmWidth / 2 + handX, 360 - infoMap.bmHeight / 2 + handY,
			infoMap.bmWidth, infoMap.bmWidth,
			hdcMem, 0, 0, SRCAND);

		SelectObject(hdcMem, Hand);
		BitBlt(bufferDC, 640 - infoMap.bmWidth / 2 + handX, 360 - infoMap.bmHeight / 2 + handY,
			infoMap.bmWidth, infoMap.bmWidth,
			hdcMem, 0, 0, SRCPAINT);

		SelectObject(hdcMem, memBitmap);
		DeleteDC(hdcMem);


		// Cleanup
		BitBlt(hdc, 0, 0, 1280, 720, bufferDC, 0, 0, SRCCOPY);
		SelectObject(hdc, oldBitmap);
		DeleteDC(bufferDC);
		EndPaint(hwnd, &ps);

	}
				   break;


	default: { // Fall-through
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
			 break;

	}

	// If, somehow, we make it here
	return 0;
}