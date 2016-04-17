#pragma once
#include "Road.h"
#include "Transaction.h"

class Core
{
private:
	int iterator;
	int delay;
	Road verticalRoad;
	Road horizontalRoad;
	Road *currentRoad;
	std::list<Transaction> transactions;
public:
	Core();
	void nextStep();
};

