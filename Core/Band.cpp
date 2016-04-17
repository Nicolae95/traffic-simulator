#include "Band.h"

Band::Band(Orientation orientation)
{
	this->_orientation = orientation;
}

Band::~Band()
{
	this->_connections.clear();
}

void Band::addConection(Band* band)
{
	this->_connections.push_back(band);
}
