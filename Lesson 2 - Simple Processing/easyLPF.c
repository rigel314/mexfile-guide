#include <stdint.h>
#include "mex.h"

static double* ioData = NULL;

void cleanUp()
{
	if(ioData)
	{
		mxFree(ioData);
		ioData = NULL;
	}
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	const mwSize dims[2] = {1, 1}; // Size of our output data

	double x, y; // Input and output variables.

	double* data; // Pointer type for an intemediate step
	int i,j; // For loop counters

	//Argument checking.
	if(nrhs != 1) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");
	if(!mxIsDouble(prhs[0]))
		mexErrMsgTxt("Input must be a double.");

	if(!ioData)
	{
		// Create our return array
		// 2 dimensional, 1x1(as declared above in dims), IEEE Double Precision type for each cell, no imaginary parts
		ioData = mxCalloc(sizeof(double), 4);
		mexMakeMemoryPersistent(ioData);
		mexAtExit(&cleanUp);
	}

	x = *((double*)mxGetData(prhs[0]));

	outMxArr = mxCreateNumericArray(2, dims, mxDOUBLE_CLASS, mxREAL);
	y = .0025*ioData[0] + .005*ioData[1] + .0025*x - .81*ioData[2] + 1.8*ioData[3];

	*((double*)mxGetData(outMxArr)) = y;

	ioData[0] = ioData[1];	// x[n-2]
	ioData[1] = x;			// x[n-1]
	ioData[2] = ioData[3];	// y[n-2]
	ioData[3] = y;			// y[n-1]

	plhs[0] = outMxArr;

	return;
}
