#include <stdint.h>
#include "mex.h"

// Pointer that should remain in memory until `clear functions`.  MATLAB will repopulate static globals.
static double* ioData = NULL;

// This function is called when `clear functions` is called from MATLAB.
// It must return void and take no arguments, but the function name is registered by a call to mexAtExit().
void cleanUp()
{
	if(ioData)
	{
		mxFree(ioData); // Un-allocate the memory used for ioData.
		ioData = NULL;
	}
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	const mwSize dims[2] = {1, 1}; // Size of our output data

	double x, y; // Input and output variables.

	double* data; // Pointer type for an intermediate step
	int i,j; // For loop counters

	// Argument checking.
	if(nrhs != 1) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");
	if(!mxIsDouble(prhs[0])) // Sanitize input.
		mexErrMsgTxt("Input must be a double.");

	if(!ioData) // If ioData hasn't been set.
	{
		ioData = mxCalloc(sizeof(double), 4); // Allocate memory for the values that need to be remembered by the filter.
		mexMakeMemoryPersistent(ioData); // Tell MATLAB to persist the memory between calls to this function.
		mexAtExit(&cleanUp); // Register a function to happen at `clear functions` so as not to leak memory.
	}

	x = *((double*)mxGetData(prhs[0])); // Get the input value.

	// Create our return array
	// 2 dimensional, 1x1(as declared above in dims), IEEE Double Precision type for each cell, no imaginary parts
	outMxArr = mxCreateNumericArray(2, dims, mxDOUBLE_CLASS, mxREAL);

	y = .0025*ioData[0] + .005*ioData[1] + .0025*x - .81*ioData[2] + 1.8*ioData[3]; // Actually do the calculation for the filter.

	*((double*)mxGetData(outMxArr)) = y; // Set the output value.

	// Remember the necessary values for this filter.
	ioData[0] = ioData[1];	// x[n-2] (two inputs ago)
	ioData[1] = x;			// x[n-1] (last input)
	ioData[2] = ioData[3];	// y[n-2] (two outputs ago)
	ioData[3] = y;			// y[n-1] (last output)

	plhs[0] = outMxArr;

	return;
}
