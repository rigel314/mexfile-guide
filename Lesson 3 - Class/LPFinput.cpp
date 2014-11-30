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
	if(!mxIsStruct(prhs[0]) || !mxGetField(prhs[0], 0, "pointer"))
		mexErrMsgTxt("Invalid first input.");
	if(!mxIsDouble(prhs[1]))
		mexErrMsgTxt("Second input must be a double.");

	input = mxGetField(prhs[0], 0, "pointer");

	a = *((LPFclass**) mxGetData(input));

	x = ((double*) mxGetData(prhs[1]));
	n = (int) mxGetNumberOfElements(prhs[1]);

	outMxArr = mxCreateDoubleMatrix(1, n, mxREAL);

	y = ((double*)mxGetData(outMxArr));
	for (int i = 0; i < n; i++)
	{
		y[i] = x[i];
	}

	a->LPFinput(y, mxGetNumberOfElements(outMxArr));

	plhs[0] = outMxArr;

	return;
}
