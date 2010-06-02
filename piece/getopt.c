/*
 *	Written by Pham The Chung
 *
 *	This program is free software;
 *	you can redistribute it or modify it
 *	under the term of the GNU General Public License as
 *	published by Free Software Foundation
 *	create Jan 1 2010 LASTDATE Sat 30 Jan 2010 08:39:18 PM ICT
 *
 * */
/*
 *  	This file need string.h implement by string.c of this clib to copy string
 * 	cmdswitch under test condition 20092112 but still woking in good condition
 * 	after call it will return char of found both in optlist and option on command.
 * 	I note some special char will return:
 * 		 ':' a string alone, cmdswitch() set popt pointer point to
 * 		 '?' not in option list
 * 		 '-' long option style like --version use char *s=getpopt() to get "version"
 * 		     if have style like --mode=0775 if getpval() to get string "0775"
 * 		     if number use a2i() to convert it to integer type
 *			if short like -mode=0640 is also return '-'
 */
#include <piece/piece_string.h>
#include <piece/piecetype.h>
#include <piece/itype.h>

#ifndef NULL
#define NULL (0x0)
#endif

Private char opt_buf[256];
Private char val_buf[256];
Private char *poopt=NULL;
Private char *popt=NULL;
Private char *pval=NULL;
Private int pos=1;
Private int elem=1;

/*
 * tested; find char int s string;  strchar like function
 * return -1 or 1 if null string or not found,
 * if found char return 0
 * */
Private int strChar( const char *s,const char ch ){
	if( s==NULL ) return -1;
	unsigned r=0,run=0;
	while( *(s+r)!=NULL ) r++; 
	while( r--!=0 ) {
		if( s[run++]==ch ) return 0;
	}
	return 1;
}
/*
	return the position of char finded
	return NO=0 if not found
*/
Private int posChar( const char *str,char ch ){
	if(str==NULL) return ERROR;
	int pos=0;
	while( *(str+pos)!=NULL )
	{
		if( *(str+pos)==ch ) return pos+1;
		pos++;
	}
	return NO;
}
/*
	TESTED
	short and long option return :-?
*/
Public _PI(char,getopt)( int c,const char**list,const char *optlist) {
	char ret=NULL,count=0,len=strlen(optlist);
	if( pos<c ){
	  if( *list[pos]=='-' ){
		if( *(list[pos]+1)=='-' ){
			ret='-';char epos=0,*pt2=(char*)(list[pos]+2);
			poopt=list[pos];
			if( !strChar(list[pos],'=') ){
				epos=posChar(pt2,'=');
				pval=strcpy(val_buf,pt2+epos-- );             //
			}else{epos=strlen(pt2);pval=NULL;}
			popt=strncpy(opt_buf,pt2,epos);
			pos++;
			return ret;
		}
		else
		{
			char countshort=strlen(list[pos]+1);
			poopt=list[pos];
			if( !strChar(list[pos],'=' ) ){
				ret='-';
				popt=strncpy
				 (opt_buf,list[pos]+1,
						 posChar(list[pos],'=')-2);
				pval=strcpy
				(val_buf,list[pos]+posChar(list[pos],'=') );
				pos++;
			}else{
				if(!strChar(optlist,*(list[pos]+elem)))
				ret=*(list[pos]+elem);
				else {ret='?';popt=list[pos]+elem;}
				if( elem>=countshort ) { pos++;elem=1;}
				else elem++;
			}
			return ret;
		}
	  }else{
		popt=strcpy(opt_buf,list[pos++]);
		return ':';
	   }
	}
	return NULL;
}
/*	implementation	*/
Public IMPLEMENT(void,resetOpt) ( void ) {
	popt = NULL;
	pval = NULL;
	pos  = 1;
	elem = 1;
}
/* TESTED
	check size of string value if zero return no
*/
Public _PI(char, OpthasValue)( void ){
	if( !strChar(poopt,'=') ) {
		int size=strlen(poopt+posChar(poopt,'='));
		if( size!=0 )	return YES;
	}
	pval=NULL;
	return NO;
}
Public _PI(char *,getpopt)(void){
	return popt;
}
Public _PI(char *,getpval)(void){
	return pval;
}
Public int countFileOpt(int c,const char **list){
	if( list==NULL ) return ERROR;
	short r=1,count=0;
	while ( c>1 ){
		if( *list[r]!='-' ) count++;
		r++;c--;
	}
	return count;
}
/* TESTED
	give the position of first file and last file
*/
Public int scanFileOpt( int c, const char **list){
	if( list==NULL ) return ERROR;
	char size=sizeof(long);
	char first=0;
	short r=1;
	short ff=1,lf=1;
	if( c<2 ) return 0;
	while( c>1 ) {
		if( *list[r]!='-' ){
			if(first ==0 )
				ff=r;
			if(first !=0 )
				lf=r;
			first=1;
		}
		r++;	c--;
	}
	return fasten_word(ff,lf);
}
/* TESTED
	[return] number of long option
*/
Public int countlongopt(int c, char**list){
	if( list==NULL ) return ERROR;
	short r=1,count=0;
	while( c>1 ){
		if( !strncmp(list[r],"--",2) ) count++;
		r++;c--;
	}
	return count;
}
/*
	[return] number of short option
*/
Public int countshortopt( int c,char**list){
	if( list==NULL ) return ERROR;
	short r=1,count=0;
	while( c>1 ){
		if( *(list[r])=='-'&&*(list[r]+1)!='-' ) count++;
		r++;	c--;
	}
	return count;
}
