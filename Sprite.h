#pragma once
#include <iostream>
using namespace std;

class Sprite
{
protected:
	int x;
	int y;
	int width;
	int height;
	HBITMAP hBitmap;
public:
	Sprite(HINSTANCE hInst, LPCWSTR path, int x, int y, int width, int height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		hBitmap = (HBITMAP)LoadImage(hInst, path, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	};

	void virtual render(HWND hwnd, PAINTSTRUCT ps, HDC hdc ) {}
	
	virtual void update() = 0;
};

