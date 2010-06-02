#ifndef _LINUX_DIRENT_H
#define _LINUX_DIRENT_H
struct linux_dirent64 {
	unsigned long	d_ino;
	long		d_off;
	unsigned short	d_reclen;
	unsigned char	d_type;
	char		d_name[0];
};

#endif
