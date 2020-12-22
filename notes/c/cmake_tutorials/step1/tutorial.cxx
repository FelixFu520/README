#include <stdio.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include "TutorialConfig.h"

using namespace std;

int main(int argc, char *argv[]){
	if(argc <2){
		fprintf(stdout, "%s Version %d.%d\n", argv[0],
				Tutorial_VERSION_MAJOR,
				Tutorial_VERSION_MINOR);
		fprintf(stdout, "Usage:%s number\n", argv[0]);
		return 1;
	}
	double inputValue = atof(argv[1]);
	double outputValue = sqrt(inputValue);
	fprintf(stdout, "The square root of %g is %g \n",
			inputValue, outputValue);
	return 0;

}
