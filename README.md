Multidimensional Arrays for C++
======

### Introduction

This C++ library provides multidimensional arrays that are straightforward to use and fast. After just including the header files e.g.
```c
#include "nik-mdarray-hpp/nik-mdarray2.hpp"
#include "nik-mdarray-hpp/nik-mdarray4.hpp"
``` 
you can create an array of any size holding any type of elements e.g.
```c
MDArray2<int> A(200, 4000); // two dimensional array of 200 x 4000 'int' elements
MDArray4<float> B(2, 4, 3, 5); // four dimensional array of 2 x 4 x 3 x 5 'float' elements
```
then you can easily operate with the elements of these arrays e.g.
```c
A(0, 0) = 1; // set the value of one element
B.fill(3.1415926); // set all elements in the array
B(i, j, k, m) = B(m, k, j, i); // set the value of one element using the value of the another element
float *x = &B(i, j, k, m); // using a pointer to an element 
```
The test file `test/mdarray_test.cpp` is included to demonstrate how it works.

### Installation
Just copy the folder `nik-mdarray-hpp` and the file `nik-log-txt-tmr-exit.hpp` to your include path and you are good to go. 

### Internals

The source code header files for arrays of different dimensions are generated using a Perl script and a template common for all dimensions. Header files contain array class templates to allow for any type of array elements. Inline element access functions (operators) allow for a full speed optimized compiled binary code.

Here are the features of this multidimensional arrays library:
* any (reasonable) dimensionality
* dynamically allocated (no overflow of stack)
* fast: static subscripting (no internal pointers)
* fast: inline functions - no function call overhead
* intuitive code e.g.: `a(i, j, k) = 1;`
* dependence free - just a header has to be included
* flexible: can hold char, int, float,...
* portable (gcc) tested on Linux and Windows

The supplied header file `nik-log-txt-tmr-exit.hpp` contains utility functions for logging and is required by multidimensional arrays for error reporting e.g. not enough memory.

The `getdataptr()` method and a pointer to an element e.g. `&B(i, j, k, 0)` can be used for low level operations e.g. loading data from file directly into the array or its specific row.

You can `#define _MDARRAY_ALL_NO_BOUNDS_CHECK_` to remove bound checks and make your binary faster.

### Acknowledgement 

This work is supported by the Synergy Grant 610028 IMBALANCE-P: Effects of phosphorus limitations on Life, Earth system and Society (Horizon 2020 European Union Funding for Research and Innovation).

### License (BSD-3-Clause)
                                                                                                     
Copyright 2017 Nikolay Khabarov, International Institute for Applied Systems Analysis (IIASA). Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:                                                      
                                                                                                     
1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.                                                                     
                                                                                                     
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.                                                                                     
                                                                                                     
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.         
                                                                                                     
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                      
