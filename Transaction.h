#pragma once
#include "Road.h"

class Transaction
{
private:
	Road *from;
	Road *to;
	bool fromA;
	bool toA;
public:
	Transaction(Road* from, Road* to, bool from_a, bool to_a);
	void perform();
};

