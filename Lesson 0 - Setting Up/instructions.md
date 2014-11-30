Using C/MEX with MATLAB
=====
# 1. You need a compiler.
- Supported compilers can be found here: [MATLAB 2014b](http://www.mathworks.com/support/compilers/R2014b/index.html).
- I suggest the Microsoft Windows SDK 7.1, since that it what I used and included.
- I had some trouble installing the compiler, but the fix was to uninstall every Microsoft Redistributable Library 2010. 

# 2. Using mex
- You can run mex from inside MATLAB or from a command line.
  - Example: `mex exampleFunc.c`
  - This will compile `exampleFunc.c` into a file called `exampleFunc.mex` which can be called as a function as `exampleFunc`
- You can always run `help mex` in MATLAB for more information such as how to specify output architecture, name, etc.

# 3. [Example 1 - Return Values](../Lesson%201%20-%20Return%20Values/Return%20Values.md)
- Returning an individual value.
  - mexErrMsgTxt - display an error
  - mxCreateNumericArray - have MATLAB create an array
  - mxGetData - get a pointer to the actual data from a MATLAB array
- Returning a list of values.
  - No new MATLAB functions.

# 4. [Example 2 - Simple Processing](../Lesson%202%20-%20Simple%20Processing/Simple%20Processing.md)
- Addition.
  - No new MATLAB functions.
- Low pass filter implemented as a singleton. (A class that can only be instantiated once)
  - mxCalloc - allocate memory
  - mexMakeMemoryPersistent - tell MATLAB not to auto clear certain memory
  - mxFree - free allocated memory
  - mexAtExit - tell MATLAB to call a function when `clear functions` is run

# 5. [Example 3 - Class](../Lesson%203%20-%20Class/Class.md)
- Low pass filter implemented as a class that can be instantiated many times.
  - mxIsStruct - test if array is a struct array
  - mxGetField - get a field from a struct array
  - mxSetField - set a field from in a struct array
  - mxCreateStructArray - have MATLAB create a struct array
  - mxIsDouble - test if array is a double array
  - mxGetNumberOfElements - get the length of an array
  - mxCreateDoubleMatrix - have MATLAB create a double array


# 6. [Example 4 - Windows API](../Lesson%204%20-%20Windows%20API/Windows%20API.md)
- Beep.
  - Windows API
    - Beep - make a beep from the motherboard speaker at a frequency for a duration
- Window list.
  - Windows API
    - EnumWindows - list all of the windows on the system
    - GetWindowText - get the window title for a specific window
    - GetWindowLong - get properties about the window
  - MATLAB API
    - mxCreateStructMatrix - have MATLAB create a struct array
