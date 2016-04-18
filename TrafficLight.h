#pragma once
#include "Sprite.h"

class TrafficLight : public Sprite
{
	bool isActive;
	TrafficLight *second;
public:
	TrafficLight(HINSTANCE hInst, LPCWSTR path, int x, int y, int width, int height) : Sprite(hInst,path,x,y,width,height) {
		this->second = second
	}
	
};

