/*
	written by Pham The Chung

*/
#ifndef _DIRENT_H
#error "Nerver user <piece/bits/dirent.h> directly,<piece/dirent.h> instead."
#endif
/*
	I just use dirent 64 formal from linux_dirent64
*/
struct dirent{
	unsigned long   d_ino;
        long            d_off;
        unsigned short  d_reclen;
        unsigned char   d_type;
        char            d_name[0];
};
struct DIR_object{
	struct dirent *entp;
	long sizedir;
	char *pos;
	long next;
	long check;
};
typedef struct DIR_object DIR;

