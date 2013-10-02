#pragma once
#include <cassert>
#ifndef NULL
#define NULL 0
#endif
/**
*	Our collector
*/
template <class Klass>
class IntegerArray
{
public:

	/**
	*	**** Type definitions**** 
	*/
	typedef unsigned int uint;

	// each blocks' bit count
	static const unsigned int N;

	// the block capacitys
	uint capacity;

	// the length of value
	uint length;

	//real content
	Klass *instance;

	/**
	*	Constructors
	*/
	IntegerArray() : capacity(0), length(0){
		instance = NULL;
	};

	IntegerArray(uint i): capacity(0), lengt(0){
		if(capacity > 0)
		{
			this->instance = new Klass[capacity];
		}
		else
		{
			this->instance = NULL;
		}
	}


	/**
	*	OVERLOADED OPERATORS
	*/
	void operator=(const IntegerArray<Klass> &integerArray){
		if(this != &integerArray){
			this->length = integerArray.length;
			this->malloc(this->length);
			uint i;
			for(i = 0; i < this->length; i++){
				this->instance[i] = integerArray.instance[i];
			}
		}
	}

	IntegerArray(const IntegerArray<Klass> &integerArray)
		:length(integerArray.length)
	{
		this->capacity = this->length;
		instance = new Klass[this->capacity];

		uint i;
		for(i = 0; i < this->length; i++){
			this->instance[i] = integerArray.instance[i];
		}
	}

	IntegerArray(const Klass *k, uint length)
		: capacity(length), length(length)
	{
		this->instance = new Klass[this->capacity];
		uint i;
		for(i = 0; i < this->length; i++){
			this->instance[i] = k[i];
		}
	}

	bool operator ==(const IntegerArray<Klass> &integerArray) const{
		if(this->length != integerArray.length)
		{
			return false;
		}
		else
		{
			uint i;
			for(i = 0; i < this->length; i++){
				if(this->instance[i] != integerArray.instance[i])
				{
					return false;
				}
			}
			return true;
		}
	}
	bool operator !=(const IntegerArray<Klass> &integerArray) const{
		return ! operator==(integerArray);
	}

	/**
	*	Special Methods
	*/
	void malloc(uint i){
		if(this->capacity < i){
			delete [] this->instance;
			this->capacity = i;
			this->instance = new Klass[this->capacity];
		}
	};
	void expand(uint i){
		if(this->capacity < i){
			Klass *temp = this->instance;
			this->capacity = i;
			this->instance = new Klass[this->capacity];

			uint j;
			for (int j= 0; j< length; j++)
			{
				this->instance[j] = temp[j];
			}

			delete []temp;
		}
	};
	uint getCapacity() const {return this->capacity;}
	uint getLenght() const {return this->length;}
	Klass getContent(uint ) const {return this->instance[i];}
	bool isEmpty() const {return this->length == 0;}


	~IntegerArray(){
		delete []instance;
	};
};

template <class Klass>
const unsigned int IntegerArray<Klass>::N = 8 * sizeof(Klass);