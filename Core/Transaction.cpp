#include "Transaction.h"

Transaction::Transaction(Road* from, Road* to, bool from_a, bool to_a)
{
	this->from = from;
	this->to = to;
	this->fromA = from_a;
	this->toA = to_a;
}

void Transaction::perform()
{
	if (this->fromA)
		this->from->_inputA.pop_front();
	else
		this->from->_inputB.pop_front();
	if(this->toA)
		this->to->_outputA-
}
