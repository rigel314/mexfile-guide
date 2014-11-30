#include <stdint.h>
#include <windows.h>
#include <string.h>
#include "mex.h"

/* Compilation & Example
	mex winList.c
	A=winList()
	for i=1:length(A)
		disp(sprintf('%#08x: %s', uint64(A(i).hwnd), A(i).title))
	end
*/

// Comment this out return every window.
#define ONLY_VISIBLE

struct windowList
{
	struct windowList* next;
	char title[256];
	HWND hwnd;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char title_str[256];
	struct windowList* head = (struct windowList*) lParam;
	struct windowList* win;

	GetWindowText(hwnd, title_str, 256);
	#ifdef ONLY_VISIBLE
	if(GetWindowLong(hwnd, GWL_STYLE) & (WS_VISIBLE))
	{
	#endif
		win = (struct windowList*) mxCalloc(1, sizeof(struct windowList));
		if(head == NULL)
		{
			head = win;
		}
		else
		{
			struct windowList* i = head;
			for (; i->next; i = i->next);
			i->next = win;
		}
		strncpy(win->title, title_str, 255);
		win->hwnd = hwnd;
	#ifdef ONLY_VISIBLE
	}
	#endif
	return TRUE;
}

struct windowList* getWindows()
{
	struct windowList* head = NULL;
	int i = 0;

	EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)&head);

	return head;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	const char* names[] = {"hwnd", "title"};
	int numWins = 0, i = 0;
	struct windowList* winList;
	struct windowList* win;

	//Argument checking.
	if(nrhs != 0) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");

	winList = getWindows();

	for(win = winList; win->next; win = win->next)
		numWins++;

	outMxArr = mxCreateStructMatrix(1, numWins, 2, names);

	for(win = winList; win->next; win = win->next)
	{
		mxArray* hwndArr, *titleArr;

		hwndArr = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL);
		*((uint64_t*)mxGetData(hwndArr)) = (uint64_t)win->hwnd;
		mxSetField(outMxArr, i, "hwnd", hwndArr);

		titleArr = mxCreateString(win->title);
		mxSetField(outMxArr, i, "title", titleArr);

		i++;
	}

	plhs[0] = outMxArr;

	return;
}
