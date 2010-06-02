/*
	Written by Pham The Chung
	create May 30 2010
*/
/*
	here is list of function I will implement
*/
#ifndef _STDLIB_H
	#define _STDLIB_H
#define __need_size_t
#define __need_NULL
#include "stddef.h"
#define EXITFAILURE 1
#define EXITSUCCESS 0
extern double atof(const char *nptr);
extern int atoi(const char *nptr);
extern long atol(const char *nptr);
extern long random(void);
extern int rand(void);
extern void *malloc(size_t n);
extern void free(void *ptr);
extern void exit(int __status);
extern int system(const char *command);
/*
	search key in base for __nmemb have __size
*/
typedef int (*__compar_fn_t)(const *void,const void *);
extern void *bsearch(const void *key,const void *base,
		size_t __nmemb,size_t __size,__compar_fn_t __compar);
extern void qsort (void *__base, size_t __nmemb, size_t __size,
                   __compar_fn_t __compar) ;

#endif
