/*
	Written by Pham The Chung
	27/5/2010
*/
#ifndef SYSCALL64_H
#define SYSCALL64_H
#include <linux/stat.h>
#include <linux/dirent.h>
#include <piece/code_macro.h>
/**/
#define __PSYS(name) PROTOSYS(long,name)
/**/
extern PROTOSYS(long,open)(const char *name,int o_flag,int cmod);
extern PROTOSYS(long,close)(int fd);
extern PROTOSYS(long,read)(unsigned fd,void *buf,long count);
extern PROTOSYS(long,write)(unsigned fd,void *buf,long count);
extern PROTOSYS(long,fstat)(unsigned fd,struct stat *buf);
extern PROTOSYS(long,stat)(const char *name,struct stat *buf);
extern PROTOSYS(long,chdir)(const char *dir);
extern __PSYS(fchdir) (int fd);
extern __PSYS(getcwd) (char *buf,int size);
extern PROTOSYS(long,getdents64)
      (unsigned fd,struct linux_dirent64 *buf,unsigned sz);
extern PROTOSYS(long,mount)
      (const char *dev,const char *dir,char *type,long flag,void *data);
extern PROTOSYS(long,umount2)(const char *dir,int flag);
#endif
