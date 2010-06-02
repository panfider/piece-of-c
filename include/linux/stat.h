#ifndef _ASM_X86_64_STAT_H
#define _ASM_X86_64_STAT_H

#include <asm/bitsperlong.h>
/*use for stat nr 4*/
struct stat {
	unsigned long	st_dev;
	unsigned long	st_ino;
	unsigned long	st_nlink;

	unsigned int	st_mode;
	unsigned int	st_uid;
	unsigned int	st_gid;
	unsigned int	__pad0;
	unsigned long	st_rdev;
	long		st_size;
	long		st_blksize;
	long		st_blocks;	/* Number 512-byte blocks allocated. */

	unsigned long	st_atime;
	unsigned long 	st_atime_nsec; 
	unsigned long	st_mtime;
	unsigned long	st_mtime_nsec;
	unsigned long	st_ctime;
	unsigned long   st_ctime_nsec;
  	long		__unused[3];
};
/*
	statfs for long=64bits
*/
#ifndef __statfs_word
#define __statfs_word long
#endif
/*
struct statfs {
	__statfs_word f_type;
	__statfs_word f_bsize;
	__statfs_word f_blocks;
	__statfs_word f_bfree;
	__statfs_word f_bavail;
	__statfs_word f_files;
	__statfs_word f_ffree;
	__kernel_fsid_t f_fsid;
	__statfs_word f_namelen;
	__statfs_word f_frsize;
	__statfs_word f_spare[5];
};
*/
#if __BITS_PER_LONG != 64
/* This matches struct stat64 in glibc2.1. Only used for 32 bit. */
struct stat64 {
	unsigned long long st_dev;	/* Device.  */
	unsigned long long st_ino;	/* File serial number.  */
	unsigned int	st_mode;	/* File mode.  */
	unsigned int	st_nlink;	/* Link count.  */
	unsigned int	st_uid;		/* User ID of the file's owner.  */
	unsigned int	st_gid;		/* Group ID of the file's group. */
	unsigned long long st_rdev;	/* Device number, if device.  */
	unsigned long long __pad1;
	long long	st_size;	/* Size of file, in bytes.  */
	int		st_blksize;	/* Optimal block size for I/O.  */
	int		__pad2;
	long long	st_blocks;	/* Number 512-byte blocks allocated. */
	int		st_atime;	/* Time of last access.  */
	unsigned int	st_atime_nsec;
	int		st_mtime;	/* Time of last modification.  */
	unsigned int	st_mtime_nsec;
	int		st_ctime;	/* Time of last status change.  */
	unsigned int	st_ctime_nsec;
	unsigned int	__unused4;
	unsigned int	__unused5;
};
#endif

#endif
