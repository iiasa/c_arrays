/*########################################################################################################
#                                                                                                        #
#  This is an example of how to use the high performance multidimensional arrays.                      #
#                                                                                                        #
#  The 3-Clause BSD License:                                                                             #
#                                                                                                        #
#  Copyright 2017 Nikolay Khabarov, International Institute for Applied Systems Analysis (IIASA).        #
#  Redistribution and use in source and binary forms, with or without modification, are permitted        #
#  provided that the following conditions are met:                                                       #
#                                                                                                        #
#  1. Redistributions of source code must retain the above copyright notice, this list of conditions     #
#     and the following disclaimer.                                                                      #
#                                                                                                        #
#  2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions  #
#     and the following disclaimer in the documentation and/or other materials provided with the         #
#     distribution.                                                                                      #
#                                                                                                        #
#  3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse  #
#     or promote products derived from this software without specific prior written permission.          #
#                                                                                                        #
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR        #
#  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND      #
#  FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR            #
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL     #
#  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,     #
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER    #
#  IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT     #
#  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                       #
#                                                                                                        #
########################################################################################################*/

/*########################################################################################################
# Acknowledgement:                                                                                       #
# This work is supported by the Synergy Grant 610028 IMBALANCE-P: Effects of phosphorus limitations      #
# on Life, Earth system and Society (Horizon 2020 European Union Funding for Research and Innovation).   #
########################################################################################################*/

#include <cstdio>
#include <cstdlib>
#include <cassert>

//#define _MDARRAY2_NO_BOUNDS_CHECK_
//#define _MDARRAY_ALL_NO_BOUNDS_CHECK_

#include "nik-mdarray-hpp/nik-mdarray2.hpp"
#include "nik-mdarray-hpp/nik-mdarray3.hpp"

int main() {
    // normal use:
    {
        MDArray2<double> A(1, 2);
        A(0, 0) = 1;
        A.fill(3.1415926);
        printf("A(0, 1) = %f, dimlen1 = %d\n", A(0, 1), A.getdimlen(1));       
        // printf("A(1, 0) = %f, dimlen1 = %d\n", A(1, 0), A.getdimlen(1)); // uncomment to see how bounds check works
    }
    // below we want to change dimension lengths of a3 dynamically:
    {
        MDArray3<float> A;
        if (A.isvalid()) printf("A is valid\n"); else printf("A is invalid\n");
        A.setdimensions(1, 2, 2);
        A(0, 1, 1) = 1;
        printf("A(0, 0, 1) = %f, dimlen1 = %d\n", A(0, 1, 1), A.getdimlen(0));
        A.setdimensions(2, 2, 2);
        A.fill(3.1415926);
        float *x = &A(0, 0, 0);
        printf("A(1, 1, 1) = %f, dimlen1 = %d, *x = %f\n", A(1, 1, 1), A.getdimlen(0), *x);
        // printf("A(2, 2, 2) = %f, dimlen1 = %d\n", A(2, 2, 2), A.getdimlen(1)); // uncomment to see how bounds check works
    }
} 
