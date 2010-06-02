/*
	written by Pham The Chung
	June 1 2010
*/
#ifdef _PIECE_STRING_H
#define _PIECE_STRING_H
#include <piece/piece_code.h>
#include <piece/itype.h>
Link Public _PP(long,strlen)(const char *s);
Link Public _PP(char *,strcpy)(char *dst,const char *src);
Link Public _PP(char *,strncpy)(char *dst,const *src,size_t n);
Link Public _PP(long,strcmp)(const char *a,const char *b);
Link Public _PP(long,strncmp) (const char *a,const char *b,size_t n);
Link Public _PP(char *,strcat) (char *dst,const char *src);
Link Public _PP(char *,strncat)(char *dst,const char src,size_t n);
Link Public _PP(char *,cpyStringat)( char *this,const char *src,int pos);
Link Public _PP(long,strstr)(const char *lstring,const char *src);
Link Public _PP(void *,memcpy)(void *dst,const void *src,size_t n);
Link Public _PP(int,memcmp)(const void *a,const void *b,size_t n);
Link Public _PP(char *,basename)(const char *path);

#endif
