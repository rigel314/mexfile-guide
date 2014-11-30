#include <stdint.h>
#include "mex.h"
#include "LPFclass.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	const mwSize dims[2] = {1, 1}; // Size of our output data
	LPFclass* a;
	mxArray* input;

	//Argument checking.
	if(nrhs != 1) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs != 0) // Left hand side (number of return values)
		mexErrMsgTxt("Returns nothing.");
	if(!mxIsStruct(prhs[0]) || !mxGetField(prhs[0], 0, "pointer"))
		mexErrMsgTxt("Invalid input.");

	input = mxGetField(prhs[0], 0, "pointer");

	a = *((LPFclass**) mxGetData(input));

	delete a;

	return;
}
