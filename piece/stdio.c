
/*
	Written by Pham The Chung
	June 1 2010
*/
/*from libc, need help for replace it*/
#include <malloc.h>

#include <linux/stat.h>
#include <piece/piece_code.h>
#include <piece/code_macro.h>
typedef struct File_Object{
        char *name;
        int fd;
        int size;
        int _mode;
        long ino;
        long off;
        char addr[0];
}File;
/*
	what level of function
*/
PIECE_IMPLE(File *,_fopen)(char *name,int oflag,int __mode){
        #define PART 4096
        struct stat fod;
        File *fpt;
        int rd=0;
        if(CALL_SYS(stat,(name,&fod)))
                return NULL;
        int filesize=fod.st_size;
        int fd=CALL_SYS(open,(name,oflag,__mode));
        if(fd<0) return NULL;
        if(filesize<=PART){
        /*      I call malloc of glibc need to replace */
             fpt=(File *)malloc(sizeof(File)+filesize+2);
                rd=CALL_SYS(read,(fd,fpt->addr,filesize));
                fpt->off=filesize;
        }
        else { /*glibc call*/
                fpt=(File *)malloc(sizeof(File)+PART+2);
                rd=CALL_SYS(read,(fd,fpt->addr,PART));
                fpt->off=PART;
        }
        if(rd==filesize){
          fpt->name=name;
          fpt->fd=fd;
          fpt->size=filesize;
          fpt->_mode=fod.st_mode;
          fpt->ino=fod.st_ino;
          return fpt;
        }
        return NULL;
}

PIECE_IMPLE(int ,fclose)(File *f){
        CALL_SYS(close,(f->fd));
        free(f); //glibc function here need to replace
        return 0;
}
PIECE_IMPLE(int,fseek)(File *f,long pos){
        f->off=pos;
        return CALL_SYS(lseek,(f->fd,pos,SEEK_SET));
}
