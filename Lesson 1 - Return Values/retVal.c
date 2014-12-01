#include <stdint.h>
#include "mex.h"

// This function has to be called mexFunction; must return void; and must take an int, an mxArray*, an int, and a const mxArray*.
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	const mwSize dims[2] = {1, 1}; // Size of our output data
	uint16_t* data; // Pointer type for an intermediate step

	// Argument checking.
	if(nrhs != 0) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly zero arguments.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");

	// Create our return array
	// 2 dimensional, 1x1(as declared above in dims), 16-bit Integer type for each element, no imaginary parts
	outMxArr = mxCreateNumericArray(2, dims, mxINT16_CLASS, mxREAL);

	// mxCreateNumericArray allocated space for an array of uint16_t's, one element long
	data = mxGetData(outMxArr); // Grab a pointer to the beginning of the array.
	data[0] = 4; // Write a value to the first(and only) element of the array.

	plhs[0] = outMxArr; // Put the return array in the first output.

	return;
}
