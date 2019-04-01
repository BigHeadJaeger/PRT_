//一些公式中的特殊数学计算
#pragma once

const double PI = 3.141592653589793;
const double ZERO = 0.000000001;
const double M_INFINITE = 1e10f;

//阶乘
inline double Factorial(int num)
{
	if (num < 1)
		return 1.0;

	double result = 1.0;

	for (int i = 1; i <= num; i++)
	{
		result *= i;
	}

	return result;
}

//双阶乘
inline double DoubleFactorial(int num)
{
	//因为勒让德公式中进行双阶乘的数一定是奇数，所以只考虑奇数的双阶乘
	if (num <= 1)
		return 1.0;

	double result = 1.0;
	for (int i = num; i >1; i-=2)
	{
		result *= i;
	}

	return result;
}

//-1的n次方
inline int Minus1PowN(int n)
{
	if (n % 2 == 0)
		return 1;
	else
		return -1;
}

