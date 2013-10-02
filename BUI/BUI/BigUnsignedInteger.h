#pragma once
#include "IntegerArray.h"

class BigUnsignedInteger : protected IntegerArray<unsigned int>
{
public:
	// COMPARISON FLAGS
	enum COMPARISON {
		smaller = -1,
		equal = 0,
		bigger = 1
	};

	// we use uint here also
	typedef IntegerArray::uint uint;

	IntegerArray<uint>::N;

protected:

	BigUnsignedInteger(int, uint c) : IntegerArray<uint>(0,c){}

	void removeZerosFromLeft(){
		while (this->length > 0  && this->instance[this->length -1] == 0)
		{
			this->length--;
		}
	}

public:
	// zero
	BigUnsignedInteger(): IntegerArray<uint>(){}

	// COPY
	BigUnsignedInteger(const BigUnsignedInteger &bui) : IntegerArray<uint>(bui){}

	void operator=(const BigUnsignedInteger &x) {
		IntegerArray<uint>::operator =(x);
	}

	BigUnsignedInteger(const uint *data, uint length) : IntegerArray<uint>(data,length){
		removeZerosFromLeft();
	}
	
	~BigUnsignedInteger(){};

	// Destructor.  
	

	// Constructors from primitive integer types
	BigUnsignedInteger(unsigned long  x);
	BigUnsignedInteger(         long  x);
	BigUnsignedInteger(unsigned int   x);
	BigUnsignedInteger(         int   x);
	BigUnsignedInteger(unsigned short x);
	BigUnsignedInteger(         short x);

protected:
	template <class T>
	void initFromPrimitive(T t);
	template <class T>
	void initFromSignedPrimitive(T t);

public:
	unsigned long toUnsignedLong() const;
	long toLong() const;
	unsigned int toUnsignedInt() const;
	int toInt() const;
	unsigned short toUnsignedShort() const;
	short toShort() const;

protected:
	template <class T>
	T convertToSignedPrimitive() const;
	template <class T>
	T convertToPrimitive() const;

public:
	IntegerArray<uint>::getCapacity;
	IntegerArray<uint>::getLenght;

	// get data from array
	uint getData(uint i)const {
		if(this->length < i){
			return 0;
		}else
		{
			return this->instance[i];
		}
	}

	// set data in array
	void setData(uint i, uint newData);

	bool isZero() const {return IntegerArray<uint>::isEmpty();}

	uint bitLength() const;

	bool getBit(uint bit)const{
		return (getData(bit / N) & (uint(1) << (bit % N))) != 0;
	}

	void setBit(uint bit, bool newBit);

	COMPARISON compareTo(const BigUnsignedInteger &bui) const;

	/*
	*	OVERLOADED OPERATORS
	*
	*/

	bool operator==(const BigUnsignedInteger &bui) const{
		return IntegerArray<uint>::operator==(bui);
	}

	bool operator!=(const BigUnsignedInteger &bui)const{
		return IntegerArray<uint>::operator!=(bui);
	}

	bool operator < (const BigUnsignedInteger &bui) const {
		return compareTo(bui) == smaller;
	}

	bool operator <= (const BigUnsignedInteger &bui) const{
		return compareTo(bui) != bigger;
	}

	bool operator >= (const BigUnsignedInteger &bui) const{
		return compareTo(bui) != smaller;
	}

	bool operator > (const BigUnsignedInteger &bui) const{
		return compareTo(bui) == bigger;
	}

	BigUnsignedInteger operator +(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator -(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator *(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator /(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator %(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator &(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator |(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator ^(const BigUnsignedInteger &bui) const;
	BigUnsignedInteger operator <<(int b) const;
	BigUnsignedInteger operator >>(int b) const;

	void operator ++(   );
	void operator ++(int);
	void operator --(   );
	void operator --(int);

	void operator +=(const BigUnsignedInteger &x);
	void operator -=(const BigUnsignedInteger &x);
	void operator *=(const BigUnsignedInteger &x);
	void operator /=(const BigUnsignedInteger &x);
	void operator %=(const BigUnsignedInteger &x);
	void operator &=(const BigUnsignedInteger &x);
	void operator |=(const BigUnsignedInteger &x);
	void operator ^=(const BigUnsignedInteger &x);
	void operator <<=(int b);
	void operator >>=(int b);

	/**
	*	MATH operations
	*/
	void add(const BigUnsignedInteger &a, const BigUnsignedInteger &b);
	void subtract(const BigUnsignedInteger &a, const BigUnsignedInteger &b);
	void multiply(const BigUnsignedInteger &a, const BigUnsignedInteger &b);
	void bitAnd(const BigUnsignedInteger &a, const BigUnsignedInteger &b);
	void bitOr(const BigUnsignedInteger &a, const BigUnsignedInteger &b);
	void bitXor(const BigUnsignedInteger &a, const BigUnsignedInteger &b);
	void bitShiftLeft(const BigUnsignedInteger &a, int b);
	void bitShiftRight(const BigUnsignedInteger &a, int b);
	void divide(const BigUnsignedInteger &b, BigUnsignedInteger &q);


	/**
	*	SOME HACK
	*/
	friend unsigned int getShiftedBlock(const BigUnsignedInteger &number, uint x,
		unsigned int y);
};

