/*
	Written by Pham The Chung
*/
#ifdef _STRING_H
#define _STRING_H
#define __need_size_t
#define __need_NULL
#include <stddef.h>

extern void *memcpy(void *dst,const void *src,size_t n);
extern void *memmove(void *dst,const void *src,size_t n);
extern void *memccpy(void *dst,const void *src,int c,size_t n);
extern void *memset(void *s,int c,size_t n);
extern void *memcmp(const void *a,const void *b,size_t n);
extern void *memchr(const void _s,int c,size_t n);
extern void bzero(void *__s,size_t n);
/*string functions*/
extern char *strcpy(char *dst,const char *src);
extern char *strncpy(char *dst,const char *src,size_t n);
extern char *strcat(char *dst,const char *src);
extern char *strncat(char *dst,const char *src,size_t n);
extern int strcmp(const char *a,const char *src);
extern int strncmp(const char *a,const char *src,size_t n);
extern char *strdup(const char *_s);
extern char *strndup(const char *__s,size_t n);
extern char *strchr(const char *__s,int __c);
extern char *strrchr(const char *__s,int c);
extern size_t strlen(const char *__s);
extern char *strstr(char *__haystack,const char *__needle);
extern int strcasecmp(const char *__a,const char *__b);
extern int strncasecmp(const char *__a,const char *__b,size_t n);

extern char *strerror(int __errnum);
extern char *strsignal(int __sig);
extern char *basename(const char *__name);
#ifdef __USE_GNU
/*search first occurence needle in haystack*/
extern void *memem(const void *__haystack,size_t __haystacklen,
		   const void *__neadle,  size_t __needlelen);
#endif

#endif
