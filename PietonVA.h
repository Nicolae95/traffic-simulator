#pragma once
#include "Sprite.h"
class PietonVA : public Sprite
{

private:
	bool isActive = false;
public:
	PietonVA(HINSTANCE hInst) : Sprite(hInst, L"assets/audi.bmp", 325, 450, 50, 50) {

	}

	void setActive(bool val) {
		this->isActive = val;
	}


	void virtual render(HWND hwnd, PAINTSTRUCT ps, HDC hdc) override {
		if (isActive) {
			BITMAP 			bitmap;
			HDC 			hdcMem;
			HGDIOBJ 		oldBitmap;

			hdcMem = CreateCompatibleDC(hdc);
			oldBitmap = SelectObject(hdcMem, hBitmap);

			GetObject(hBitmap, sizeof(bitmap), &bitmap);
			BitBlt(hdc, x - width / 2, y - height / 2, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);

			SelectObject(hdcMem, oldBitmap);
			DeleteDC(hdcMem);
		}
	}

	void virtual update() override {

	}

};

