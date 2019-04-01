//用来计算每一个球面调和函数
#pragma once
#include<math.h>
#include"Tool.h"



namespace SphericalTerm
{
	//归一化因子
	inline double N_lm(int l, int m)
	{
		//l=m时不用计算阶乘
		if (0==m)
		{
			double up = 2 * l + l;
			double down = 4 * PI;
			return sqrt(up / down);
		}
		else
		{
			double up = (2 * l + 1)*Factorial(l - abs(m));
			double down = (4 * PI)*(Factorial(l + abs(m)));
			return sqrt(up / down);
		}
	}

	//勒让德多项式（递归的形式定义）
	inline double Legendre(double x, int l, int m)
	{
		if (l == m)		//递归终止条件
		{
			return (double)Minus1PowN(m)*DoubleFactorial(2 * m - 1)*(double)pow((1 - x*x), (double)m / 2);
		}
		else if (l == m + 1)
		{
			return x*(2 * m + 1)*Legendre(x, m, m);
		}
		else
		{
			return (x*(2*l-1)*Legendre(x,l-1,m)-(l+m-1)*Legendre(x,l-2,m))/(l-m);
		}
	}

	//根据m的值计算当前基函数的值
	inline double SH(double theta, double phi, int l, int m)
	{
		double result = 0;
		if (m == 0)
		{
			result = N_lm(l, m)*Legendre(cos(theta), l, m);
		}
		else if (m > 0)
		{
			result = sqrt(2.0)*N_lm(l, m)*cos(m*phi)*Legendre(cos(theta), l, m);
		}
		else
		{
			result = sqrt(2.0)*N_lm(l, abs(m))*sin(abs(m)*phi)*Legendre(cos(theta), l, abs(m));
		}

		if (result <= ZERO)
			result = 0.0;


		return result;
	}
}