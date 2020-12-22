#include <cmath>
#include <iostream>
#include <string>

#include "TutorialConfig.h"

#ifdef USE_MYMATH
#include "MathFunctions.h"
#endif

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << argv[0] << " Version " << Tutorial_VERSION_MAJOR
				  << "." << Tutorial_VERSION_MINOR << std::endl;
		std::cout << "Usage: " << argv[0] << " number" << std::endl;
		return 1;
	}

	double inputValue = std::stod(argv[1]);

#ifdef USE_MYMATH
	double outputValue = mysqrt(inputValue);
	std::cout << "Mysqrt: The square root of " << inputValue
			  << " is " << outputValue << std::endl;
#else
	double outputValue = sqrt(inputValue);
	std::cout << "sqrt:  The square root of " << inputValue
			  << " is " << outputValue << std::endl;
#endif

	return 0;
}
