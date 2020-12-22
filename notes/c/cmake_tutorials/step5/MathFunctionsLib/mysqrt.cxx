#include "MathFunctions.h"
#include "TutorialConfig.h"
#include <iostream>
#include <cmath>
double mysqrt(double x)
{
	if (x <= 0)
	{
		return 0;
	}

	// 如果有log和exp就使用它们
#if defined(HAVE_LOG) && defined(HAVE_EXP)
	double result = exp(log(x) * 0.5);
	std::cout << "Computing sqrt of " << x
			  << " to be " << result << " using log" << std::endl;
#else
	double result = x;

	//循环十次
	for (int i = 0; i < 10; ++i)
	{
		if (result <= 0)
		{
			result = 0.1;
		}
		double delta = x - (result * result);
		result = result + 0.5 * delta / result;
		std::cout << "Computing sqrt of " << x
				  << " to be " << result << std::endl;
	}
#endif
	return result;
}
