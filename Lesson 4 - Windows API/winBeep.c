#include <windows.h>
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	// Argument checking.
	if(nrhs != 0) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly zero arguments.");
	if(nlhs != 0) // Left hand side (number of return values)
		mexErrMsgTxt("Returns exactly zero things.");

	Beep(1000, 1000); // Defined in windows.h
	Beep(2000, 1000); // Beep(int freq, int ms)

	return;
}
