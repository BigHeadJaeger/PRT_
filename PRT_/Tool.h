//һЩ��ʽ�е�������ѧ����
#pragma once

const double PI = 3.141592653589793;
const double ZERO = 0.000000001;
const double M_INFINITE = 1e10f;

//�׳�
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

//˫�׳�
inline double DoubleFactorial(int num)
{
	//��Ϊ���õ¹�ʽ�н���˫�׳˵���һ��������������ֻ����������˫�׳�
	if (num <= 1)
		return 1.0;

	double result = 1.0;
	for (int i = num; i >1; i-=2)
	{
		result *= i;
	}

	return result;
}

//-1��n�η�
inline int Minus1PowN(int n)
{
	if (n % 2 == 0)
		return 1;
	else
		return -1;
}

