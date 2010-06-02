#ifndef _BITS_TYPES_H
#define _BIT_TYPES_H
#include "wordsize.h"
#if __WORD_SIZE == 64
	typedef unsigned long __uint64_t;
	typedef long __int64_t;

#else
	#define __INT64_T 10000
#endif

#endif
