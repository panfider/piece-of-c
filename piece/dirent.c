/*
	Written Pham The Chung
	create 27/05/2010
	gcc -m64 -std=c99 -c dirent.c -Iinclude
	development status:
		has been test: opendir closedir readdir rewinddir direntry
*/

/*my dirent still depend on system malloc*/
#include <malloc.h>
#include <piece/kconnect.h>
#include <linux/types.h>
#include <linux/dirent.h>
#include "linux/stat.h"
#include "linux/fcntl.h"
#include "piece/piece_string.h"
#include "piece/syscall64.h"
#include "piece/piece_code.h"
#include "piece/code_macro.h"
typedef struct dirent_object{
	unsigned long	d_ino;
	long		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[0];
}Dirent;
typedef struct linuxdirent_object{
	long dfd;
	Dirent *dents;
	long sizedir;
	char *pos; /*pos pointer*/
	long next;
	long check; /*check whether it reach sizedir*/
}Dir;


/*
	getdent abstract functions to system call getdents64
*/

PIECE_IMPLE(static long,open_name)(const char *name){
	long dfd=CALL_SYS(open,(name,O_RDONLY,0));
	return dfd;
}
PIECE_IMPLE(static Dirent *,listDir)(long dfd,long *retsize){
	struct stat fod;
	Dirent *dirp,*entp;
	if(CALL_SYS(fstat,(dfd,&fod))) return (Dirent *)NULL;
	if(dfd<0) return (Dirent *)-1;
	int buf_size=fod.st_size+sizeof(Dirent);
	dirp=(Dirent *)CALL_USUAL(malloc,(buf_size));      /*yes!I'm malloc*/
	long recsize=CALL_SYS(getdents64,
		(dfd,(struct linux_dirent64 *)dirp,buf_size) );
	if(recsize<0) return NULL;/*(Dirent *)recsize;*/
	*retsize=recsize;
	int byte=0;
	entp=dirp;
	char *pt=(char*)dirp;
	return (Dirent *)dirp;
}

PIECE_IMPLE(Dir *,opendir)(const char *dirname){
	int dfd=CALL_SYS(open,(dirname,O_RDONLY,0));
	Dir *dirp;
	long syssize;
	dirp=(Dir*)CALL_USUAL(malloc,(sizeof(Dir)));
	if(dirp==NULL) return NULL;
	dirp->dents=PIECE_CALL(listDir,(dfd,&syssize));
	if(dirp->dents<=0) return NULL;
	dirp->pos=(char*)dirp->dents;
	dirp->sizedir=syssize;
	dirp->next=0;
	dirp->check=0;
	dirp->dfd=dfd;
	return dirp;
}
/*	offer an fdopendir functions for convinience
	FIXME continue writting this functions
*/
PIECE_IMPLE(Dir *,fdopendir)(int fd){
	Dir *dirp=(Dir*)CALL_USUAL(malloc,(sizeof(Dir)));
	long syssize;
	if(dirp==NULL) return dirp;
	dirp->dents=PIECE_CALL(listDir,(fd,&syssize));
	if(dirp->dents<=0) return NULL;
	dirp->pos=(char*)dirp->dents;
	dirp->sizedir=syssize;
	dirp->next=0;
	dirp->check=0;
	CALL_SYS(close,(fd));
	return dirp;
}
/*
	yast ! It run good
*/
PIECE_IMPLE(Dirent *,readdir)(Dir *dp){
	Dirent *entp,*idir;
	idir=dp->dents; /*init a pointer to frame*/
	if(dp->check==dp->sizedir) return NULL;
	dp->pos+=dp->next;
	entp=(Dirent *)dp->pos;
	dp->next=entp->d_reclen;
	dp->check+=dp->next;
	return (Dirent*)entp;
}
PIECE_IMPLE(void ,closedir)(Dir *dp){
	void *freethis=dp->dents;
	CALL_USUAL(free,(freethis));
	CALL_SYS(close,(dp->dfd));
}
PIECE_IMPLE(void,rewinddir)(Dir *dp){
	Dir *dirp=dp;
	dirp->pos=(char*)dirp->dents;
	dirp->next=0;
	dirp->check=0;
}
/*
	from now can use all dirent function to operating with directory
*/
/*
	understand the function
	return a pointer shape char** 
	vector of pointer to a malloc flat memory contain list of strings
*/

PIECE_IMPLE(char **,direntry)(const char *dirname){
	Dir *dirp;
	Dirent *dent;
	dirp=PIECE_CALL(opendir,(dirname));
	int nitem=0,nbyte=0;
	if(dirp){
		while((dent=PIECE_CALL(readdir,(dirp)))){
			nitem++;
			nbyte+=PIECE_CALL(strlen,(dent->d_name));
		}
	}else return NULL;
	char *pt[nitem+1];
	pt[nitem]=NULL;
	int tnbyte=nbyte+nitem;
	void *field=CALL_USUAL(malloc,(tnbyte+1));
	if(!field) return NULL;
	char *buf=(char*)field;
	short len=0;
	PIECE_CALL(rewinddir,(dirp));
	int run=0;
	if(dirp)
	while((dent=PIECE_CALL(readdir,(dirp)))){
		PIECE_CALL(strcpy,(buf,dent->d_name));
		pt[run]=buf;
		len=1+PIECE_CALL(strlen,(dent->d_name));
		buf+=len;
		run++;
	}
	PIECE_CALL(closedir,(dirp));
	void *bufpt=CALL_USUAL(malloc,(sizeof (pt)));
	void *retp=(void *)PIECE_CALL(memcpy,(bufpt,pt,sizeof pt));
	return (char**)retp;
}

PIECE_IMPLE(long,ndentry)(const char *dirname){
	Dir *dirp;
	Dirent *dent;
	dirp=PIECE_CALL(opendir,(dirname));
	int entry=0,byte=0;
	if(dirp){
		while((dent=PIECE_CALL(readdir,(dirp)))) entry++;
	}else return 0;
	PIECE_CALL(closedir,(dirp));
	return entry;
}
