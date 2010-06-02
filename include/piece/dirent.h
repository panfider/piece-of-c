/*
	written by Pham The Chung
	create 1/3/2010
*/
#ifndef PIECE_DIRENT_H
#define PIECE_DIRENT_H
#include "piece_code.h"
#include "piecetype.h"
#include "itype.h"
/*
	like linux_dirent64
*/
typedef struct dirent_object{
	unsigned long	d_ino;
	long		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[0];
}Dirent;
typedef struct linuxdirent_object{
	Dirent *dents;
	long sizedir;
	char *pos; /*pos pointer*/
	long next;
	long check; /*check whether it reach sizedir*/
}Dir;
//typedef Dir DIR;
/*
	Dir *dp=piece_opendir("/");
	Dirent *entp;
	while((entp=piece_readdir(dp))!=NULL)
		printf("%s \n",entp->d_name);
*/
Link Public PIECE_PROTO(Dir *,opendir)(const char *dirname);
Link Public PIECE_PROTO(Dir *,fdopendir)(int dfd);
Link Public PIECE_PROTO(Dirent *,readdir)(Dir *dp);
Link Public PIECE_PROTO(void ,closedir)(Dir *dp);
Link Public PIECE_PROTO(void,rewinddir)(Dir *dp);
Link Public PIECE_PROTO(char **,direntry)(const char *dirname);
Link Public PIECE_PROTO(long,ndentry)(const char *dirname);

#endif
