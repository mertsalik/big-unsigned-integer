#include "BigUnsignedInteger.h"

BigUnsignedInteger BigUnsignedInteger::operator+(const BigUnsignedInteger &bui) const{
	BigUnsignedInteger temp;
	temp.add(*this, bui);
	return temp;
}

BigUnsignedInteger BigUnsignedInteger::operator-(const BigUnsignedInteger &bui) const{
	BigUnsignedInteger temp;
	temp.subtract(*this,bui);
	return temp;
}

BigUnsignedInteger BigUnsignedInteger::operator*(const BigUnsignedInteger &bui) const{
	BigUnsignedInteger temp;
	temp.multiply(*this,bui);
	return temp;
}

BigUnsignedInteger BigUnsignedInteger::operator/(const BigUnsignedInteger &bui) const{
	assert(!bui.isZero());
	BigUnsignedInteger result,temp;
	temp = *this;
	temp.divide(bui,result);
	return result;
}

BigUnsignedInteger BigUnsignedInteger::operator%(const BigUnsignedInteger &bui) const{
	assert(!bui.isZero());
	BigUnsignedInteger result,temp;
	temp = *this;
	temp.divide(bui,result);
	return result;
}

BigUnsignedInteger BigUnsignedInteger::operator&(const BigUnsignedInteger &bui) const{
	BigUnsignedInteger temp;
	temp.bitAnd(*this, bui);
	return temp;
}

BigUnsignedInteger BigUnsignedInteger::operator|(const BigUnsignedInteger &bui) const{
	BigUnsignedInteger temp;
	temp.bitOr(*this,bui);
	return temp;
}

BigUnsignedInteger BigUnsignedInteger::operator^(const BigUnsignedInteger &bui) const{
	BigUnsignedInteger temp;
	temp.bitXor(*this,bui);
	return temp;
}

BigUnsignedInteger BigUnsignedInteger::operator <<(int i) const{
	BigUnsignedInteger temp;
	temp.bitShiftLeft(*this,i);
	return temp;
}

BigUnsignedInteger BigUnsignedInteger::operator>>(int i) const{
	BigUnsignedInteger temp;
	temp.bitShiftRight(*this,i);
	return temp;
}
void BigUnsignedInteger::operator+=(const BigUnsignedInteger &bui){
	this->add(*this,bui);
}

void BigUnsignedInteger::operator-=(const BigUnsignedInteger &bui){
	this->subtract(*this,bui);
}

void BigUnsignedInteger::operator*=(const BigUnsignedInteger &bui){
	this->multiply(*this,bui);
}

void BigUnsignedInteger::operator/=(const BigUnsignedInteger &bui){
	assert(!bui.isZero());
	BigUnsignedInteger temp;
	this->divide(bui,temp);
	*this = temp;
}

void BigUnsignedInteger::operator %=(const BigUnsignedInteger &bui){
	assert(!bui.isZero());
	BigUnsignedInteger temp;
	divide(bui,temp);
}

void BigUnsignedInteger::operator &=(const BigUnsignedInteger &bui){
	bitAnd(*this,bui);
}

void BigUnsignedInteger::operator |=(const BigUnsignedInteger &bui){
	bitOr(*this,bui);
}

void BigUnsignedInteger::operator ^=(const BigUnsignedInteger &bui){
	bitXor(*this,bui);
}

void BigUnsignedInteger::operator<<=(int i){
	bitShiftLeft(*this,i);
}

void BigUnsignedInteger::operator>>=(int i){
	bitShiftRight(*this,i);
}


/**
*	TEMPLATES
*/

template<class P>
void BigUnsignedInteger::initFromPrimitive(P p){
	if(p == 0){
		// already zero
	}else
	{
		this->capacity = 1;
		this->instance = new uint[1];
		this->length = 1;
		this->instance[0] = uint(p);
	}
}

template <class SP>
void BigUnsignedInteger::initFromSignedPrimitive(SP sp){
	assert(sp >= 0);

	initFromPrimitive(sp);
}

template <class P>
P BigUnsignedInteger::convertToPrimitive()const{
	if(this->length == 0){
		return 0;
	}
	else if(this->length == 1)
	{
		P p = P(this->instance[0]);

		//assert(uint(p) == this->instance[p]);
		return p;
	}
}

template <class SP>
SP BigUnsignedInteger::convertToSignedPrimitive() const{
	SP sp = convertToPrimitive<SP>();
	assert(sp >= 0);
	return sp;
}


// CREATORS

BigUnsignedInteger::BigUnsignedInteger(unsigned long x){
	this->initFromPrimitive(x);
}
BigUnsignedInteger::BigUnsignedInteger(unsigned int x){
	this->initFromPrimitive(x);
}
BigUnsignedInteger::BigUnsignedInteger(unsigned short x){
	this->initFromPrimitive(x);
}
BigUnsignedInteger::BigUnsignedInteger(long x){
	this->initFromSignedPrimitive(x);
}
BigUnsignedInteger::BigUnsignedInteger(int x){
	this->initFromSignedPrimitive(x);
}
BigUnsignedInteger::BigUnsignedInteger(short x){
	this->initFromSignedPrimitive(x);
}
unsigned long BigUnsignedInteger::toUnsignedLong() const{
	return convertToPrimitive<unsigned long>();
}
unsigned int BigUnsignedInteger::toUnsignedInt() const{
	return convertToPrimitive<unsigned int>();
}
unsigned short BigUnsignedInteger::toUnsignedShort() const{
	return convertToPrimitive<unsigned short>();
}
long BigUnsignedInteger::toLong()const{
	return convertToSignedPrimitive<long>();
}
int BigUnsignedInteger::toInt()const{
	return convertToSignedPrimitive<int>();
}
short BigUnsignedInteger::toShort()const{
	return convertToSignedPrimitive<int>();
}

inline void BigUnsignedInteger::setData(uint i,uint newData){
	if(newData == 0){
		if(i < this->length){
			this->instance[i] = 0;
			this->removeZerosFromLeft();
		}
	}else
	{
		if(i >= this->length){
			this->expand(i+1);
			for(uint j = this->length; j < i; j++){
				this->instance[j] = 0;
			}
			this->length = i+1;
		}
		this->instance[i] = newData;
	}
}

inline BigUnsignedInteger::uint BigUnsignedInteger::bitLength() const{
	if(this->isZero()){
		return 0;
	}else
	{
		uint leftMostData = getData(this->length -1);
		uint leftMostDataLength = 0;
		while(leftMostData != 0){
			leftMostData >>= 1;
			leftMostDataLength++;
		}
		return leftMostDataLength + (this->length -1) * N;
	}
}

inline void BigUnsignedInteger::setBit(uint bit, bool newBit){
	uint temp = bit / N;
	uint data = getData(temp);
	uint mask = uint(1) << (bit % N);
	if(newBit){
		data = data | mask;
	}else
	{
		data = data & ~mask;
	}
	setData(temp,data);
}

/**
*	COMPARISONS
*/
BigUnsignedInteger::COMPARISON BigUnsignedInteger::compareTo(const BigUnsignedInteger &bui)const{
	if(this->length < bui.length){
		return smaller;
	}else if(this->length > bui.length){
		return bigger;
	}else
	{
		uint i = this->length;
		while (i>0)
		{
			i--;
			if(this->instance[i] == bui.instance[i])
				continue;
			else if(this->instance[i] > bui.instance[i])
				return bigger;
			else 
				return smaller;
		}
	}
	return equal;
}



void BigUnsignedInteger::add(const BigUnsignedInteger &a, const BigUnsignedInteger &b){
	// trick for right hand operations
	if(this == &a || this == &b){
		BigUnsignedInteger temp;
		temp.add(a,b);
		*this = temp;
		return;
	}
	if(a.length == 0){
		operator =(b);
		return;
	}else if(b.length == 0){
		operator =(a);
		return;
	}
	bool carryIn,carryOut;
	uint temp;
	uint i;

	const BigUnsignedInteger *longer,*shorter;
	if(a.length >= b.length){
		longer = &a;
		shorter = &b;
	}else
	{
		longer = &b;
		shorter = &a;
	}

	this->length = longer->length +1;
	this->malloc(this->length);

	for (i = 0, carryIn = false; i < shorter->length; i++)
	{
		temp = longer->instance[i] + shorter->instance[i];
		// if any overflow occurs result less then shorter one
		carryOut = (temp < shorter->instance[i]);
		// if this is a carry input
		if(carryIn){
			temp++;
			carryOut |= (temp == 0);
		}
		// save the data
		this->instance[i] = temp; 
		// carryout -> carryIn
		carryIn = carryOut;
	}

	// if there is a carry over from left, increase data
	for (; i < longer->length && carryIn; i++)
	{
		temp = longer->instance[i] + 1;
		carryIn = (temp == 0);
		this->instance[i] = temp;
	}

	// copy remaining data from longer one
	for(; i< longer->length; i++){
		this->instance[i] = longer->instance[i];
	}
	// if still carry in add extra digit
	if(carryIn){
		this->instance[i] = 1;
	}else
	{
		this->length--;
	}
}


void BigUnsignedInteger::subtract(const BigUnsignedInteger &a, const BigUnsignedInteger &b){
	// trick for right hand operations
	if(this == &a || this == &b){
		BigUnsignedInteger temp;
		temp.subtract(a,b);
		*this = temp;
		return;
	}
	assert(a.length >= b.length);

	if(b.length == 0){
		operator =(a);
		return;
	}

	bool borrowIn, borrowOut;
	uint temp;
	uint i;

	this->length = a.length;
	this->malloc(this->length);

	for (i = 0, borrowIn = false; i < b.length; i++)
	{
		temp = a.instance[i] - b.instance[i];
		borrowOut = (temp > a.instance[i]);

		if(borrowIn){
			borrowOut |= (temp ==0);
			temp--;
		}
		// result
		this->instance[i] = temp;
		borrowIn = borrowOut;
	}

	for (; i < length; i++)
	{
		borrowIn = (a.instance[i] == 0);
		this->instance[i] = a.instance[i] -1;
	}
	// if still has a borrow, result is negative lets make it zero
	if(borrowIn){
		this->length = 0;
	}else
	{
		// copy rest of the a data
		for (; i < a.length; i++)
		{
			this->instance[i]  = a.instance[i];
		}
	}

	this->removeZerosFromLeft();
}

inline unsigned int getShiftedBlock(const BigUnsignedInteger &number,
									BigUnsignedInteger::uint x, unsigned int y){
										BigUnsignedInteger::uint part1 = (x == 0 || y == 0) ? 0 : (number.instance[x-1] >> (BigUnsignedInteger::N - y));
										BigUnsignedInteger::uint part2 = (x == number.length) ? 0 : (number.instance[x] << y);
										return part1|part2;
}


void BigUnsignedInteger::multiply(const BigUnsignedInteger &a, const BigUnsignedInteger &b){
	// trick for right hand operations
	if(this == &a || this == &b){
		BigUnsignedInteger temp;
		temp.multiply(a,b);
		*this = temp;
		return;
	}

	if(a.length == 0 || b.length == 0){
		this->length = 0;
		return;
	}

	/*
	* For each 1-bit of "a" 
	*    Add b digits to *this.
	*/
	uint i,j,k;
	uint i2;
	uint temp;
	bool carryIn, carryOut;


	this->length = a.length + b.length;
	this->malloc(this->length);
	for (i = 0; i < this->length; i++)
	{
		this->instance[i] = 0;
	}
	for (i = 0; i < a.length; i++)
	{
		for (int i2 = 0; i2  < this->N; i2 ++)
		{
			if( (a.instance[i] & (uint(1) << i2)) == 0 )
				continue;

			// add b to this

			for (j = 0,k = i, carryIn = false; j < b.length; j++, k++)
			{
				temp = this->instance[k] + getShiftedBlock(b,j,i2);
				carryOut = (temp < this->instance[k]);
				if(carryIn){
					temp++;
					carryOut |= (temp == 0);
				}

				// save the data
				this->instance[k] = temp;
				carryIn = carryOut;
			}

			for(; carryIn; k++){
				this->instance[k]++;
				carryIn = (this->instance[k] == 0);
			}
		}
	}

	if(this->instance[this->length -1] == 0){
		this->length --;
	}
}


void BigUnsignedInteger::divide(const BigUnsignedInteger &b, BigUnsignedInteger &q){
	assert(this != &q);
	// trick for aliases
	if(this == &b || &q == &b){
		BigUnsignedInteger tempB(b);
		divide(tempB,q);
		return;
	}

	if(b.length == 0){
		q.length = 0;
		return;
	}

	// this is smaller than b
	if(this->length < b.length){
		q.length = 0;
		return;
	}

	// this.length >= b.length > 0
	uint i,j,k;
	uint i2;
	uint temp;
	bool borrowIn,borrowOut;

	uint originalLength = this->length;

	// increment logical length
	this->expand(this->length+1);
	this->length++;
	this->instance[originalLength] = 0;

	uint *substractBuffer = new uint(this->length);

	q.length = originalLength - b.length +1;
	q.malloc(q.length);

	// bölüm sýfýrlandý
	for (i = 0; i < q.length; i++)
	{
		q.instance[i] = 0;
	}

	// continue with left shifts
	i = q.length;
	while(i > 0){
		i--;
		q.instance[i] = 0;
		i2 = N;
		while(i2 > 0){
			i2--;

			for (j = 0, k=i, borrowIn = false; j <= b.length; j++,k++)
			{
				temp = this->instance[k] - getShiftedBlock(b,j,i2);
				borrowOut = (temp > this->instance[k]);
				if(borrowIn){
					borrowOut |=  (temp == 0);
					temp--;
				}

				substractBuffer[k] = temp;
				borrowIn = borrowOut;
			}

			for(;k<originalLength && borrowIn; k++){
				borrowIn = (this->instance[k] == 0);
				substractBuffer[k] = this->instance[k] -1;
			}

			if(!borrowIn){
				q.instance[i] |= (uint(1) << i2);
				while(k > i){
					k--;
					this->instance[k] = substractBuffer[k];
				}
			}
		}
	}
	if(q.instance[q.length -1] == 0){
		q.length--;
	}
	removeZerosFromLeft();
	//delete[] substractBuffer;
}

inline void BigUnsignedInteger::bitAnd(const BigUnsignedInteger &a, const BigUnsignedInteger &b){
	// trick for the aliases
	if(this == &a || this == &b){
		BigUnsignedInteger temp;
		temp.bitAnd(a,b);
		*this = temp;
		return;
	}
	if(a.length > b.length){
		this->length = b.length;
	}else
	{
		this->length = a.length;
	}

	this->malloc(this->length);
	uint i;
	for (i = 0; i < this->length; i++)
	{
		this->instance[i] = a.instance[i] & b.instance[i];
	}

	removeZerosFromLeft();
}

inline void BigUnsignedInteger::bitOr(const BigUnsignedInteger &a, const BigUnsignedInteger &b){
	// trick for the aliases
	if(this == &a || this == &b){
		BigUnsignedInteger temp;
		temp.bitOr(a,b);
		*this = temp;
		return;
	}
	uint i;
	const BigUnsignedInteger *longer,*shorter;
	if (a.length >= b.length) {
		longer = &a;
		shorter = &b;
	} else {
		longer = &b;
		shorter = &a;
	}

	this->malloc(longer->length);
	for (i = 0; i < shorter->length; i++)
	{
		this->instance[i] = longer->instance[i] | shorter->instance[i];
	}
	for (; i< longer->length; i++)
	{
		this->instance[i] = longer->instance[i];
	}
	this->length = longer->length;
}

inline void BigUnsignedInteger::bitXor(const BigUnsignedInteger &a, const BigUnsignedInteger &b){
	// trick for the aliases
	if(this == &a || this == &b){
		BigUnsignedInteger temp;
		temp.bitXor(a,b);
		*this = temp;
		return;
	}
	uint i;
	const BigUnsignedInteger *longer,*shorter;
	if (a.length >= b.length) {
		longer = &a;
		shorter = &b;
	} else {
		longer = &b;
		shorter = &a;
	}

	this->malloc(longer->length);
	for (i = 0; i < shorter->length; i++)
	{
		this->instance[i] = longer->instance[i] ^ shorter->instance[i];
	}
	for (; i< longer->length; i++)
	{
		this->instance[i] = longer->instance[i];
	}
	this->length = longer->length;
	this->removeZerosFromLeft();
}

inline void BigUnsignedInteger::bitShiftLeft(const BigUnsignedInteger &a, int b){
	// trick for the aliases
	if(this == &a){
		BigUnsignedInteger temp;
		temp.bitShiftLeft(a,b);
		*this = temp;
		return;
	}

	if(b < 0){
		assert((b << 1) != 0);
		bitShiftRight(a,-b);
		return;
	}

	uint shiftSize = b/this->N;
	uint shiftBits = b%this->N;
	this->length = a.length + shiftSize+1;
	this->malloc(this->length);

	uint i,j;
	for (i = 0; i < shiftSize; i++)
	{
		this->instance[i] = 0;
	}
	for(j=0,i=shiftSize; j <= a.length;j++,i++){
		this->instance[i] = getShiftedBlock(a,j,shiftBits);
	}
	if(this->instance[this->length -1] == 0)
		this->length--;

}


inline void BigUnsignedInteger::bitShiftRight(const BigUnsignedInteger &a, int b)
{
	// trick for the aliases
	if(this == &a){
		BigUnsignedInteger temp;
		temp.bitShiftLeft(a,b);
		*this = temp;
		return;
	}

	if(b < 0){
		assert((b << 1) != 0);
		bitShiftLeft(a,-b);
		return;
	}

	uint rightShiftSize = (b + this->N -1) /this->N;
	uint leftShiftBits = this->N * rightShiftSize -b;

	if(rightShiftSize >= a.length +1){
		this->length = 0;
		return;
	}else
	{
		this->length = a.length + 1 - rightShiftSize;
		this->malloc(this->length);
		uint i,j;
		for(j = rightShiftSize, i = 0; j <= a.length; j++,i++){
			this->instance[i] = getShiftedBlock(a,j,leftShiftBits);
		}

		if(this->instance[this->length -1] == 0){
			this->length--;
		}
	}
}


void BigUnsignedInteger::operator ++(){
	uint i;
	bool carry = true;
	for (i = 0; i < this->length && carry; i++)
	{
		this->instance[i] ++;
		carry = (this->instance[i] == 0);
	}
	if(carry){
		this->expand(this->length+1);
		this->length++;
		this->instance[i] = 1;
	}
}

void BigUnsignedInteger::operator ++(int){
	operator++();
}

void BigUnsignedInteger::operator --(){
	assert(this->length != 0);
	uint i;
	bool borrow = true;
	for (i = 0; i < length; i++)
	{
		borrow = (this->instance[i] == 0);
		this->instance[i]--;
	}

	if(this->instance[this->length -1] == 0){
		this->length--;
	}
}

void BigUnsignedInteger::operator --(int){
	operator--();
}

