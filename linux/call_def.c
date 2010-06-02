/*
	Written by Pham The Chung
	May 31 2010
*/
#include <piece/kint80.h>
#include <linux/dirent.h>
#include <linux/stat.h>

typedef unsigned gid_t;
typedef long time_t;
typedef unsigned int mode_t;
typedef unsigned uid_t;
//struct linux_dirent64;
/*
long __getdents64_( int fd, struct linux_dirent64 *__entp,unsigned _bytes){

}*/
SYS_DEF3(getdents64,int,fd,struct linux_dirent64 *,_entp,int, bytes);
SYS_DEF1(exit,int,code);
SYS_DEF0(fork);
SYS_DEF3(read,int,ffd,void *,buf,unsigned,size);
SYS_DEF3(write,int,ffd,void *,buf,unsigned,size);
SYS_DEF3(open,const char *,name,int ,O_flag,int ,creat_mode);
SYS_DEF1(close,int,fd);
/*SYS_DEF0(waitpid);*//*temporaty reg here*/
SYS_DEF2(creat,const char *,name,int ,crat_mode);
SYS_DEF2(link,const char *,f,const char *,t);
SYS_DEF1(unlink,const char *,name);
SYS_DEF3(execve,const char *,name, const char **,argv,const char **,env);
SYS_DEF1(chdir,const char *,name);
SYS_DEF1(time,time_t *,t);
SYS_DEF3(mknod,const char*,name, int,fmode, unsigned,def);
SYS_DEF2(chmod,const char *,name,mode_t,mode);
SYS_DEF3(lchown,const char *,name, uid_t, user, gid_t, group);
//SYS_DEF0(break);
//SYS_DEF0(oldstat);
/*
SYS_DEF3(lseek,int,fd,unsigned,off,int,whence);
SYS_DEF0(getpid);
SYS_DEF0(mount,char *,dev, char *,dir, char *,type, int,flag, void *,data);
SYS_DEF0(umount,char *,name,int,flag);
SYS_DEF0(setuid);
SYS_DEF0(getuid)
SYS_DEF0(stime);
SYS_DEF0(ptrace);
SYS_DEF1(alarm,int,seconds);
SYS_DEF0(oldfstat);
SYS_DEF0(pause);
SYS_DEF0(utime);
SYS_DEF0(stty);
SYS_DEF0(gtty);
SYS_DEF0(access);
SYS_DEF0(nice);
SYS_DEF0(ftime);
SYS_DEF0(sync);
SYS_DEF0(kill);
SYS_DEF0(rename);
SYS_DEF0(mkdir);
SYS_DEF0(rmdir);
SYS_DEF0(dup);
SYS_DEF0(pipe);
SYS_DEF0(times);
SYS_DEF0(brk);
SYS_DEF0(setgid);
SYS_DEF0(getgid);
SYS_DEF0(signal);
SYS_DEF0(geteuid);
SYS_DEF0(getegid);
SYS_DEF0(acct);
SYS_DEF0(umount2);
SYS_DEF0(lock);
*/
/*above incomplete*/
SYS_DEF3(ioctl,int,fd, int,cmd,int,arg);
SYS_DEF3(fcntl,int,fd, int,cmd,int,arg);

struct linux_dirent;

SYS_DEF1(fchdir,unsigned,dfd);
SYS_DEF2(stat,const char *,name,struct stat *,buf);
SYS_DEF2(lstat,const char *,name,struct stat *,buf);
SYS_DEF2(fstat,const char *,name,struct stat *,buf);

//CALL_DEF3(getdents, int,fd, struct linux_dirent *,__dent,unsigned,sizes);


