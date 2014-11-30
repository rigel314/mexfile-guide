#include <stdint.h>
#include <windows.h>
#include <string.h>
#include "mex.h"

// Comment this out return every window.
#define ONLY_VISIBLE

// C struct to generate then copy into a MATLAB struct.
struct windowList
{
	struct windowList* next;
	char title[256];
	HWND hwnd;
};

// Registered to be called by EnumWindows().
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char title_str[256]; // Used to temporarily hold the title of a window.
	struct windowList* head = (struct windowList*) lParam; // Get the value of head from lParam.
	struct windowList* win; // Linked list iterator.

#ifdef ONLY_VISIBLE
	if(GetWindowLong(hwnd, GWL_STYLE) & (WS_VISIBLE))
	{
#endif
		GetWindowText(hwnd, title_str, 255); // Get the window text.
		win = (struct windowList*) mxCalloc(1, sizeof(struct windowList)); // Allocate memory for a new linked list node.
		if(head == NULL)
		{
			head = win; // Set head if it's not set.
		}
		else
		{
			struct windowList* i = head;
			for (; i->next; i = i->next); // Iterate to the last element in the linked list.
			i->next = win; // Set next of the last node to the newly created node.
		}
		strncpy(win->title, title_str, 255); // Copy the title into the new node.
		win->hwnd = hwnd; // Set hwnd in the new node.
#ifdef ONLY_VISIBLE
	}
#endif
	return TRUE;
}

struct windowList* getWindows()
{
	struct windowList* head = NULL;
	int i = 0;

	EnumWindows((WNDENUMPROC)EnumWindowsProc, (LPARAM)&head); // Call EnumWindows().  It will call EnumWindowsProc().
	// Notice that the address of head is passed.  LPARAM is unused by EnumWindows() it will just be passed directly to EnumWindowsProc().

	// Since we passed the address of head, it can be modified.
	return head;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	mxArray* outMxArr; // Pointer for our output data
	const char* names[] = {"hwnd", "title"}; // Names for the fields of our output struct.
	int numWins = 0, i = 0; // Counter and iterator.
	struct windowList* winList; // C struct to hold the data before putting it in a MATLAB struct.
	struct windowList* win; // Linked list iterator.

	// Argument checking.
	if(nrhs != 0) // Right hand side (a.k.a. 'argc' or 'nargin')
		mexErrMsgTxt("Takes exactly one argument.");
	if(nlhs > 1) // Left hand side (number of return values)
		mexErrMsgTxt("Only returns one thing.");

	winList = getWindows(); // Read all visible windows into a C struct.

	// Count windows.
	for(win = winList; win && win->next; win = win->next)
		numWins++;

	outMxArr = mxCreateStructMatrix(1, numWins, 2, names); // Create the output struct.

	// Copy the values from the C struct into the MATLAB struct.
	for(win = winList; win && win->next; win = win->next)
	{
		mxArray* hwndArr, *titleArr;

		hwndArr = mxCreateNumericMatrix(1, 1, mxUINT64_CLASS, mxREAL); // Create an array to store this window's hwnd ID.
		*((uint64_t*)mxGetData(hwndArr)) = (uint64_t)win->hwnd; // Store this window's hwnd ID in the array that was just created.
		mxSetField(outMxArr, i, "hwnd", hwndArr); // Set the array as the value for the 'hwnd' field of this element of the struct.

		titleArr = mxCreateString(win->title); // Create a string by copying this window's title string.
		mxSetField(outMxArr, i, "title", titleArr); // Set the string as the value for the 'title' field of this element of the struct.

		i++; // Increment the iterator.
	}

	plhs[0] = outMxArr;

	return;
}
