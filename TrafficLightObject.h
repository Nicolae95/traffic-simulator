#pragma once
#include "Sprite.h"

class TrafficLightObject : public Sprite
{
private:
	bool isGreen = false;
	TrafficLightObject *second = NULL;
public:

	TrafficLightObject(HINSTANCE hInst, int x, int y) : Sprite(hInst,L"assets/Audi.bmp",x,y,80,50) {
		
	}

	void render(HWND hwnd, PAINTSTRUCT ps, HDC hdc) override {
		
		
		if (isGreen) {
			SelectObject(hdc, CreateSolidBrush(RGB(0,255,0)));
		}
		else {
			SelectObject(hdc, CreateSolidBrush(RGB(255, 0, 0)));
		}
		
			int size = 20;
			
			int left = x - 20;
			int top = y - 20;
			int right = x + 20;
			int bottom = y + 20;

			Ellipse(hdc, left, top, right, bottom);		
	}

	void setInitialCollorTrue() {
		isGreen = true;
		if(second)
			second->switchColor();
	}

	virtual void update() override {
		
	}

	void setSecond(TrafficLightObject *second) {
		this->second = second;
	}
	void switchColor() {
		isGreen = !isGreen;
		if (second)
			second->switchColor();
	}
};

