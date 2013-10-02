#pragma once

#include "IntegerArray.h"
#include <string>
#include "BigUnsignedInteger.h"

class BigUnsignedIntegerWithBase : protected IntegerArray<unsigned short>
{
public:
	typedef unsigned short Element;
	typedef Element Base;
	typedef IntegerArray::uint uint;

protected:
	Base base;

	BigUnsignedIntegerWithBase(int, uint capacity) : IntegerArray<Element>(0,capacity){}

	void removeZerosFromLeft(){
		while (this->length > 0  && this->instance[this->length -1] == 0)
		{
			this->length--;
		}
	}

public:

	unsigned int bitLen(unsigned int x) {
		unsigned int len = 0;
		while (x > 0) {
			x >>= 1;
			len++;
		}
		return len;
	}

	unsigned int ceilingDiv(unsigned int a, unsigned int b) {
		return (a + b - 1) / b;
	}

	// BASE 2
	BigUnsignedIntegerWithBase() : IntegerArray<Element>(), base(2){}


	// COPY 
	BigUnsignedIntegerWithBase(const BigUnsignedIntegerWithBase &bui): IntegerArray<Element>(bui), base(bui.base) {}

	// ASSIGN
	void operator=(const BigUnsignedIntegerWithBase &bui){
		IntegerArray<Element>::operator=(bui);
		this->base = bui.base;
	}

	// COPY FROM Given array of digits
	BigUnsignedIntegerWithBase(const Element *u, uint i, Base base);

	~BigUnsignedIntegerWithBase() {}
	/**
	* BIG UNSIGNED INTEGER CLASS
	*/
	BigUnsignedIntegerWithBase(const BigUnsignedInteger &x, Base base) {
		// Check the base
		assert(base >= 2);

		this->base = base;

		// Get an upper bound on how much space we need
		int maxBitLenOfX = x.getLenght() * BigUnsignedInteger::N;
		int minBitsPerDigit = bitLen(base) - 1;
		int maxDigitLenOfX = ceilingDiv(maxBitLenOfX, minBitsPerDigit);
		this->length = maxDigitLenOfX;
		this->malloc(this->length); // Get the space

		BigUnsignedInteger x2(x);
		BigUnsignedInteger buBase(base);
		uint digitNum = 0;

		while (!x2.isZero()) {
			// Get last digit.  This is like `lastDigit = x2 % buBase, x2 /= buBase'.
			BigUnsignedInteger lastDigit(x2);
			lastDigit.divide(buBase, x2);
			// Save the digit.
			this->instance[digitNum] = lastDigit.toUnsignedShort();
			// Move on.  We can't run out of room: we figured it out above.
			digitNum++;
		}

		// Save the actual length.
		this->length = digitNum;
	}
	//BigUnsignedIntegerWithBase(const BigUnsignedInteger &x, Base base);
	operator BigUnsignedInteger() const{
		BigUnsignedInteger ans(0), buBase(base), temp;
		uint digitNum = this->length;
		while (digitNum > 0) {
			digitNum--;
			temp.multiply(ans, buBase);
			ans.add(temp, BigUnsignedInteger(this->instance[digitNum]));
		}
		return ans;
	}




	operator std::string() const;
	BigUnsignedIntegerWithBase(const std::string &s, Base base);

public:


	/**
	*       GETTERS
	*/
	Base getBase() const { return base;}
	IntegerArray<Element>::getCapacity;
	IntegerArray<Element>::getLenght;

	unsigned short getElement(uint i) const 
	{
		if(i >= this->length){
			return 0;
		}else
		{
			return this->instance[i];
		}
	}

	bool izZero() const {
		return IntegerArray<Element>::isEmpty();
	}

	// EQUALS
	bool operator==(const BigUnsignedIntegerWithBase &bui) const{
		if(this->base == bui.base){
			return IntegerArray<Element>::operator==(bui);
		}else
		{
			return false;
		}
	}

	// NOT EQUAL
	bool operator!=(const BigUnsignedIntegerWithBase &bui) const {
		return !this->operator==(bui);
	}

};

