#include "PascalsTriangle.h"

PascalsTriangle::PascalsTriangle(void)
{
}


PascalsTriangle::~PascalsTriangle(void)
{
}

void PascalsTriangle::Calculate(BigUnsignedInteger a){
	this->earlyCalculations.clear();
	this->currentTriangle.clear();
	TriangleRow triangle;
	BigUnsignedInteger temp;
	this->recur_(temp,temp);
	for(;temp<=a;temp++){
		triangle[temp] = this->recur_(a,temp);
	}
	
	//return triangle;
}

BigUnsignedInteger PascalsTriangle::recur_(BigUnsignedInteger a, BigUnsignedInteger b){
	std::string left = std::string(BigUnsignedIntegerWithBase(a, 10));
	std::string rigth = std::string(BigUnsignedIntegerWithBase(b, 10));
	std::string calcKey = left + " " + rigth;
	BigUnsignedInteger result;

	if(this->earlyCalculations.find(calcKey) == this->earlyCalculations.end()){
		if(b==0 || a==b){
			result = 1;
		}else{
			result = this->recur_(a-1,b-1) + this->recur_(a-1,b);
			//return this->pascal_(a-1,b-1) + this->pascal_(a-1,b);
		}	
		this->earlyCalculations[calcKey] = result;
	}else
	{
		// already calculated
		result = this->earlyCalculations[calcKey];
	}
	return result;
}