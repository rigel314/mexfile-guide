#include "LPFclass.h"

// Constructor
LPFclass::LPFclass()
{
	y2=y1=x2=x1=0; // Set all instance variables to zero.
}

// Input a single value.
double LPFclass::LPFinput(double x)
{
	double y = .0025*x2 + .005*x1 + .0025*x - .81*y2 + 1.8*y1; // Run the calculation.

	// Set the memory of the filter.
	x2 = x1;
	x1 = x;
	y2 = y1;
	y1 = y;
	return y;
}

// Input a list of values.
// x serves as input and output.
void LPFclass::LPFinput(double* x, int len)
{
	int i;
	for (i = 0; i < len; i++)
	{
		x[i] = this->LPFinput(x[i]);
	}
}
