#include <stdio.h>
//#include <dirent.h>
//#include <piece/piece_math.h>
//#include <piece/itype.h>
//#include <piece/syscall64.h>
#include <linux/dirent.h>
#include <piece/piece_code.h>
//#include <std/time.h>
#define __NR_getdents64 220
long getdents64(int dfd,struct linux_dirent64 *ent,int sizes){
	__asm__("int $0x80"::"a"(__NR_getdents64),"b"(dfd),"c"(ent),"d"(sizes));
}

int main(){
	char *dir="/";
	int dfd=open(dir,0,0);
	struct linux_dirent64 *ep=malloc(1024);
	long s=getdents64(dfd,ep,1024);
	printf(" %s \n",ep->d_name);
	return 0;
}
/*Dir *dp=_PC(opendir,("/"));
	Dirent *ent;
	while((ent=_PC(readdir,(dp))))
		printf(": %s\n",ent->d_name);
*/
/*
PIECE_IMPLE(int *,abc)(int a){
	return (int *)a;
}
int l(char *name){
	DIR *dp;
	struct dirent *entp;
	dp=opendir(name);
	while((entp=readdir(dp)))
	printf("%s\n",entp->d_name);
	return 0;
}*/
