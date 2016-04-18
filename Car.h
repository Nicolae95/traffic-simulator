#pragma once

enum Direction
{
	LEFT = 0,RIGHT = 1,FRONT = 2
};

class Car
{
public:
	Direction direction;
	bool animateAparition;
	Car();
};

