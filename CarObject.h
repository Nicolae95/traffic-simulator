#pragma once
#include "Sprite.h"

class CarObject : public Sprite
{
private:
	int vX;
	int vY;

public:
	CarObject(HINSTANCE hInst, LPCWSTR path, int x, int y, int width, int height) : Sprite(hInst,path,x,y,width,height) {

	}

	void setVelocity(int x, int y) {
		this->vX = x;
		this->vY = y;
	}

	virtual void update() override {
		x += vX;
		y += vY;
	}
};

