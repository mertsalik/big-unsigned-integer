#include "CombinatorialSolution.h"


CombinatorialSolution::CombinatorialSolution(void)
{
}


CombinatorialSolution::~CombinatorialSolution(void)
{
}


BigUnsignedInteger CombinatorialSolution::Choose(BigUnsignedInteger n, BigUnsignedInteger &k)
{
	assert(k <= n);

	BigUnsignedInteger r = 1, d = 1;
	for(; d <= k; ++d, --n){
		BigUnsignedInteger gcd = CombinatorialSolution::GreatestCommonDivisor(r,d);
		r /= gcd;
		BigUnsignedInteger t = n / ( d / gcd);
		r *= t;
	}
	return r;
}

BigUnsignedInteger CombinatorialSolution::GreatestCommonDivisor(BigUnsignedInteger &a, BigUnsignedInteger &b){
	BigUnsignedInteger trash;
	for (;;) {
		if (b.isZero())
			return a;
		a.divide(b, trash);
		if (a.isZero())
			return b;
		b.divide(a, trash);
	}
}