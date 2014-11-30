#include <stdint.h>
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	const mwSize dims[2] = {10, 10}; // Size of our output data
	uint16_t* data; // Pointer type for an intemediate step
	int i,j; // For loop counters

	//Argument checking.
	if(nrhs != 0) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly zero arguments.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");

	// Create our return array
	// 2 dimensional, 10x10(as declared above in dims), 16-bit Integer type for each cell, no imaginary parts
	outMxArr = mxCreateNumericArray(2, dims, mxINT16_CLASS, mxREAL);

	// mxCreateNumericArray allocated space for an array of uint16_t's, 100 elements long
	data = mxGetData(outMxArr); // Grab a pointer to the beginning of the array.
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			data[10*j+i] = (10*i+j); // Write a value.
		}
	}

	plhs[0] = outMxArr;

	return;
}
