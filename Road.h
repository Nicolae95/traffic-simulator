#pragma once
#include <list>
#include "Car.h"

class Road
{
public:
	bool active;
	bool crossingA;
	bool crossingB;
	std::list<Car*> _inputA;
	std::list<Car*> _inputB;
	std::list<Car*> _outputA;
	std::list<Car*> _outputB;

	Road()
	{
		for(int i =0 ; i < 2;i++)
		{
			_inputA.push_back(NULL);
			_inputB.push_back(NULL);
			_outputA.push_back(NULL);
			_outputB.push_back(NULL);
		}
	}
};

