#pragma once
#include <list>
#include "Car.h"

struct Road
{
	bool active;
	bool crossingA;
	bool crossingB;
	std::list<Car*> _inputA;
	std::list<Car*> _inputB;
	std::list<Car*> _outputA;
	std::list<Car*> _outputB;
};
