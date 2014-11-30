Lesson 2 - Simple Processing
=====
# Building & Examples
## addXY
```
>> mex addXY.c
Building with 'Microsoft Windows SDK 7.1 (C)'.
MEX completed successfully.
>> addXY(2.4,pi)

ans =

    5.5416

>>
```

## easyLPF
```
>> mex easyLPF.c
Building with 'Microsoft Windows SDK 7.1 (C)'.
MEX completed successfully.
>> for i=1:50
disp(easyLPF(1))
end
    0.0025
    0.0120
    0.0296
    0.0535
    0.0824
    0.1149
    0.1501
    0.1872
    0.2253
    0.2639
    0.3025
    0.3408
    0.3784
    0.4151
    0.4506
    0.4849
    0.5179
    0.5493
    0.5794
    0.6079
    0.6349
    0.6604
    0.6845
    0.7072
    0.7285
    0.7484
    0.7671
    0.7846
    0.8009
    0.8160
    0.8302
    0.8433
    0.8556
    0.8669
    0.8774
    0.8872
    0.8962
    0.9045
    0.9123
    0.9194
    0.9260
    0.9320
    0.9376
    0.9428
    0.9475
    0.9519
    0.9559
    0.9596
    0.9630
    0.9662
>> 
```

# Documentation
`ret = addXY(x, y);`<br />
ret is set equal to x+y.<br />
x and y are each a 1x1 double

`ret = easyLPF(x);`<br />
takes one input and returns one output that has put the input through a digital low pass filter.<br />
run this many times and the answer will be a low pass filtered version of the inputs.<br />
x is a 1x1 double

=====
[Next](../Lesson%203%20-%20Class/Class.md)
