#pragma once
#include "BigUnsignedIntegerWithBase.h"
#include <iostream>
#include <map>

using namespace std;
class PascalsTriangle
{
public:
	/**
		PASCAL TRIANGLE 
	*/
	typedef std::map<BigUnsignedInteger,BigUnsignedInteger> TriangleRow;
	typedef std::map<std::string,BigUnsignedInteger> TriangleNodes;

	void Calculate(BigUnsignedInteger a);
	TriangleNodes GetCalculations(){
		return this->earlyCalculations;
	}
	PascalsTriangle();
	~PascalsTriangle(void);


private:
	TriangleRow currentTriangle;
	TriangleNodes earlyCalculations;
	BigUnsignedInteger recur_(BigUnsignedInteger a,BigUnsignedInteger b);
};

