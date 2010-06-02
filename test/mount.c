/*
	mount.c 2010 Pham The Chung
*/
#include <stdio.h>

#include <piece/itype.h>
#include <piece/basetype.h>
#include <piece/getopt.h>
#include <>
const char help[]="mount --type=fstype /dev/??? dir \n\
	option:\n\
		--type=fstype	see fstype below(not all)\n\
		--version show version this program\n\
		--usage 	show usage and exit\n\
	list of fs type:\n\
		ext2 ext3 vfat \n\
	claim at: pham.the.chung0@gmail.com\n";
const char version[]="mount version 0.1\nWritten by Pham The Chung\n";
const char *fstype[]={
	"ext2","ext3","vfat","NULL",NULL
};
void ERRMESS(){
	printf("mount: error !cant mount\n");
}
Bool chkexist( const char*file ){
	Bool test;
	if( !access(file,0) ) test=YES;
	else test=NO;
	return test;
}
long Kmount ( 
		const char *dev_name, 
		const char *dir_name,
		const char *type,
		unsigned long flags,
		void *data 
	   ) 
{
	/*
	__asm__("\n\
		mov %4,%%r10;mov %5,%%r8; \
		syscall;\
		"::"a"(__NR_mount),"D"(dev_name),"S"(dir_name),"d"(type),"g"(flags),"g"(data));
	*/
	CALL_SYS(mount,())
}
int do_mount(int argc,char **argv){
	char *pt=NULL,ch,fs=1,fact=1,t=NO;
	int r;
	int count_name=countFileOpt(argc,argv);
	int n=scanFileOpt(argc,argv);
	while( (ch=getopt(argc,argv,NULL))!=NULL ){
		switch(ch){
			case '-':
				if( !cmpString(getpopt(),"usage") ) 
				{
					printf(help);exit(0);
				}
				if( !cmpString(getpopt(),"version") ) 
				{ printf(version);exit(0); }
				if( !cmpString(getpopt(),"type") ) {
					t=YES;
					if(OpthasValue()) {
					 pt=getpval();
					 if( count_name==2 )
					 r=Kmount(argv[get_word_low(n)],
					 	argv[get_word_high(n)],pt,MS_SYNCHRONOUS,NULL);
					 printf("%s->%s type %s\n",
					 argv[get_word_low(n)],argv[get_word_high(n)],pt);
					 if(r==ERROR) ERRMESS();
					 if(r<0) ERRMESS();
					}
					else{
						printf("mount: must specify fs type\n");
					}
				}
				break;
			case ':':{
					if( ifexist(getpopt()) )
						printf("mount:dont exist %s\n",getpopt());
				}
				break;
		}
	}
}
int main( const int argc,const char**argv ){
	if(argc>1){
		do_mount(argc,argv);
	}else printf("mount: missing argument\nmount --usage to see usage");
	printf("\n");
	exit(1);
}

