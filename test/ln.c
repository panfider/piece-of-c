/*
	ln.c 2010 Pham The Chung
	LASTDATE Mon Feb 01 2010 10:11:09 AM ICT
*/
/* INCLUDE sector */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
	#include <basetype.h>
	#include <itype.h>
#include <cstring.h>
#include <opt.h>
#include <ednumber.h>
#include <iofile.h>
//#include <syscall.h>
/* end INCLUDE sector */
char buf[256];
/* INTERFACE to kernel */
long k_symlink(const char*from,const char*to){
	return symlink(from,to);
}
long k_link( char*from,char*to ){
	return link(from,to);
}
/* end of INTERFACE*/
Private char help[]="Usage: ln [OPTION]... [-T] TARGET LINK_NAME   (1st form)\n\
  or:  ln [OPTION]... TARGET                  (2nd form)\n\
  or:  ln [OPTION]... TARGET... DIRECTORY     (3rd form)\n\
  or:  ln [OPTION]... -t DIRECTORY TARGET...  (4th form)\n\
  understand: ln [OPT] EXIST LINK_NAME \n\
In the 1st form, create a link to TARGET with the name LINK_NAME.\n\
In the 2nd form, create a link to TARGET in the current directory.\n\
In the 3rd and 4th forms, create links to each TARGET in DIRECTORY.\n\
Create hard links by default, symbolic links with --symbolic.\n\
When creating hard links, each TARGET must exist.\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
      --backup[=CONTROL]      make a backup of each existing destination file\n\
  -b                          like --backup but does not accept an argument\n\
  -d, -F, --directory         allow the superuser to attempt to hard link\n\
                                directories (note: will probably fail due to\n\
                                system restrictions, even for the superuser)\n\
  -f, --force                 remove existing destination files\n\
  -n, --no-dereference        treat destination that is a symlink to a\n\
                                directory as if it were a normal file\n\
  -i, --interactive           prompt whether to remove destinations\n\
  -s, --symbolic              make symbolic links instead of hard links\n\
  -S, --suffix=SUFFIX         override the usual backup suffix\n\
  -t, --target-directory=DIRECTORY  specify the DIRECTORY in which to create\n\
                                the links\n\
  -T, --no-target-directory   treat LINK_NAME as a normal file\n\
  -v, --verbose               print name of each linked file\n\
      --help     display this help and exit\n\
      --version  output version information and exit\n\
\n\
The backup suffix is `~', unless set with --suffix .\n\
The version control method may be selected via the --backup option or through\n";
Private char version[]="ln version 0.1\nWritten by Pham The Chung.\n\
					Contact pham.the.chung0@gmail.com\n";
Private char nofile[]="ln: Missing file argument.\nTry ln --help .\n";
Private char option[]="bdFfnisStTv";
typedef long(*func)(char*,char*);
#define VERBOSE(x) (x==YES?printf("%s <- %s\n",argv[get_word_low(posfile)],argv[get_word_high(posfile)]):"")
/* IMPLEMENTATION sector */
Private Bool makeslink( const char*from,const char*to ){
		long ret=k_symlink( from,to );
		if( !ret )
			return YES;
		else return NO;
}
Private Bool makehlink( const char*from,const char*to ){
	if( !k_link( from,to ) ) return YES;
	else return NO;
}
Private Bool forceto( const char*to){ if(!unlink(to)) return YES;return NO; }
Private Bool forceerror( const char*to){ 
	printf("ln:Existing destination %s\n",to);
	exit(1);
}
/* end IMPLEMENTATION sector */
Private func funlink[]={makehlink,makeslink};
FuncPt force[2]={forceerror,forceto};

int main( const int argc,const char**argv )
{
	if(argc>1){
	  char ch,fact=0,*suffixvalue="~";
	  Bool backup=NO,targetdir=NO,v=NO,s=NO,i=NO,f=NO,T=NO,b=NO,S=NO,t=NO;
	  int nfile=countFileOpt(argc,argv);
	  while( (ch=getOpt(argc,argv,option))!=NULL ){
		switch(ch){
			case '-': 
			  if( !cmpString(getpopt(),"help") ) /*SUPPORTED*/
			    if(nfile<2) {printf(help);exit(0);}
			  if( !cmpString(getpopt(),"version") ) /*SUPPORTED*/
				if(nfile<2) {printf(version);exit(0);}
			  if( !cmpString( getpopt(),"target-directory") )
				targetdir=YES;
			  if( !cmpString( getpopt(),"backup") ) backup=YES;/*SUPPORTED*/
			  if( !cmpString( getpopt(),"verbose") ) v=YES;/*SUPPORTED*/
			  if( !cmpString( getpopt(),"symbolic") ) s=YES;/*SUPPORTED*/
			  if( !cmpString( getpopt(),"force") ) f=YES; /*SUPPORTED*/
			  if( !cmpString( getpopt(),"suffix" )) { /*SUPPORTED*/
				S=YES;
				if(OpthasValue()) 
				suffixvalue=getpval();
			  }
			break;
			case 's':s=YES;break;/*SUPPORTED*/
			case 'i':i=YES;break;/*SUPPORTED*/
			case 'f':f=YES;break;/*SUPPORTED*/
			case 'v':v=YES;break;/*SUPPORTED*/
			case 'T':T=YES;break;
			case 't':t=YES;break;
			case 'b':b=YES;break;
			case ':': 
			{
			  fact++;
			  if( nfile<2 ) printf(nofile);
			  else {
				if( fact==2 ) {
					int posfile=scanFileOpt( argc, argv);
					short from=get_word_low(posfile);
					short to=get_word_high(posfile);
					if( !ifexist(argv[to]) ) {
						if(b==YES) {
						  /* FIXME function to rename */
						  cpyString(buf,argv[to]);
						  catString(buf,suffixvalue);
						  rename(argv[to],buf);
						}
						if(i==YES) {
						   printf("ln: remove %s(y)? ",argv[to]);
						   char req[2]={[0]='y'};
						   read( 0,req,1);
						   if( req[0]=='y' ) 
						   {
						      unlink(argv[to]);
						      kprint("\n");
						   }
						   else 
						   {
						      kprint("ln: U cancel make link\n");
						      exit(0);
						   }
						}
						if(i==NO&&!ifexist(argv[to]) ) 
							force[f](argv[to]);
					}
					if( !ifexist(argv[from]) ) {
						int ret =funlink[s](argv[from],argv[to]);
						if(ret==NO) 
							printf("ln: cant make link %s\n",argv[to]); 
						if( ifexist(argv[to]) ) 
							printf("ln: destination %s not exist.\n",argv[to]);
						} else printf("ln: %s dont exist.\n",argv[from]);
					VERBOSE(v);
				}
             		  }
			  break;
			}
			case '?': 
				printf("ln: unknown option: %c\n",*getpopt()); break;
			default:  
				printf("This option not support this time:%c\n",ch);
				break;
		}
	}
} else printf("ln: missing argument. Try help\n");
   return 0;
}

