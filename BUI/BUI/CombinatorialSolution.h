#pragma once
#include "PascalsTriangle.h"
class CombinatorialSolution
{
public:
	typedef PascalsTriangle::TriangleNodes SolutionMap;

	CombinatorialSolution(void);
	~CombinatorialSolution(void);

	BigUnsignedInteger Choose(BigUnsignedInteger n, BigUnsignedInteger &k);
	static BigUnsignedInteger GreatestCommonDivisor(BigUnsignedInteger &a, BigUnsignedInteger &b);
};

