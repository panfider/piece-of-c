#ifndef _DIRENT_H
#define _DIRENT_H
#include "bits/dirent.h"
extern DIR *opendir(const char *__name);
extern DIR *fdopendir(int __fd);

extern int closedir(DIR *__dp);
extern struct dirent *readdir(DIR *__dp);
extern void rewinddir(DIR *__dp);

extern int dirfd(DIR *__dp);
extern long int telldir(DIR *__dp);
extern void seekdir(DIR *__dp,long __pos);

#endif
