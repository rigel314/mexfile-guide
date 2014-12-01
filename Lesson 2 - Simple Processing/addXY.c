#include <stdint.h>
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	const mwSize dims[2] = {1, 1}; // Size of our output data

	double x,y; // Input variables.

	double* data; // Pointer type for an intermediate step

	// Argument checking.
	if(nrhs != 2) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly two arguments.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");
	if(!mxIsDouble(prhs[0]) || !mxIsDouble(prhs[1])) // Sanitize our inputs
		mexErrMsgTxt("Inputs must be doubles.");

	// Create our return array
	// 2 dimensional, 1x1(as declared above in dims), IEEE Double Precision type for each cell, no imaginary parts
	outMxArr = mxCreateNumericArray(2, dims, mxDOUBLE_CLASS, mxREAL);

	// mxCreateNumericArray allocated space for an array of doubles's, one element long
	data = mxGetData(outMxArr); // Grab a pointer to the beginning of the array.
	
	// read our input
	x = *((double*)mxGetData(prhs[0])); // Get a pointer to the data of the first argument, cast it to a double pointer and get the value of said pointer.
	y = *((double*)mxGetData(prhs[1])); // Get a pointer to the data of the second argument, cast it to a double pointer and get the value of said pointer.
	
	data[0] = x+y; // Write a value.

	plhs[0] = outMxArr;

	return;
}
