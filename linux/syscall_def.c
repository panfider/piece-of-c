/*
	Written by Pham The Chung 1/4/2010
	this file define syscall by kconnect macro
	gcc [-m64] -c syscall_def.c -Iinclude
*/
/*
	compile success
	Note: syscall has name like _##name##_ for calling
	CALL_SYS(name,(par,par2)); for _name_(par,par2);
*/
#include <piece/kconnect.h>
#include "linux/types.h"
#include "linux/stat.h"
#include "linux/dirent.h"
#include "linux/msg.h"
#include "linux/kernel.h"
#include "linux/time.h"
#include "linux/uio.h"
#include "linux/shm.h"
#include "linux/socket.h"
#include "linux/resource.h"
#include "linux/utsname.h"
#include "linux/sem.h"
#include "linux/poll.h"
#include "linux/signal.h"
#include <linux/quota.h>
#ifndef __user
#define __user
#endif

/*
	syscall defination
*/
SYSCALL_DEFINE2(chmod, const char __user *, filename, mode_t, mode);
SYSCALL_DEFINE2(link,
const char __user *,oldname, const char __user *, newname);

SYSCALL_DEFINE3(read,
	unsigned int, fd, char __user *, buf, size_t, count);
SYSCALL_DEFINE3(write,
	unsigned int, fd, const char __user *, buf,size_t, count);
SYSCALL_DEFINE3(open, const char __user *, filename, int, flags, int, mode);
SYSCALL_DEFINE1(close, unsigned int, fd);
/*		struct stat is right for stat nr 4	*/
SYSCALL_DEFINE2(stat, char __user *, filename, struct stat __user *, statbuf);
SYSCALL_DEFINE2(lstat, char __user *, filename, struct stat __user *, statbuf);
SYSCALL_DEFINE2(fstat, unsigned int, fd, struct stat __user *, statbuf);
SYSCALL_DEFINE3(poll,
	struct pollfd __user *, ufds, unsigned int, nfds,long, timeout_msecs);

/*check type later*/
SYSCALL_DEFINE3(lseek,
		long,fd,long,offset,unsigned, whence);
SYSCALL_DEFINE6(mmap, unsigned long, addr, unsigned long, len,
		unsigned long, prot, unsigned long, flags,
		unsigned long, fd, unsigned long, off);
SYSCALL_DEFINE3(mprotect, unsigned long, start, size_t, len,
		unsigned long, prot);
SYSCALL_DEFINE2(munmap, unsigned long, addr, size_t, len);
SYSCALL_DEFINE1(brk, unsigned long, brk);
SYSCALL_DEFINE4(rt_sigaction, int, sig,
		const struct sigaction __user *, act,
		struct sigaction __user *, oact,
		size_t, sigsetsize);
SYSCALL_DEFINE4(rt_sigprocmask, int, how, sigset_t __user *, set,
		sigset_t __user *, oset, size_t, sigsetsize);
/* i dont know sigreturn is what ???*/

SYSCALL_DEFINE3(ioctl,
		unsigned int, fd, unsigned int, cmd, unsigned long, arg);
SYSCALL_DEFINE4(pread64,
	unsigned int,fd,char __user *,buf,size_t,count, loff_t,pos);
SYSCALL_DEFINE4(pwrite64,
	unsigned int,fd, const char __user *,buf,size_t,count, loff_t,pos);
SYSCALL_DEFINE3(readv, unsigned long, fd, const struct iovec __user *, vec,
		unsigned long, vlen);
SYSCALL_DEFINE3(writev, unsigned long, fd, const struct iovec __user *, vec,
		unsigned long, vlen);
SYSCALL_DEFINE5(preadv,
	unsigned long, fd,const struct iovec __user *, vec,
	unsigned long, vlen,unsigned long, pos_l,
	unsigned long, pos_h);
SYSCALL_DEFINE5(pwritev,
	unsigned long, fd, const struct iovec __user *, vec,
	unsigned long, vlen, unsigned long, pos_l,
	unsigned long, pos_h);
SYSCALL_DEFINE2(access, const char __user *, filename, int, bitmode);
SYSCALL_DEFINE1(pipe, int __user *, fildes);
SYSCALL_DEFINE5(select,
		int, n, fd_set __user *, inp, fd_set __user *, outp,
		fd_set __user *, exp, struct timeval __user *, tvp);
SYSCALL_DEFINE0(sched_yield);
SYSCALL_DEFINE5(mremap, unsigned long, addr, unsigned long, old_len,
		unsigned long, new_len, unsigned long, flags,
		unsigned long, new_addr);
SYSCALL_DEFINE3(msync, unsigned long, start, size_t, len, int, flags);
SYSCALL_DEFINE3(mincore,
	unsigned long, start, size_t, len,unsigned char __user *, vec);
SYSCALL_DEFINE3(madvise, unsigned long, start, size_t, len_in, int, behavior);

SYSCALL_DEFINE3(shmget, key_t, key, size_t, size, int, shmflg);
SYSCALL_DEFINE3(shmat, int, shmid, char __user *, shmaddr, int, shmflg);
SYSCALL_DEFINE3(shmctl, int, shmid, int, cmd, struct shmid_ds __user *, buf);

SYSCALL_DEFINE1(dup, unsigned int, fildes);
SYSCALL_DEFINE2(dup2, unsigned int, oldfd, unsigned int, newfd);
SYSCALL_DEFINE0(pause);
SYSCALL_DEFINE2(nanosleep, struct timespec __user *, rqtp,
		struct timespec __user *, rmtp);
SYSCALL_DEFINE2(getitimer, int, which, struct itimerval __user *, value);
SYSCALL_DEFINE1(alarm, unsigned int, seconds);
SYSCALL_DEFINE3(setitimer, int, which, struct itimerval __user *, value,
		struct itimerval __user *, ovalue);
SYSCALL_DEFINE0(getpid);
SYSCALL_DEFINE4(sendfile,
	int, out_fd, int, in_fd, off_t __user *, offset, size_t, count);
SYSCALL_DEFINE3(socket, int, family, int, type, int, protocol);
SYSCALL_DEFINE3(connect, int, fd, struct sockaddr __user *, uservaddr,
		int, addrlen);
SYSCALL_DEFINE3(accept, int, fd, struct sockaddr __user *, upeer_sockaddr,
		int __user *, upeer_addrlen); /*wrap of accept4*/
SYSCALL_DEFINE6(sendto, int, fd, void __user *, buff, size_t, len,
		unsigned, flags, struct sockaddr __user *, addr,int, addr_len);
SYSCALL_DEFINE6(recvfrom, int, fd, void __user *, ubuf, size_t, size,
		unsigned, flags, struct sockaddr __user *, addr,
		int __user *, addr_len);
SYSCALL_DEFINE3(sendmsg, int, fd, struct msghdr __user *, msg, unsigned, flags);
SYSCALL_DEFINE3(recvmsg, int, fd, struct msghdr __user *, msg,
		unsigned int, flags);
SYSCALL_DEFINE2(shutdown, int, fd, int, how);
SYSCALL_DEFINE3(bind, int, fd, struct sockaddr __user *, umyaddr, int, addrlen);
SYSCALL_DEFINE2(listen, int, fd, int, backlog);
SYSCALL_DEFINE3(getsockname, int, fd, struct sockaddr __user *, usockaddr,
		int __user *, usockaddr_len);
SYSCALL_DEFINE3(getpeername, int, fd, struct sockaddr __user *, usockaddr,
		int __user *, usockaddr_len);
SYSCALL_DEFINE5(setsockopt, int, fd, int, level, int, optname,
		char __user *, optval, int, optlen);
SYSCALL_DEFINE5(getsockopt, int, fd, int, level, int, optname,
		char __user *, optval, int __user *, optlen);
/*clone isnt know */
SYSCALL_DEFINE0(fork);
SYSCALL_DEFINE0(vfork);
SYSCALL_DEFINE3(execve,const char*,_name_,char*const*,arg,char*const*,envp );
SYSCALL_DEFINE1(exit, int, error_code);
SYSCALL_DEFINE4(wait4, pid_t, upid, int __user *, stat_addr,
		int, options, struct rusage __user *, ru);
SYSCALL_DEFINE2(kill, pid_t, pid, int, sig);
SYSCALL_DEFINE1(uname, struct new_utsname __user *, name);

SYSCALL_DEFINE3(semget, key_t, key, int, nsems, int, semflg);
SYSCALL_DEFINE3(semop, int, semid, struct sembuf __user *, tsops,
		unsigned, nsops);
SYSCALL_DEFINE4(semctl,int,semid,int,semnum,int,cmd,union semun,arg);
SYSCALL_DEFINE1(shmdt, char __user *, shmaddr);
SYSCALL_DEFINE2(msgget, key_t, key, int, msgflg);
SYSCALL_DEFINE3(msgctl, int, msqid, int, cmd, struct msqid_ds __user *, buf);
SYSCALL_DEFINE4(msgsnd, int, msqid, struct msgbuf __user *, msgp, size_t, msgsz,
		int, msgflg);
SYSCALL_DEFINE5(msgrcv, int, msqid, struct msgbuf __user *, msgp, size_t, msgsz,
		long, msgtyp, int, msgflg);

SYSCALL_DEFINE3(fcntl, unsigned int, fd, unsigned int, cmd, unsigned long, arg);
SYSCALL_DEFINE2(flock, unsigned int, fd, unsigned int, cmd);
SYSCALL_DEFINE1(fsync, unsigned int, fd);
SYSCALL_DEFINE1(fdatasync, unsigned int, fd);
SYSCALL_DEFINE2(truncate, const char __user *, path, long, length);
SYSCALL_DEFINE2(ftruncate, unsigned int, fd, unsigned long, length);
struct linux_dirent;
SYSCALL_DEFINE3(getdents, unsigned int, fd,
		struct linux_dirent __user *, dirent, unsigned int, count);
SYSCALL_DEFINE3(getdents64, unsigned int, fd,
		struct linux_dirent64 __user *, dirent, unsigned int, count);
SYSCALL_DEFINE2(getcwd, char __user *, buf, unsigned long, size);

SYSCALL_DEFINE1(chdir, const char __user *, filename);
SYSCALL_DEFINE1(fchdir, unsigned int, fd);
SYSCALL_DEFINE2(rename,const char __user *,oldname,const char __user *,newname);
SYSCALL_DEFINE3(chown, const char __user *,filename,uid_t, user,gid_t,group);
SYSCALL_DEFINE3(lchown, const char __user *,filename,uid_t, user, gid_t, group);
SYSCALL_DEFINE3(fchown, unsigned int, fd, uid_t, user, gid_t, group);
SYSCALL_DEFINE1(umask, int, mask);

SYSCALL_DEFINE2(gettimeofday, struct timeval __user *, tv,
		struct timezone __user *, tz);
SYSCALL_DEFINE2(settimeofday, struct timeval __user *, tv,
		struct timezone __user *, tz);
SYSCALL_DEFINE2(getrlimit, unsigned int,resource,struct rlimit __user *,rlim);
SYSCALL_DEFINE2(getrusage, int, who, struct rusage __user *, ru);
SYSCALL_DEFINE1(sysinfo, struct sysinfo __user *, info);
SYSCALL_DEFINE1(times, struct tm __user *, tbuf);
/* suspicous about struct tms or tm*/
SYSCALL_DEFINE4(ptrace, long, request, long, pid, long, addr, long, data);
SYSCALL_DEFINE0(getuid);
SYSCALL_DEFINE3(syslog, int, type, char __user *, buf, int, len);

SYSCALL_DEFINE0(getgid);
SYSCALL_DEFINE1(setuid, uid_t, uid);
SYSCALL_DEFINE1(setgid, gid_t, gid);
SYSCALL_DEFINE0(geteuid);
SYSCALL_DEFINE0(getegid);
SYSCALL_DEFINE2(setpgid, pid_t, pid, pid_t, pgid);
SYSCALL_DEFINE0(getppid);
SYSCALL_DEFINE0(getpgrp);
SYSCALL_DEFINE0(setsid);
SYSCALL_DEFINE2(setreuid, uid_t, ruid, uid_t, euid);
SYSCALL_DEFINE2(setregid, gid_t, rgid, gid_t, egid);
SYSCALL_DEFINE2(getgroups, int, gidsetsize, gid_t __user *, grouplist);
SYSCALL_DEFINE2(setgroups, int, gidsetsize, gid_t __user *, grouplist);
SYSCALL_DEFINE3(setresuid, uid_t, ruid, uid_t, euid, uid_t, suid);
SYSCALL_DEFINE3
(getresuid, uid_t __user *, ruid, uid_t __user *, euid, uid_t __user *, suid);
SYSCALL_DEFINE3
(setresgid, gid_t, rgid, gid_t, egid, gid_t, sgid);
SYSCALL_DEFINE3
(getresgid, gid_t __user *, rgid, gid_t __user *, egid, gid_t __user *, sgid);
SYSCALL_DEFINE1(getpgid, pid_t, pid);
SYSCALL_DEFINE1(setfsuid, uid_t, uid);
SYSCALL_DEFINE1(setfsgid, gid_t, gid);
SYSCALL_DEFINE1(getsid, pid_t, pid);
#define cap_user_header_t long
#define cap_user_data_t long
SYSCALL_DEFINE2(capget, cap_user_header_t, header, cap_user_data_t, dataptr);
SYSCALL_DEFINE2(capset, cap_user_header_t, header, const cap_user_data_t, data);

SYSCALL_DEFINE2(rt_sigpending, sigset_t __user *, set, size_t, sigsetsize);
SYSCALL_DEFINE4(rt_sigtimedwait, const sigset_t __user *, uthese,
		siginfo_t __user *, uinfo, const struct timespec __user *, uts,
		size_t, sigsetsize);
SYSCALL_DEFINE3(rt_sigqueueinfo, pid_t, pid, int, sig,
		siginfo_t __user *, uinfo);
SYSCALL_DEFINE2(rt_sigsuspend, sigset_t __user *, unewset, size_t, sigsetsize);
/*__NR_sigaltstack                       131*/
SYSCALL_DEFINE3(mknod, const char __user *,filename,int,mode,unsigned,dev);

SYSCALL_DEFINE3(setpriority, int, which, int, who, int, niceval);
SYSCALL_DEFINE2(getpriority, int, which, int, who);

/*
SYSCALL_DEFINE2
(utime, char __user *, filename, struct utimbuf __user *, times);*/
/* free order list of syscall */

SYSCALL_DEFINE2(pivot_root, const char __user *, new_root,
		const char __user *, put_old);
SYSCALL_DEFINE0(sync);
SYSCALL_DEFINE1(chroot, const char __user *, filename);
SYSCALL_DEFINE4(getxattr, const char __user *, pathname,
		const char __user *, name, void __user *,value,size_t,size);
SYSCALL_DEFINE4(lgetxattr, const char __user *, pathname,
		const char __user *, name, void __user *, value, size_t, size);
SYSCALL_DEFINE4(fgetxattr, int, fd, const char __user *, name,
		void __user *, value, size_t, size);
SYSCALL_DEFINE3(listxattr, const char __user *, pathname, char __user *, list,
		size_t, size);
SYSCALL_DEFINE3(llistxattr, const char __user *, pathname, char __user *, list,
		size_t, size);
SYSCALL_DEFINE3(flistxattr, int, fd, char __user *, list, size_t, size);
SYSCALL_DEFINE2(removexattr, const char __user *, pathname,
		const char __user *, name);
SYSCALL_DEFINE2(lremovexattr, const char __user *, pathname,
		const char __user *, name);
SYSCALL_DEFINE2(fremovexattr, int, fd, const char __user *, name);
SYSCALL_DEFINE2(tkill, pid_t, pid, int, sig);
SYSCALL_DEFINE1(time, time_t __user *, tloc);
SYSCALL_DEFINE6(futex, u32 __user *, uaddr, int, op, u32, val,
		struct timespec __user *, utime, u32 __user *,uaddr2,u32, val3);
SYSCALL_DEFINE3(sched_setaffinity, pid_t, pid, unsigned int, len,
		unsigned long __user *, user_mask_ptr);
SYSCALL_DEFINE3(sched_getaffinity, pid_t, pid, unsigned int, len,
		unsigned long __user *, user_mask_ptr);

SYSCALL_DEFINE3(timer_create, const clockid_t, which_clock,
		struct sigevent __user *, timer_event_spec,
		timer_t __user *, created_timer_id);
SYSCALL_DEFINE2(timer_gettime, timer_t, timer_id,
		struct itimerspec __user *, setting);
SYSCALL_DEFINE1(timer_getoverrun, timer_t, timer_id);
SYSCALL_DEFINE4(timer_settime, timer_t, timer_id, int, flags,
		const struct itimerspec __user *, new_setting,
		struct itimerspec __user *, old_setting);
SYSCALL_DEFINE1(timer_delete, timer_t, timer_id);

SYSCALL_DEFINE4(openat, int, dfd, const char __user *, filename, int, flags,
		int, mode);
SYSCALL_DEFINE3(mkdirat, int, dfd, const char __user *, pathname, int, mode);
SYSCALL_DEFINE4(mknodat, int, dfd, const char __user *, filename, int, mode,
		unsigned, dev);
SYSCALL_DEFINE5(fchownat, int, dfd, const char __user *, filename, uid_t, user,
		gid_t, group, int, flag);
SYSCALL_DEFINE3(futimesat, int, dfd, char __user *, filename,
		struct timeval __user *, utimes);
SYSCALL_DEFINE4(newfstatat, int, dfd, char __user *, filename,
		struct stat __user *, statbuf, int, flag);
SYSCALL_DEFINE4(renameat,
		int, olddfd, const char __user *, oldname,
		int, newdfd, const char __user *, newname);
SYSCALL_DEFINE3(unlinkat, int, dfd, const char __user *, pathname, int, flag);
SYSCALL_DEFINE5(linkat,
		int, olddfd, const char __user *, oldname,
		int, newdfd, const char __user *, newname, int, flags);
SYSCALL_DEFINE3(symlinkat,
		const char __user *, oldname,
		int, newdfd, const char __user *, newname);
SYSCALL_DEFINE4(readlinkat, int, dfd, const char __user *, pathname,
		char __user *, buf, int, bufsiz);
SYSCALL_DEFINE3(fchmodat, int, dfd, const char __user *, filename, mode_t, mode);
SYSCALL_DEFINE3(faccessat, int, dfd, const char __user *, filename, int, mode);
SYSCALL_DEFINE6(pselect6,
		int, n, fd_set __user *, inp, fd_set __user *, outp,
		fd_set __user *, exp, struct timespec __user *, tsp,
		void __user *, sig);
SYSCALL_DEFINE5(ppoll, struct pollfd __user *, ufds, unsigned int, nfds,
		struct timespec __user *, tsp, const sigset_t __user *, sigmask,
		size_t, sigsetsize);
SYSCALL_DEFINE1(unshare, unsigned long, unshare_flags);
SYSCALL_DEFINE3(dup3, unsigned int, oldfd, unsigned int, newfd, int, flags);
SYSCALL_DEFINE2(pipe2, int __user *, fildes, int, flags);
SYSCALL_DEFINE4(accept4, int, fd, struct sockaddr __user *, upeer_sockaddr,
		int __user *, upeer_addrlen, int, flags);
SYSCALL_DEFINE5(mount, char __user *, dev_name, char __user *, dir_name,
		char __user *, type, unsigned long, flags, void __user *, data);
SYSCALL_DEFINE2(umount2, char __user *, name, int, flags);
SYSCALL_DEFINE1(epoll_create1, int, flags);
SYSCALL_DEFINE1(epoll_create, int, size);
SYSCALL_DEFINE2(creat, char __user *,name,long ,bitmode);
SYSCALL_DEFINE2(mkdir,char __user *,dir,long,bitmode);
SYSCALL_DEFINE1(rmdir,char __user *,dir);
SYSCALL_DEFINE1(unlink,char __user *,name);
SYSCALL_DEFINE4(quotactl,unsigned int,cmd, const char __user *,special,
				qid_t, id, void __user *,addr);
