#pragma once
#include "Road.h"
#include "Transaction.h"

class Core
{
private:
	int delay;
	Road *currentRoad;
	void check(Car *a, Car *b);
public:
	Road verticalRoad;
	Road horizontalRoad;
	int iterator;
	static Core instance;
	std::list<Transaction*> transactions;
	Core();
	void nextStep();
	void generateRandomCar();
	bool canGoThroughtPath(Car *car, bool fromA);
	void createTransactionForCar(Car *car,bool fromA);
	void increaseSpeed();
	void decreaseSpeed();
};

