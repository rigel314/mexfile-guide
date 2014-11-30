#include <stdint.h>
#include "mex.h"
#include "LPFclass.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	const mwSize dims[2] = {1, 1}; // Size of our output data
	LPFclass* a;
	mxArray* input;

	// Argument checking.
	if(nrhs != 1) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs != 0) // Left hand side (number of return values)
		mexErrMsgTxt("Returns nothing.");
	if(!mxIsStruct(prhs[0]) || !mxGetField(prhs[0], 0, "pointer")) // Sanitize input.
		mexErrMsgTxt("Invalid input.");

	input = mxGetField(prhs[0], 0, "pointer"); // Get a pointer to the array in the 'pointer' field, element 0 of the struct.

	a = *((LPFclass**) mxGetData(input)); // Cast the value to a pointer to an LPFclass and store in a. 

	// This will crash MATLAB if a is not actually a pointer to an LPFclass.
	delete a; // Free the memory pointed to by a.

	return;
}
