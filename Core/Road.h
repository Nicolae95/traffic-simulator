#pragma once
#include "Orientation.h"
#include <list>

class Road
{
private:
	Orientation _orientation;
	std::list<Road*> _connections;
public:
	Road(Orientation orientation);
	~Road();
	void addConection(Road *band);
};

