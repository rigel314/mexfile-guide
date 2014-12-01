#include <stdint.h>
#include "mex.h"
#include "LPFclass.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	mxArray* pointer;
	const mwSize dims[2] = {1, 1}; // Size of our output data
	LPFclass* a = new LPFclass(); // Allocate memory in a way that MATLAB doesn't know about so we can keep it around without mxMakeMemoryPersistant().
	const char* names = "pointer";

	// Argument checking.
	if(nrhs != 0) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs != 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");

	// MATLAB structs have fields and indexes.
	// Every combination of index and field need to have a MATLAB array(which could be another struct or a cell array or a numeric array).
	// Then you must call mxSetField() to set the field at a specific index to an existing MATLAB array.

	// I chose to return a struct because returning a number made it too easy to pass an invalid number.  There is no way to check an invalid number
	// in this implementation.  You could make another function and a global static that maps arbitrary numbers to actual pointers, but blar...

	outMxArr = mxCreateStructArray(2, dims, 1, &names); // Create a 1x1 struct with 1 field.
	pointer = mxCreateNumericArray(2, dims, mxUINT64_CLASS, mxREAL); // Create an array to put in the 'pointer' field of the first element of the struct array.
	
	// Cast the return of mxGetData() as a pointer to a pointer to an LPFclass, then dereference to store our pointer.
	*((LPFclass**)mxGetData(pointer)) = a; // Put a value in the numeric array.

	mxSetField(outMxArr, 0, "pointer", pointer); // Set the numeric array as the value of the 'pointer' field of the first element of the struct array.

	plhs[0] = outMxArr;

	return;
}
