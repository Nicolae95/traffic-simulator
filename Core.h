#pragma once
#include "Road.h"
#include "Transaction.h"

class Core
{
private:
	const int carsPerBand = 3;
	int iterator;
	int delay;
	Road verticalRoad;
	Road horizontalRoad;
	Road *currentRoad;
	void check(Car *a, Car *b);
public:
	static Core instance;
	std::list<Transaction*> transactions;
	Core();
	void nextStep();
	void generateRandomCar();
	bool canGoThroughtPath(Car *car, bool fromA);
	void createTransactionForCar(Car *car,bool fromA);
};

