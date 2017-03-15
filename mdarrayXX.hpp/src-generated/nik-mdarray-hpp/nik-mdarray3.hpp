/*########################################################################################################
#                                                                                                        #
#  High performance multidimensional matrices template. (For bounds checking info see the end of file.)  #
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

// The code below was automatically generated out of a template.

#ifndef __MDARRAY3__HPP__ 
#define __MDARRAY3__HPP__

#if not (defined _MDARRAY3_NO_BOUNDS_CHECK_ || defined _MDARRAY_ALL_NO_BOUNDS_CHECK_)
#include <cassert>
#define _DO_MDARRAY3_BOUNDS_CHECK_ assert((i0>=0) && (i0<dim0) && (i1>=0) && (i1<dim1) && (i2>=0) && (i2<dim2));
#define _DO_MDARRAY3_INIT_CHECK_   assert(data != NULL);
#else
#define _DO_MDARRAY3_BOUNDS_CHECK_
#define _DO_MDARRAY3_INIT_CHECK_
#endif

#include "nik-mdarrayX.hpp" // this is the common ancestor for matrices, just describing a part of the public interface, no real implementation

template<typename T>
class MDArray3 : public MDArrayX<T> {
	public:
		MDArray3();
		MDArray3(size_t d0, size_t d1, size_t d2);
    	MDArray3(size_t d0, size_t d1, size_t d2, T initval);
    	~MDArray3();
	    T& operator() (size_t i0, size_t i1, size_t i2);
    	T operator() (size_t i0, size_t i1, size_t i2) const;
		void setdimensions(size_t d0, size_t d1, size_t d2); // updating (re-allocating memory) or just creating (allocating memory)
		bool isvalid(); // true i.e. valid only if memory is allocated i.e. dimensions are set
    	T *getdataptr();
		void fill(T value);
		size_t getdimlen(int idx) const;
		int getnumdims() const;
	private:
    	T *data;
    	size_t dim0, dim1, dim2;
		void initialize(size_t d0, size_t d1, size_t d2);
};

template<typename T>
void MDArray3<T>::initialize(size_t d0, size_t d1, size_t d2) {
	const size_t max_size = (size_t) -1;
	double physical = (double) max_size;
	double requested = ((double)d0)*((double)d1)*((double)d2) * ((double) sizeof(T));	
	if (requested >= physical) err_exit("Amount of requested memory %.0fMB is bigger than can be physically allocated %.0fMB", requested/1024/1024, physical/1024/1024);
	
	dim0 = d0; dim1 = d1; dim2 = d2;
	try {
		data = new T[d0*d1*d2];
	}
	catch (std::bad_alloc& ba) {
		err_exit("cannot allocate %.0fMB of memory: %s", requested/1024/1024, ba.what());
	}					
}

template<typename T>
MDArray3<T>::MDArray3(size_t d0, size_t d1, size_t d2) {
	initialize(d0, d1, d2);
}

template<typename T>
MDArray3<T>::MDArray3(size_t d0, size_t d1, size_t d2, T initval) {
	initialize(d0, d1, d2);
	fill(initval);
}

template<typename T>
MDArray3<T>::MDArray3() {
	data = NULL;
}

template<typename T>
MDArray3<T>::~MDArray3() {
	delete[] data;
}

template<typename T>
void MDArray3<T>::setdimensions(size_t d0, size_t d1, size_t d2) {
	if (data) delete[] data;
	initialize(d0, d1, d2);
}

template<typename T>
bool MDArray3<T>::isvalid() {
	return (data != NULL);
}

template<typename T>
void MDArray3<T>::fill(T value) {
	_DO_MDARRAY3_INIT_CHECK_
	for (size_t i = 0; i < dim0*dim1*dim2; ++i) data[i] = value;
}

template<typename T>
inline T& MDArray3<T>::operator() (size_t i0, size_t i1, size_t i2) {
	_DO_MDARRAY3_INIT_CHECK_
    _DO_MDARRAY3_BOUNDS_CHECK_
    return data[i0*dim1*dim2 + i1*dim2 + i2];
}

template<typename T>
inline T MDArray3<T>::operator() (size_t i0, size_t i1, size_t i2) const {
	_DO_MDARRAY3_INIT_CHECK_
    _DO_MDARRAY3_BOUNDS_CHECK_
    return data[i0*dim1*dim2 + i1*dim2 + i2];
}

template<typename T>
inline T *MDArray3<T>::getdataptr() {
	_DO_MDARRAY3_INIT_CHECK_
    return data;
}

template<typename T>
inline size_t MDArray3<T>::getdimlen(int idx) const {
	_DO_MDARRAY3_INIT_CHECK_
	switch (idx) {
		case 0: return dim0;
		case 1: return dim1;
		case 2: return dim2;
		default: return 0;
	}
}

template<typename T>
inline int MDArray3<T>::getnumdims() const {
	return 3;
}
#endif

// Debugging bounds checks
/*
	to find where the bound check failed do the following:
	1) in the main program do not define _MDARRAY3_NO_BOUNDS_CHECK_ nor _MDARRAY_ALL_NO_BOUNDS_CHECK_ before including this header file
	2) recompile the main program with gdb symbols info, use switch -ggdb
	3) load main program e.g. gdb main.exe
	4) run it to make sure assertion fails: gdb> run
	5) set breakpoint on abort function called when assert fails: gdb> break abort
	6) run again to make it break on abort: gdb> run
	7) see what caused the assertion failure in the first place: gdb> backtrace
*/

// This is a sample for substitutions (dimension = 3) can be used for checking in the generated header file
/*
	3 = 3
	(i0>=0) && (i0<dim0) && (i1>=0) && (i1<dim1) && (i2>=0) && (i2<dim2) = (i0>=0) && (i0<dim0) && (i1>=0) && (i1<dim1) && (i2>=0) && (i2<dim2)
	size_t d0, size_t d1, size_t d2 = size_t d0, size_t d1, size_t d2
	d0*d1*d2 = d0*d1*d2
	d0, d1, d2 = d0, d1, d2
	size_t i0, size_t i1, size_t i2 = size_t i0, size_t i1, size_t i2
	dim0, dim1, dim2 = dim0, dim1, dim2
	dim0*dim1*dim2 = dim0*dim1*dim2
	dim0 = d0; dim1 = d1; dim2 = d2; = dim0 = d0; dim1 = d1; dim2 = d2;
	i0*dim1*dim2 + i1*dim2 + i2 = i0*dim1*dim2 + i1*dim2 + i2
	case 0: return dim0;
		case 1: return dim1;
		case 2: return dim2; = case 0: return dim0; ... case 2: return dim2;
*/
