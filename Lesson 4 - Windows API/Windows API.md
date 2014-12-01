Lesson 4 - Windows API
=====
# Building & Examples
## winBeep
```
>> mex winBeep.c
Building with 'Microsoft Windows SDK 7.1 (C)'.
MEX completed successfully.
>> winBeep()
>>
```

## winList
```
>> mex winList.c
Building with 'Microsoft Windows SDK 7.1 (C)'.
MEX completed successfully.
>> ret = winList()

ret = 

1x9 struct array with fields:

    hwnd
    title

>> for i=1:length(ret)
disp(sprintf('%#08x: %s', uint64(ret(i).hwnd), ret(i).title))
end
0x01011a: Start
0x01010e: 
0x040554: MATLAB R2014b
0x0904d0: rigel314/mexfile-guide - Google Chrome
0x0c0582: -zsh
0x0c06bc: -zsh
0x170572: Lesson 4 - Windows API
0x020150: Glint
>> 
```

# Documentation
`winBeep();`<br />
Causes a one second beep at 1kHz then a one second beep at 2kHz.

`ret = winList();`<br />
ret is set equal to a struct array with members "hwnd" and "title".  Each element in the struct array has a window's title and its hwnd ID.
