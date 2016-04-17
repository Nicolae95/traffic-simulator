#include "Road.h"

Road::Road(Orientation orientation)
{
	this->_orientation = orientation;
}

Road::~Road()
{
	this->_connections.clear();
}

void Road::addConection(Road* band)
{
	this->_connections.push_back(band);
}
