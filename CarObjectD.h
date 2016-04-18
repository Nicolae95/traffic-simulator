#pragma once
#include "Sprite.h"

class CarObjectD : public Sprite
{
private:
	bool animate = false;
	int notIntersectoin = 500;
	int vX;
	int vY;
	bool leftLight = false;
	bool rightLight = false;
public:
	
	CarObjectD(HINSTANCE hInst, LPCWSTR path) : Sprite(hInst, path, 580, 280, 70, 50) { }

	void setAnimate(bool val) {
		this->animate = val;
	}

	void virtual render(HWND hwnd, PAINTSTRUCT ps, HDC hdc) {
		BITMAP 			bitmap;
		HDC 			hdcMem;
		HGDIOBJ 		oldBitmap;

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, hBitmap);

		GetObject(hBitmap, sizeof(bitmap), &bitmap);
		BitBlt(hdc, x - width / 2, y - height / 2, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, SRCCOPY);
		if (leftLight)
			LeftLight(hdc);
		if (rightLight)
			RightLight(hdc);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);
	}

	void turnLeft(bool val) {
		leftLight = val;
	}

	void turnRight(bool val) {
		rightLight = val;
	}


	void switchOffLights() {
		leftLight = rightLight = false;
	}

	void LeftLight(HDC hdc) {
		SelectObject(hdc, CreateSolidBrush(RGB(255, 165, 0)));
		int size = 5;

		int left = x - width / 2 - size;
		int top = y - width / 2 + size;
		int right = x - height / 2 - size;
		int bottom = y - height / 2 + size;

		Ellipse(hdc, left, top, right, bottom);



		left = x + width / 2 + size;
		top = y - width / 2 + size;
		right = x + height / 2 + size;
		bottom = y - height / 2 + size;

		Ellipse(hdc, left, top, right, bottom);


	}

	void RightLight(HDC hdc) {
		SelectObject(hdc, CreateSolidBrush(RGB(255, 165, 0)));
		int size = 5;
		int left = x + width / 2 + size;
		int top = y + width / 2 - size;
		int right = x + height / 2 + size;
		int bottom = y + height / 2 - size;

		Ellipse(hdc, left, top, right, bottom);

		left = x - width / 2 - size;
		top = y + width / 2 - size;
		right = x - height / 2 - size;
		bottom = y + height / 2 - size;

		Ellipse(hdc, left, top, right, bottom);
	}

	void setVelocity(int x, int y) {
		this->vX = x;
		this->vY = y;
	}

	virtual void update() override {
		if (x != notIntersectoin) {
			x += vX;
			y += vY;
		}
		
	}

	void go() {
		if (animate)
			this->setVelocity(-2, 0);
		else
			x = notIntersectoin;
	}

};

