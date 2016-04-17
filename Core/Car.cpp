#include "Car.h"
#include <cstdlib>

Car::Car()
{
	direction = (Direction)(rand() % 3);
}
