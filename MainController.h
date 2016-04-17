#pragma once
#include <vector>
#include "Sprite.h"
#include "CarObject.h"
#include "resource.h"

class MainController
{
private:
	vector<Sprite*> sprites;
	HINSTANCE hInst;
	HWND hwnd;
public:
	MainController(HINSTANCE hinst,HWND hwnd) {
		this->hInst = hinst;
	}

	void setBackGorund() {
		Sprite *backgorund = new CarObject(hInst, L"assets/map.bmp", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 650, 650);
		sprites.push_back(backgorund);
	};

	void generateRandomCar() {
		Sprite* car = new CarObject(hInst, L"assets/Audi.bmp", 100, 100, 100, 100);
		((CarObject*)car)->setVelocity(1, 1);
		sprites.push_back(car);
	}

	void render(PAINTSTRUCT ps,HDC hdc) {
		for (std::vector<Sprite*>::iterator sprite = sprites.begin(); sprite != sprites.end(); ++sprite) {
			(*sprite)->render(hwnd, ps, hdc);
		}
	}

	void update() {
		for (std::vector<Sprite*>::iterator sprite = sprites.begin(); sprite != sprites.end(); ++sprite) {
			(*sprite)->update();
		}
	}
};

