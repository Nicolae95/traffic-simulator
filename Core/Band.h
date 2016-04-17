#pragma once
#include "Orientation.h"
#include <list>

class Band
{
private:
	Orientation _orientation;
	std::list<Band*> _connections;
public:
	Band(Orientation orientation);
	~Band();
	void addConection(Band *band);
};

