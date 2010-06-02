/*
	mkdir.c 2010 Pham The Chung
*/
/*
	SYSCALL	mkdir access
*/
#include <stdio.h>
#include <unistd.h>
#include "itype.h"
#include "opt.h"
#include "string.h"
const char usage[]="Usage:\n\
	mkdir [OPT] directory\n\
	option:\n\
		--mode=N	specify mode of directory( decimal)\n\
		-p		not error when exist\n";
const char version[]="mkdir version 0.1\n\
Written by Pham The Chung\n";
int main( const int argc,const char**argv ){
	if(argc>1){
		char ch,*pt;
		char p=NO;
		int bitmode=0750;
		while( (ch=getOpt(argc,argv,NULL)) ){
			switch(ch){
				case 'p':p=YES;break;
				case '-':
					if( !cmpString(getpopt(),"mode") )
						if( OpthasValue() ) {
							bitmode=a2i(getpval());
							//printf("mkdir: %d\n",bitmode);
						}else printf("mkdir: use 0750\n");
					break;
				case ':':
					if( ifexist(getpopt()) )
						mkdir(getpopt(),bitmode);
					else {
						if(p==YES) exit(0);
						else {
								printf("mkdir: error! Exist %s \n",getpopt());
								exit(1);
							}
					}
					break;
				case '?': printf("mkdir: dont know this option\n");break;
			}
		}
	}else printf("mkdir: not have argument\n");
	exit(1);
}

