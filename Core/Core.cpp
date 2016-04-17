#include "Core.h"



Core::Core()
{
	delay = 5;
	iterator = 0;
}

void Core::nextStep()
{
	// check if we have to toggle data
	iterator++;
	if(iterator > delay)
	{
		currentRoad->active = false;
		currentRoad = (horizontalRoad.active) ? &verticalRoad : &horizontalRoad;
	}
	currentRoad->active = true;

	// do transactions
	for (std::list<Transaction>::iterator it = transactions.begin(); it != transactions.end(); it++)
	{
		
	}


	// reset crossing :) assume that "pietons" crossed lines.
	currentRoad->crossingA = currentRoad->crossingB = false;
}
