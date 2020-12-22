#include "MathFunctions.h"
#include <iostream>

double mysqrt(double x)
{
	if (x <= 0)
	{
		return 0;
	}

	double result = x;

	// 循环计算10次
	for (int i = 0; i < 10; ++i)
	{
		if (result <= 0)
		{
			result = 0.1;
		}
		double delta = x - (result * result);
		result = result + 0.5 * delta / result;
	}
	return result;
}
