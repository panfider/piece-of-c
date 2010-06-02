/*
	Written Pham The Chung
	create 27/05/2010
*/
#ifndef __USE_PIECE_H
	#define __USE_PIECE_H

#include "piece_code.h"

#ifdef USE_PIECE_STRING_H
	#include <piece/piece##_string.h>
#endif
#ifdef USE_PIECE_STDIO_H
	#include <piece/piece##_stdio.h>
#endif
#ifdef USE_PIECE_STDLIB_H
	#include <piece/piece_stdlib.h>
#endif
#ifdef USE_PIECE_MATH_H
	#include <piece/piece_math.h>
#endif
#ifdef USE_PIECE_GETOPT_H
	#include <piece/piece_getopt.h>
#endif
#ifdef USE_PIECE_TIME_H
	#include <piece/piece_time.h>
#endif
#ifdef USE_PIECE_MALLOC_H
	#include <piece/piece_malloc.h>
#endif
#ifdef USE_PIECE_IOFILE_H
	#include <piece/piece_iofile.h>
#endif

#endif


