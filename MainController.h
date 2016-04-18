#pragma once
#include "stdafx.h"
#include "resource.h"
#include <vector>

#include "Sprite.h"
#include "BackGroundObject.h"
#include "TrafficLightObject.h"
#include "CarObjectA.h"
#include "CarObjectB.h"
#include "CarObjectC.h"
#include "CarObjectD.h"
#include "CarObjectAO.h"
#include "CarObjectBO.h"
#include "CarObjectCO.h"
#include "CarObjectDO.h"
#include "PietonHA.h"
#include "PietonHB.h"
#include "PietonVA.h"
#include "PietonVB.h"


class MainController
{
private:
	LPCWSTR path = L"assets/audi.bmp";
	vector<Sprite*> sprites;
	vector<Sprite*> scenObjects;
	HINSTANCE hInst;
	HWND hwnd;
	TrafficLightObject *HtrafficLight;
	TrafficLightObject *VtrafficLight;
	PietonHA *PHA;
	PietonHB *PHB;
	PietonVA *PVA;
	PietonVB *PVB;
	

	void pietonRender(PAINTSTRUCT ps, HDC hdc) {
		PHA->render(hwnd, ps, hdc);
		PHB->render(hwnd, ps, hdc);
		PVA->render(hwnd, ps, hdc);
		PVB->render(hwnd, ps, hdc);
	}

	void Setups() {
		///Set the brackground..
		scenObjects.push_back(new BackGroundObject(hInst, L"assets/map.bmp", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 650, 650));
		
		
		//Set pieton....
		PHA = new PietonHA(hInst);
		PHB = new PietonHB(hInst);
		PVA = new PietonVA(hInst);
		PVB = new PietonVB(hInst);

		//Setup Traffic Lights
		TrafficLightObject *Vtemp;
		TrafficLightObject *Htemp;

		Vtemp = new TrafficLightObject(hInst, 170, 180);
		
		VtrafficLight = new TrafficLightObject(hInst, 480, 480);
		VtrafficLight->setSecond(Vtemp);
		VtrafficLight->setInitialCollorTrue();
		scenObjects.push_back(VtrafficLight);
		scenObjects.push_back(Vtemp);


		Htemp = new TrafficLightObject(hInst, 170, 480);

		HtrafficLight = new TrafficLightObject(hInst, 480, 180);
		HtrafficLight->setSecond(Htemp);

		scenObjects.push_back(HtrafficLight);
		scenObjects.push_back(Htemp);
		switchTraficLightColor();

	}

public:
	MainController(HINSTANCE hinst,HWND hwnd) {
		this->hInst = hinst;
		Setups();
	}

	//PietonActivators
	void setPHA(bool val) {
		PHA->setActive(val);
	}

	void setPHB(bool val) {
		PHB->setActive(val);
	}

	void setPVA(bool val) {
		PVA->setActive(val);
	}

	void setPVB(bool val) {
		PVB->setActive(val);
	}

	/////Input..............................................

	void createDcar(bool leftLight, bool rightLight,bool animate)
	{
		Sprite* car = new CarObjectD(hInst, path);
		((CarObjectD*)car)->turnLeft(leftLight);
		((CarObjectD*)car)->turnRight(rightLight);
		((CarObjectD*)car)->setAnimate(animate);
		((CarObjectD*)car)->go();
		sprites.push_back(car);
	}

	void createCcar(bool leftLight, bool rightLight, bool animate)
	{
		Sprite* car = new CarObjectC(hInst, path);
		((CarObjectC*)car)->turnLeft(leftLight);
		((CarObjectC*)car)->turnRight(rightLight);
		((CarObjectC*)car)->setAnimate(animate);
		((CarObjectC*)car)->go();
		sprites.push_back(car);
	}

	void createAcar(bool leftLight, bool rightLight, bool animate)
	{
		Sprite* car = new CarObjectA(hInst, path);
		((CarObjectA*)car)->turnLeft(leftLight);
		((CarObjectA*)car)->turnRight(rightLight);
		((CarObjectA*)car)->setAnimate(animate);
		((CarObjectA*)car)->go();
		sprites.push_back(car);
	}

	void createBcar(bool leftLight, bool rightLight, bool animate) {
		Sprite* car = new CarObjectB(hInst, path);
		((CarObjectB*)car)->turnLeft(leftLight);
		((CarObjectB*)car)->turnRight(rightLight);
		((CarObjectB*)car)->setAnimate(animate);
		((CarObjectB*)car)->go();
		sprites.push_back(car);
	}


	/////Output ................................

	void createDOcar(bool leftLight, bool rightLight)
	{
		Sprite* car = new CarObjectDO(hInst, path);
		((CarObjectDO*)car)->turnLeft(leftLight);
		((CarObjectDO*)car)->turnRight(rightLight);
		((CarObjectDO*)car)->go();
		sprites.push_back(car);
	}

	void createCOcar(bool leftLight, bool rightLight)
	{
		Sprite* car = new CarObjectCO(hInst, path);
		((CarObjectCO*)car)->turnLeft(leftLight);
		((CarObjectCO*)car)->turnRight(rightLight);
		((CarObjectCO*)car)->go();
		sprites.push_back(car);
	}

	void createAOcar(bool leftLight, bool rightLight)
	{
		Sprite* car = new CarObjectAO(hInst, path);
		((CarObjectAO*)car)->turnLeft(leftLight);
		((CarObjectAO*)car)->turnRight(rightLight);
		((CarObjectAO*)car)->go();
		sprites.push_back(car);
	}

	void createBOcar(bool leftLight, bool rightLight) {
		Sprite* car = new CarObjectBO(hInst, path);
		((CarObjectBO*)car)->turnLeft(leftLight);
		((CarObjectBO*)car)->turnRight(rightLight);
		((CarObjectBO*)car)->go();
		sprites.push_back(car);
	}

	

	void removeAllCars() {
		sprites.clear();
	}
	

	void switchTraficLightColor() {
		VtrafficLight->switchColor();
		HtrafficLight->switchColor();
	}

	void sceneObjectsRender(PAINTSTRUCT ps, HDC hdc) {
		
		for (std::vector<Sprite*>::iterator scenObject = scenObjects.begin(); scenObject != scenObjects.end(); ++scenObject) {
			(*scenObject)->render(hwnd, ps, hdc);
		}
	}

	void render(PAINTSTRUCT ps,HDC hdc) {
		sceneObjectsRender(ps, hdc);
		pietonRender(ps,hdc);
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

