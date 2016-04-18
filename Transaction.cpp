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
	Car *car;
	if (this->fromA) {
		car = *(this->from->_inputA.begin());
		this->from->_inputA.pop_front();
		this->from->_inputA.push_back(NULL);
	}
	else {
		car = *(this->from->_inputB.begin());
		this->from->_inputB.pop_front();
		this->from->_inputB.push_back(NULL);
	}
	if (this->toA){
		this->to->_outputA.pop_back();
		this->to->_outputA.push_back(car);
	}
	else {
		this->to->_outputB.pop_back();
		this->to->_outputB.push_back(car);
	}
}
