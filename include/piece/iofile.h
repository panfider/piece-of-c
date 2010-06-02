/*
	Written by Pham The Chung
	create May 30 2010
*/
/*
	USAGE using PIECE_CALL() to call below
	PIECE_CALL(copyfile)( file1,file2 );
*/
#ifndef PIECE_IOFILE_H
#define PIECE_IOFILE_H
#include "piece_code.h"
#include "itype.h"
Link Public PIECE_PROTO(long,sizeofFile)(const char *filename);
Link Public PIECE_PROTO(long,getMode)(const char *filename);
/*
	copyfile
*/
Link Public PIECE_PROTO(int, copyfile) (const char *from,const char *to);
Link Public PIECE_PROTO(long,copydir) (const char *from,const char *to);
Link Public PIECE_PROTO(long,removdir)(const char *dirname);
Link Public PIECE_PROTO(long,movdir)(const char *src,const char *dst);

#endif
