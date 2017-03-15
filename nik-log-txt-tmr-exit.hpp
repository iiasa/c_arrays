/*########################################################################################################
#                                                                                                        #
#  Here are utility functions for:                                                                       #
#      * Logging to a file                                                                               #
#      * Text files output                                                                               #
#      * Timer                                                                                           #
#      * Exit                                                                                            #
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

#ifndef _nik_include_logging_timer_exit_def_
#define _nik_include_logging_timer_exit_def_ 

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <cstdarg>
#include <cfloat>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/time.h>

///////////////////////////////////////////////////////////////////////////
// utility classes (used by utility functions below, a user should better use the function than a class)
///////////////////////////////////////////////////////////////////////////

void printflog(const char *fmt, ...); // forward ref for logging output to main log file

//// Text file writer class
class NikTextFileWriter {
	public:
		NikTextFileWriter();
		~NikTextFileWriter();
		void open(const char *filepath, const char *filename); // if not opened will print to screen only
		void open(const char *fullfilename); // if not opened will print to screen only
		void openfnfs(const char *fmt, ...); // file name is formatted string
		void printf(const char *fmt, ...);
		void vprintf(const char *fmt, va_list args);
	private:
		FILE *fh;
};
NikTextFileWriter::NikTextFileWriter() {
	fh = NULL;
}
void NikTextFileWriter::open(const char *filepath, const char *filename) {
	char fullfilename[1024];
	snprintf(fullfilename, 1024, "%s%s", filepath, filename);
	open(fullfilename);
}
void NikTextFileWriter::open(const char *fullfilename) {
	if (fh != NULL) fclose(fh);
	fh = NULL;
	if ( (fh = fopen(fullfilename, "w")) == NULL ) { 
		printflog("* Error: can't open text file '%s' for writing.\n", fullfilename);	
		exit(-1);
	}
	printflog("Opened file '%s' for output.\n", fullfilename);	
}
NikTextFileWriter::~NikTextFileWriter() {
    if (fh != NULL) {
		fclose(fh);
	}
}
void NikTextFileWriter::openfnfs(const char *fmt, ...) {
	va_list args;
    va_start(args, fmt);	
	char fullfilename[1024];
	vsnprintf(fullfilename, 1024, fmt, args); 
	open(fullfilename);
	va_end(args); // need to call va_end() after va_start() before return
}
void NikTextFileWriter::printf(const char *fmt, ...) {
	va_list args;
    va_start(args, fmt);	
	if (fh != NULL) std::vfprintf(fh, fmt, args); 
	va_end(args); // need to call va_end() after va_start() before return
}
void NikTextFileWriter::vprintf(const char *fmt, va_list args) {
	if (fh != NULL) std::vfprintf(fh, fmt, args); 
}

//// Logger class
class NikLogger {
	public:
		NikLogger();
		~NikLogger();
		void open(const char *logpath, const char *logfname); // if not opened will print to screen only
		void open(const char *fnamelog); // if not opened will print to screen only
		void printf(const char *fmt, ...);
		void vprintf(const char *fmt, va_list args);
	private:
		FILE *fh;
};
NikLogger::NikLogger() {
	fh = NULL;
}
void NikLogger::open(const char *logpath, const char *logfname) {
	char fnamelog[1024];
	snprintf(fnamelog, 1024, "%s%s", logpath, logfname);
	open(fnamelog);
}
void NikLogger::open(const char *fnamelog) {
	if (fh != NULL) fclose(fh);
	fh = NULL;
	if ( (fh = fopen(fnamelog, "w")) == NULL ) { 
		std::printf("* Error: can't open log file '%s' for writing.\n", fnamelog);	
		exit(-1);
	}
	std::printf("Writing log to '%s'\n", fnamelog);	
	time_t now;
	time(&now);
	printf("Log started: %s", ctime(&now));	
}
NikLogger::~NikLogger() {
    if (fh != NULL) {
		time_t now;
		time(&now);
		printf("Log closed: %s", ctime(&now));		
		fclose(fh);
	}
}
void NikLogger::printf(const char *fmt, ...) {
	va_list args;
	va_list args2;
    va_start(args, fmt);	
	va_copy(args2, args); // need to copy args for additional vXprintf() calls (see http://www.bailopan.net/blog/?p=30) --Nik
    std::vprintf(fmt, args);
	if (fh != NULL) std::vfprintf(fh, fmt, args2); 
	va_end(args); // neded to call va_end() after va_start() before return
}
void NikLogger::vprintf(const char *fmt, va_list args) {
	va_list args2;
	va_copy(args2, args); // need to copy args for additional vXprintf() calls (see http://www.bailopan.net/blog/?p=30) --Nik
    std::vprintf(fmt, args);
	if (fh != NULL) std::vfprintf(fh, fmt, args2); 
}

//// Timer class (using some ideas from http://berenger.eu/blog/2010/09/01/c-time-clock-time-manager-cross-platform-windows-posix/)
class NikTimer {
	public:
		NikTimer(NikLogger *logger); 
		void start();
		void show();
	private:		
		double time_start, time_curr, time_last;
		NikLogger *logger;
		double nik_clock(); // compatible with unix and windows
};
NikTimer::NikTimer(NikLogger *lgr) {
	logger = lgr;
}
void NikTimer::start() {
	time_start = time_last = nik_clock();
}
void NikTimer::show() {
	time_curr = nik_clock();
	double last = time_curr - time_last;
	double total = time_curr - time_start;
	if (fabs(last) < FLT_EPSILON) last = 0;		// ignore too small difference especially as it might be negative 1e-10 due to rounding errors
	if (fabs(total) < FLT_EPSILON) total = 0;	// -the-same-
	(*logger).printf("Elapsed time: last = %.2f sec, total = %.2f sec\n", last, total);
	time_last = time_curr;
}
double NikTimer::nik_clock() {
	timeval t;
	gettimeofday(&t, NULL); // works fine under mingw --Nik
	return t.tv_sec + ((double)t.tv_usec)/1000000.0;
}

///////////////////////////////////////////////////////////////////////////
// some globals (used by utility functions below, not by a user)
///////////////////////////////////////////////////////////////////////////

NikLogger nik_global_log_file = NikLogger();
NikTimer nik_global_timer = NikTimer(&nik_global_log_file);

///////////////////////////////////////////////////////////////////////////
// utility functions (to be used directly by a user)
///////////////////////////////////////////////////////////////////////////

void starttimer() {
	nik_global_timer.start();
}

void showtimer() {
	nik_global_timer.show();
}

void openlog(const char *file_out_path, const char *log_file_name) {
	nik_global_log_file.open(file_out_path, log_file_name);	
}

void openlog(const char *log_file_name_with_path) {
	nik_global_log_file.open(log_file_name_with_path);	
}

void printflog(const char *fmt, ...) {
	va_list args;
    va_start(args, fmt);	
    nik_global_log_file.vprintf(fmt, args);
	va_end(args); // need to call va_end() after va_start() before return
}

void vprintflog(const char *fmt, va_list args) {
    nik_global_log_file.vprintf(fmt, args);
}

void err_exit(const char *fmt, ...) {
	printflog("* Error: ");
	va_list args;
    va_start(args, fmt);
    vprintflog(fmt, args);
	va_end(args); // need to call va_end() after va_start() before return
	printflog(".\n");
	exit(-1);
}

void dbg_exit(const char *fmt, ...) {
	printflog("* Debug exit: ");
	va_list args;
    va_start(args, fmt);
    vprintflog(fmt, args);
	va_end(args); // need to call va_end() after va_start() before return
	printflog(".\n");
	exit(0);
}

#endif
