#include "Core.h"
#include <ctime>


Core::Core()
{
	srand(time(NULL));
	delay = 5;
	iterator = 0;
	currentRoad = &horizontalRoad;
}

void Core::nextStep()
{
	// check if we have to toggle data
	iterator++;
	if(iterator >= delay)
	{
		iterator = 0;
		currentRoad->active = false;
		currentRoad = (currentRoad == &horizontalRoad) ? &verticalRoad : &horizontalRoad;
	}
	currentRoad->active = true;

	// do transactions
	for (std::list<Transaction*>::iterator it = transactions.begin(); it != transactions.end(); it++)
	{
		(*it)->perform();
	}

	//remove transactions
	transactions.clear();

	Car* carA = currentRoad->_inputA.size() ? *(currentRoad->_inputA.begin()) : NULL;
	Car* carB = currentRoad->_inputB.size() ? *(currentRoad->_inputB.begin()) : NULL;
	if(carA && carB)
		check(carA, carB);
	else
	{
		if (carA)
			createTransactionForCar(carA,true);
		if (carB)
			createTransactionForCar(carB,false);

	}

	// reset crossing :) assume that "pietons" crossed lines.
	Road *crossingRoad = (currentRoad == &verticalRoad) ? &horizontalRoad : &verticalRoad;
	crossingRoad->crossingA = crossingRoad->crossingB = false;
}

void Core::generateRandomCar()
{
	Road *temp = (rand() % 2) ? &horizontalRoad : &verticalRoad;
	std::list<Car*> *tempList = (rand() % 2) ? &temp->_inputA : &temp->_inputB;
	tempList->push_back(new Car());
}


void Core::check(Car* a, Car* b)
{
	bool aCanMove = true;
	bool bCanMove = true;
	if (a->direction == FRONT || b->direction == LEFT)
		bCanMove = false;
	if (a->direction == LEFT || b->direction == FRONT)
		aCanMove = false;

	if (a->direction == RIGHT && b->direction == LEFT)
		bCanMove = false;

	if (a->direction == LEFT && b->direction == RIGHT)
		aCanMove = false;

	// add if all ok
	if(aCanMove)
	{
		createTransactionForCar(a,true);
	}
	if(bCanMove)
	{
		createTransactionForCar(b,false);		
	}
}

//check for zebras )))
bool Core::canGoThroughtPath(Car* car, bool fromA)
{
	if (currentRoad == &verticalRoad)
	{
		if (fromA && car->direction == RIGHT && horizontalRoad.crossingB)
			return false;
		if (fromA && car->direction == LEFT && horizontalRoad.crossingA)
			return false;
		if (!fromA && car->direction == RIGHT && horizontalRoad.crossingA)
			return false;
		if (!fromA && car->direction == LEFT && horizontalRoad.crossingB)
			return false;
	}
	else
	{
		if (fromA && car->direction == RIGHT && verticalRoad.crossingA)
			return false;
		if (fromA && car->direction == LEFT && verticalRoad.crossingB)
			return false;
		if (!fromA && car->direction == RIGHT && verticalRoad.crossingB)
			return false;
		if (!fromA && car->direction == LEFT && verticalRoad.crossingA)
			return false;

	}

	return true;
}

void Core::createTransactionForCar(Car* car,bool fromA)
{
	if (canGoThroughtPath(car, fromA)) {
		Road *toRoad = (currentRoad == &verticalRoad) ? &horizontalRoad : &verticalRoad;
		if (car->direction == FRONT)
			toRoad = currentRoad;
		bool toA;
		if (fromA && currentRoad == &verticalRoad)
			toA = (car->direction == LEFT) ? true : false;
		if (!fromA && currentRoad == &verticalRoad)
			toA = (car->direction == RIGHT) ? true : false;
		if (fromA && currentRoad == &horizontalRoad)
			toA = (car->direction == RIGHT) ? true : false;
		if (!fromA && currentRoad == &horizontalRoad)
			toA = (car->direction == LEFT) ? true : false;

		// if go forward :)
		if (toRoad == currentRoad)
			toA = !fromA;
		transactions.push_back(new Transaction(currentRoad, toRoad, fromA, toA));
	}
}
