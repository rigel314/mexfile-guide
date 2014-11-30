#include <stdint.h>
#include "mex.h"
#include "LPFclass.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	mxArray* pointer;
	const mwSize dims[2] = {1, 1}; // Size of our output data
	LPFclass* a = new LPFclass();
	const char* names = "pointer";

	//Argument checking.
	if(nrhs != 0) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs != 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");

	outMxArr = mxCreateStructArray(2, dims, 1, &names);
	pointer = mxCreateNumericArray(2, dims, mxUINT64_CLASS, mxREAL);
	*((LPFclass**)mxGetData(pointer)) = a;

	mxSetField(outMxArr, 0, "pointer", pointer);

	plhs[0] = outMxArr;

	return;
}
