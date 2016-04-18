#pragma once
#include "stdafx.h"
#include "resource.h"
#include <vector>

#include "Sprite.h"
#include "CarObject.h"
#include "TrafficLightObject.h"

class MainController
{
private:
	vector<Sprite*> sprites;
	HINSTANCE hInst;
	HWND hwnd;
	TrafficLightObject *HtrafficLight;
	TrafficLightObject *VtrafficLight;
	void Setups() {
		///Set the brackground..
		sprites.push_back(new CarObject(hInst, L"assets/map.bmp", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 650, 650));


		//Setup Traffic Lights
		TrafficLightObject *Vtemp;
		TrafficLightObject *Htemp;

		Vtemp = new TrafficLightObject(hInst, 170, 180);
		
		VtrafficLight = new TrafficLightObject(hInst, 480, 480);
		VtrafficLight->setSecond(Vtemp);
		VtrafficLight->setInitialCollorTrue();
		sprites.push_back(VtrafficLight);
		sprites.push_back(Vtemp);


		Htemp = new TrafficLightObject(hInst, 170, 480);

		HtrafficLight = new TrafficLightObject(hInst, 480, 180);
		HtrafficLight->setSecond(Htemp);

		sprites.push_back(HtrafficLight);
		sprites.push_back(Htemp);
		switchTraficLightColor();
	}

public:
	MainController(HINSTANCE hinst,HWND hwnd) {
		this->hInst = hinst;
		Setups();
	}


	void generateRandomCar(int x, int y) {
		LPCWSTR path;
		switch (rand() % 5) {
		case 0:
			path = L"assets/Audi.bmp";
			break;
		case 1:
			path = L"assets/Audi.bmp";
			break;
		case 2:
			path = L"assets/Audi.bmp";
			break;
		case 3:
			path = L"assets/Audi.bmp";
			break;
		case 4:
			path = L"assets/Audi.bmp";
			break;
		default:
			path = L"assets/Audi.bmp";
			break;
		}

		Sprite* car = new CarObject(hInst, path, x, y, 50, 70);
		((CarObject*)car)->setVelocity(0, -1);
		sprites.push_back(car);
	}

	void switchTraficLightColor() {
		VtrafficLight->switchColor();
		HtrafficLight->switchColor();
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

