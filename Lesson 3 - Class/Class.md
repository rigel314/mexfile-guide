Lesson 3 - Class
=====
# Building & Examples
## LPFinit
```
>> mex LPFinit.cpp LPFclass.cpp
Building with 'Microsoft Windows SDK 7.1 (C++)'.
MEX completed successfully.
>> lpf = LPFinit()

lpf = 

    pointer: 1142309120

>>
```

## LPFinput
```
>> mex LPFinput.cpp LPFclass.cpp
Building with 'Microsoft Windows SDK 7.1 (C++)'.
MEX completed successfully.
>> LPFinput(lpf, [1,1,1,1,1,1,1,1,1])

ans =

    0.0025    0.0120    0.0296    0.0535    0.0824    0.1149    0.1501    0.1872    0.2253

>>
```

## LPFdestroy
```
>> mex LPFdestroy.cpp LPFclass.cpp
Building with 'Microsoft Windows SDK 7.1 (C++)'.
MEX completed successfully.
>> LPFdestroy(lpf)
>>
```

# Documentation
`ret = LPFinit();`<br />
ret is set equal to an instance of an LPF class.  Except MEX files can't return a MATLAB class, so I returned a MATLAB struct with a pointer.

`ret = LPFinput(lpf, x);`<br />
takes one input and returns one output that has put the input through a digital low pass filter.<br />
run this many times and the answer will be a low pass filtered version of the inputs.<br />
x is a 1x1 double<br />
lpf is a struct returned by LPFinit().

`ret = LPFinput(lpf, x);`<br />
ret is a matrix the same legth as x with `ret(i) = LPFinput(x(i))` starting from the beginning.<br />
x is a 1xN double<br />
lpf is a struct returned by LPFinit().

`ret = LPFdestroy(lpf);`<br />
frees the memory allocated to lpf by LPFinit().<br />
lpf is a struct returned by LPFinit().

====
[Next](../Lesson%204%20-%20Windows%20API/Windows%20API.md)
