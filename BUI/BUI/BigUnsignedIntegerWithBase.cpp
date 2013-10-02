#include "BigUnsignedIntegerWithBase.h"


BigUnsignedIntegerWithBase::BigUnsignedIntegerWithBase(const Element *e, uint _length, Base base) 
	: IntegerArray<Element>(e,_length),base(base){

		// base validation
		assert(base>=2);

		// element validation
		uint i;
		for(i=0; i < _length; i++){
			assert(this->instance[i] < base);
		}

		removeZerosFromLeft();
}



BigUnsignedIntegerWithBase::BigUnsignedIntegerWithBase(const std::string &s, Base base){
	assert(base <= 36);

	this->base = base;

	this->length = uint(s.length());
	this->malloc(this->length);

	uint elementNumber;
	uint character;
	for (int elementNumber = 0; elementNumber < this->length; elementNumber++)
	{
		character = this->length -1 - elementNumber;
		char theCharacter = s[character];
		if(theCharacter >= '0' && theCharacter <= '9'){
			this->instance[elementNumber] = theCharacter - '0';
		}else if(theCharacter >= 'A' && theCharacter <= 'Z'){
			this->instance[elementNumber] = theCharacter - 'A' + 10;
		}else if(theCharacter >= 'a' && theCharacter <= 'z'){
			this->instance[elementNumber] = theCharacter - 'a' +10;
		}else{
			// nothing for now
		}

		// validate if its too big
		assert(this->instance[elementNumber] < base);
	}

	removeZerosFromLeft();
}

BigUnsignedIntegerWithBase::operator std::string() const{
	// validate base over 36
	assert(base <= 36);
	if(this->length == 0){
		return std::string("0");
	}

	char *s = new char[this->length+1];
	s[this->length] = '\0';
	uint elementNumber;
	uint character;
	for (int character = 0; character< this->length; character++)
	{
		elementNumber = this->length -1 -character;
		Element theElement = this->instance[elementNumber];
		if(theElement < 10){
			s[character] = char('0' + theElement);
		}else
		{
			s[character] = char('A' + theElement - 10);
		}
	}

	std::string s2(s);
	delete[] s;
	return s2;
}



//namespace {
//	unsigned int bitLen(unsigned int x) {
//		unsigned int len = 0;
//		while (x > 0) {
//			x >>= 1;
//			len++;
//		}
//		return len;
//	}
//	unsigned int ceilingDiv(unsigned int a, unsigned int b) {
//		return (a + b - 1) / b;
//	}
//}



//inline BigUnsignedIntegerWithBase::operator BigUnsignedInteger() const {
//	BigUnsignedInteger ans(0), buBase(base), temp;
//	uint digitNum = this->length;
//	while (digitNum > 0) {
//		digitNum--;
//		temp.multiply(ans, buBase);
//		ans.add(temp, BigUnsignedInteger(this->instance[digitNum]));
//	}
//	return ans;
//}