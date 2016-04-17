#include "Core.h"

int main()
{
	Core core;
	while(true)
	{
		core.nextStep();
		if (rand() % 1 == 0)
			core.generateRandomCar();
	}

	return 0;
}
