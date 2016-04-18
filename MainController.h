#pragma once
#include "stdafx.h"
#include "resource.h"
#include <vector>

#include "Sprite.h"
#include "BackGroundObject.h"
#include "CarObjectA.h"
#include "CarObjectB.h"
#include "CarObjectC.h"
#include "CarObjectD.h"
#include "TrafficLightObject.h"

class MainController
{
private:
	LPCWSTR path = L"assets/audi.bmp";
	vector<Sprite*> sprites;
	HINSTANCE hInst;
	HWND hwnd;
	TrafficLightObject *HtrafficLight;
	TrafficLightObject *VtrafficLight;
	void Setups() {
		///Set the brackground..
		sprites.push_back(new BackGroundObject(hInst, L"assets/map.bmp", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 650, 650));


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

	void createDcar()
	{

		Sprite* car = new CarObjectD(hInst, path);
		((CarObjectD*)car)->go();
		sprites.push_back(car);
	}

	void createCcar()
	{

		Sprite* car = new CarObjectC(hInst, path);
		((CarObjectC*)car)->go();
		sprites.push_back(car);
	}

	void createAcar()
	{
		Sprite* car = new CarObjectA(hInst, path);
		((CarObjectA*)car)->go();
		sprites.push_back(car);
	}

	void createBcar() {
		Sprite* car = new CarObjectB(hInst, path);
		((CarObjectB*)car)->go();
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

