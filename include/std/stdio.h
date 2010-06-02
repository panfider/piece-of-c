/*
	Written by Pham The Chung
	create May 31 2010
*/
/*
	this file have path <piece/std/stdio.h>
*/
//get type
#ifndef _STDIO_H
#define _STDIO_H

#define __need_NULL
#define __need_size_t
#include "stddef.h"

typedef void fpos_t;

/*File operation function */
extern FILE *fopen(const char *name,const char *mode);
extern FILE *fdopen(int fd,const char *mode);
extern FILE *freopen(const char *name,const char *mode,FILE *stream);
extern int fclose(FILE *stream);
extern int fseek(FILE *stream,long off,int whence);
extern long int ftell(FILE *stream);
extern int rewind(FILE *stream);
extern int fflush(FILE *stream);
extern int fgetc(FILE *stream);
extern void setbuf(FILE *stream,char *buf);
extern int fprintf(FILE *stream,char *fmt,...);
extern int fscanf(FILE *stream,char *fmt,...);

extern fgets(char *buf,int n,FILE *stream);
extern fputs(char *buf,FILE *stream);
extern fread(void *pt,size_t size,FILE *stream);
extern fwrite(void *pt,size_t size,FILE *stream);
// dont know type fpos_t
extern int fgetpos(FILE __stream,fpos_t *__pos);
extern int fsetpos(FILE __stream,const fpos_t *__pos);
extern void flockfile(FILE *__stream);
extern void funlockfile(FILE *__stream);

extern int printf(const char *fmt,...);
extern int scanf(const char *fmt,...);
extern int sprintf(char *__s,const char *fmt,...);
extern int sscanf(char *__s,const char *fmt,...);
extern int dprintf(int fd,cosnt char *fmt,...);

extern void perror( const char *s);
extern int getchar(void);
extern int putchar(int c);
extern char *gets(char *s);
extern int puts(char *s);
extern int fileno(FILE *stream);
extern char *ctermid(char *s);
#endif
