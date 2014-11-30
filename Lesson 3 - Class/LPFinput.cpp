#include <stdlib.h>
#include <stdint.h>
#include "mex.h"
#include "LPFclass.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	LPFclass* a;
	double* x, *y;
	int n;
	mxArray* input;

	// Argument checking.
	if(nrhs != 2) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly two arguments.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");
	if(!mxIsStruct(prhs[0]) || !mxGetField(prhs[0], 0, "pointer")) // Sanitize inputs.
		mexErrMsgTxt("Invalid first input.");
	if(!mxIsDouble(prhs[1]))
		mexErrMsgTxt("Second input must be a double.");

	input = mxGetField(prhs[0], 0, "pointer"); // Get a pointer to the array in the 'pointer' field, element 0 of the struct.

	a = *((LPFclass**) mxGetData(input)); // Cast the value to a pointer to an LPFclass and store in a. 

	x = ((double*) mxGetData(prhs[1])); // Get the input array.
	n = (int) mxGetNumberOfElements(prhs[1]); // Get the length of the input array.

	outMxArr = mxCreateDoubleMatrix(1, n, mxREAL); // Create an array for our output.

	y = ((double*)mxGetData(outMxArr)); // Get a pointer to the output array.
	
	// Copy the input array into the output array. (The input should not be modified, but LPFinput modifies the array passed to it to give the output).
	for (int i = 0; i < n; i++)
		y[i] = x[i];

	// This will crash MATLAB if a is not actually a pointer to an LPFclass.
	a->LPFinput(y, mxGetNumberOfElements(outMxArr)); // Actually run the low pass filter.

	plhs[0] = outMxArr;

	return;
}
