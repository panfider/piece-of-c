/*
	getopt.h 2010
	Written by Pham The Chung
	CONTACT pham.the.chung0@gmail.com
	Create Jan 1 2010
*/
#ifndef _GETOPT_H
#define _GETOPT_H
#include <piece/piecetype.h>
#include <piece/itype.h>


/* TESTED
	char ch;
	while( (ch=getopt(argc,argv,"abc"))!=NULL ){
		switch(ch){
			case ':': printf("file: %s \n",getpopt());break;
			case '-': if( OpthasValue() )
					printf("long opt:%s=%s\n",getpopt(),getpval());
					 else printf("long opt:%s\n",getpopt());
					break;
			case '?': printf("unknown option: %c\n",*getpopt()); break;
			default:  printf("option:%c \n",ch);break;
		}
	}
	getopt under test condition 20092112 woking
 * 	optlist. I note some special char:
 * 		 ':' a string alone, getpopt()
 * 		 '?' not in option list
 * 		 '-' long option style like --version --help --mode=640
 			if have value(equal sign) call getpval()
 			if has equal sign in short option like -mode=0640
 			if will regconize it like long option
 			can use both short and long option
*/

Link Public char getopt(int __argc,char *const *__list,const char *__shortopt);
/* TESTED
*/
Link Public Bool OpthasValue( void );
/*
	comming soon
*/
Link Public int getopt_long( int c, const char**list,const char**list_long_opt );
/* TESTED
	count option look like a file
	return number of option file
*/
Link Public int countFileOpt(int c,const char**list);
/* TESTED
	return half below is position first file
	above is last file
	[usage]
		argv[get_word_low(scanFileOpt(argc,argv))] to get first file name string
		argv[get_word_high(scanFileOpt(argc,argv))] to get last file name string
*/
Link Public int scanFileOpt( int c, const char**list);

/*
	return map bit map with long option position
	so it base on number of bit of long type 32 or 64
*/
Public long getlongOptMap( int c,char**list);
/*
	pass the declaration char *pt[countlongOpt(argc,argv)]; to pt
	[return] pt has a map to long opt in argv
*/
Link Public long maplongOpt(int c,char**list,char**pt);
/*
	[return] number of long option
*/
Link Public int countlongOpt(int c, char**list);
/*
	[return] number of short option
*/
Link Public int countshortOpt( int c,char**list);
/*
	check the pointer to long opt has value
	if have return 1  , no return 0
	use getpval to get value when has value
*/
Link Public Bool chkhasValue( char*pt );
/*
	after call getOpt or cmdswitch use resetOpt to 
	void damage or segment fault
*/
Link Public void resetOpt ( void );
/* TESTED
	getpopt to get the value of opt when long option for file name
	use with getOpt getlongOpt function
*/
Link Public char *getpopt( NoThing );
/*TESTED
	get string of value in long option has value --long=123
*/
Link Public char *getpval( NoThing ) ;

#endif
