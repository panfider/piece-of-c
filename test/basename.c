/*
	basename.c Copyright (c) 2010 Pham The Chung
	lastdate June 1 2010
*/
/*
	note
	 this file near all in one except stdio.h
	compile success with:
	gcc test/basename.c -Iinclude
*/
#include <stdio.h>
#include "piece/itype.h"
/* configuration sector */
#define WinDow 1
#define Unix 0
#define UseSep Unix

/* variable */
Private char help[]=
		"basename get the last name in path\n\
Usage: basename [option] path path2\n\
Option:\n\
	--byte=N		get N byte from result basename\n\
	--sep=c			use character separator when multi-basename\n\
	-b --basename	get base name\n\
	-p --pathname	get path name\n\
	--help			display this help\n\
	-v --version	display version\n\
	";
Private char version[]="basename version 0.1\n\
Written by Pham The Chung.\n";
Private char option[]="bpv";
/* end of variable */

/* IMPLEMENTATION */
long fy( int a,int b ){
	long ret=-1;
	char size=sizeof(long);
	char isize=sizeof(int);
	if(size==isize*2){
		isize/=2;
		short aa=(short)a;
		short ab=(short)b;
		ret=ab;
		ret <<= (isize*8);
		ret|=aa;
		return ret;
	}
	if( size==(isize*2) ){
		ret=b;
		ret<<=(sizeof(int)*8);
		if(ret==0) {ret=b;ret<<=16;}
		ret+=a;
		return ret;
	}
	return ERROR;
}
int getly( long n ){
	char isize=sizeof(int);
	char size=sizeof(long);
	if(size==isize*2){
		short ret;
		isize/=2;
		n<<=(isize*8);
		n>>=(isize*8);
		ret=n;
		return ret;
	}
	if( size==(isize*2) ){
		int ret;
		n<<=(isize*8);
		n>>=(isize*8);
		ret = n;
		return ret;
	}
	return -1;
}
int gethy(long n){
	char isize=sizeof(int);
	char size=sizeof(long);
	if(size==isize*2){
		short ret;
		isize/=2;
		n>>=(isize*8);
		ret=n;
		return ret;
	}
	if( size==(isize*2) ){
		int ret;
		n>>=(isize*8);
		ret = n;
		return ret;
	}
	return -1;
}
/* return number of character in name */
int slen( const char *name ){
	int run=0;
	while( *(name+run)!=NULL ) run++;
	return run;
}
/*	return position of ch in str if finded */
int searchChar( const char*str,char ch ){
	if( str==NULL ) return 0;
	int run=0;
	while( *(str+run)!=NULL ) {
		if( *(str+run)==ch ) return run;
		run++;
	}
	return 0;
}
Public char* cpyString ( char *dest,const char *src ) {
	if( dest==NULL||src==NULL ) return dest;
	const char *this=src;
	unsigned r=0;
	while( *(this+r)!=0x0 ) {
		*(dest+r) = *(this+r);
		r++;
	}
	*(dest+r)=NULL;
	return dest;
}
Public long cmpStringn( const char *sa,const char *sb,int bytes) {
	unsigned r=0;
	const char *ss = sa;
	while( bytes-- ){
		if(*sa==*sb) {
			if( *sa==0x0&&*sb==0x0 )
				return 0;
			sa++; sb++;
		} 
		else return sa-ss+1;
	}
	return 0;
}
/*	must be complete same to return 0 	*/
#define max(a,b) (a>b?a:b)
Public long cmpString( const char *a,const char *b ){
	//if( a==NULL||b==NULL ) return -1;
	const char *oa=a,*ob=b;  // get the original of a and b
	unsigned same=0,roa=0,rob=0;
	while( *(a+roa)!=NULL ) roa++;
	while( *(b+rob)!=NULL ) rob++;
	if ( roa!=rob ) return max(roa,rob);
	while( *a==*b ){
		same++;
		if( *a==NULL&&*b==NULL )
			return (a-oa) - (b-ob);
		a++;b++;
	}
	return max(roa,rob)-same;  // return at least 1
}
/* option processing section */
int countShortOpt( int c, const char**list ){
	if( list==NULL ) return 0;
	short count=0,run=1;
	while( c>1 ){
		if( *list[run]=='-'&&*list[run]!='-' ) count++;
		c--;run++;
	}
	return count;
}

Public int countFileOpt(int c,const char**list){
	if( list==NULL ) return ERROR;
	short r=1,count=0;
	while ( c>1 ){
		if( *list[r]!='-' ) count++;
		r++;c--;
	}
	return count;
}
int searchNameOpt( int c,const char**list ){
	if( c<2 ) return 0;
	short run=1,nf,nl=1;
	char first=0;
	while( c>1 ){
		if( *list[run]!='-' ) {
			if(first==0) nf=run;
			else nl=run;
		}
		if( first==0 ) first++;
		c--;run++;
	}
	return fy(nf,nl);
}
/* end of option processing section */
char *cpyStringn( char*a,const char*b,int c){
	if( b==NULL ) return a;
	int run=0;
	while( c-- ) *(a+run)=*(b+run++);
	return a;
}
/*
	TESTED 
	/path/to/filename{/} ->filename
*/
static char bufname[256];
static char sep[2]={'/','\\'}; //sep[UseSep] configurarion
char *basename( const char *name ){
	if( name==NULL ) return name;
	int run=0,pos,len=0,byte=0;
	while( *(name+len)!=NULL ) len++;
	//while( name[len-1]==sep[UseSep] ) 
		if( name[len-1]==sep[UseSep] ) {pos=len-2;len-=1;}
	else pos=len-1;
	while( len-- ){
		if( name[pos]==sep[UseSep] ) {pos++;break;}
		byte++;pos--;
	}
	if( pos<0 ) pos=0;
	//return name+pos;
	return cpyStringn( bufname,name+pos,byte);
}
#define PATHBUF 8192
static char bufpath[PATHBUF];
Public char *pathname(const char *path) {
	if( path==NULL ) return path;
	short i,len=0,alen;
	char *pt;
	while( *(path+len)!='\0' ) ++len;  //get lenght of path
	while( len ) {
		if( *(path+len)==sep[UseSep] ) break;
		len--;
	}
	len++;
	if( len<PATHBUF )
		pt = bufpath;//(char*) malloc(len);
	else return NULL;
	return cpyStringn(pt,path,len); /*cpyStringn also terminate str */

}
Public long findChar( const char *s,const char ch ){
	if( s==NULL ) return -1;
	unsigned r=0,run=0;
	while( *(s+r)!=NULL ) r++; 
	while( r--!=0 ) {
		if( s[run++]==ch ) return 0;
	}
	return 1;
}
/* function getOpt */
Private char opt_buf[256];
Private char val_buf[256];
Private char *poopt=NULL;
Private char *popt=NULL;
Private char *pval=NULL;
Private int pos=1;
Private int elem=1;
Public char getOpt( int c,const char**list,const char *optlist) {
	char ret=NULL;
	char len=slen(optlist),count=0;
	if( pos<c ){
		if( *list[pos]=='-' ){
			if( *(list[pos]+1)=='-' ){
				ret='-';char epos=0,*pt2=(char*)(list[pos]+2);
				poopt=list[pos];
				if( !findChar(list[pos],'=') ){
					epos=searchChar(pt2,'=');
					pval=cpyString(val_buf,pt2+epos-- );
				}else{epos=slen(pt2);pval=NULL;}
				popt=cpyStringn(opt_buf,pt2,epos);
				pos++;
				return ret;
			} else{
				char countshort=slen(list[pos]+1);poopt=list[pos];
				if( !findChar(list[pos],'=' ) ){
					ret='-';
					popt=cpyStringn(opt_buf,list[pos]+1,searchChar(list[pos],'=')-2);
					pval=cpyString(val_buf,list[pos]+searchChar(list[pos],'=') );
					pos++;
				}else{
					if ( !findChar(optlist,*(list[pos]+elem)) ) ret=*(list[pos]+elem);
					else {ret='?';popt=list[pos]+elem;}
					if( elem>=countshort ) { pos++;elem=1;}
					else elem++;
				}
				return ret;
			}
		}else{
			popt=cpyString(opt_buf,list[pos++]);
			return ':';
		}
	}
	return NULL;
}
Public char OpthasValue( NoThing ){
	if( !findChar(poopt,'=') ) {
		int size=slen(poopt+searchChar(poopt,'='));
		if( size!=0 )	return YES;
	}
	pval=NULL;
	return NO;
}
/* TESTED
	[return] number of long option
*/
Public int countlongOpt(int c,const char**list){
	if( list==NULL ) return ERROR;
	short r=1,count=0;
	while( c>1 ){
		if( !cmpStringn(list[r],"--",2) ) count++;
		r++;c--;
	}
	return count;
}
#define VERSION(x) (x==1?printf(version):"")
typedef char*(*Fb)(char*);
Fb fa[]={basename,pathname};
int main( const int argc, const char**argv ){
	char v=0,b=0,h=0;
	if( argc>1 ) {
		char ch;
		int n=searchNameOpt(argc,argv); //run wrong
		int file=countFileOpt(argc,argv);
		while( (ch=getOpt(argc,argv,option)) ){
			switch(ch){
				case 'v':v=YES;break;
				case 'p':b=NO;break;
				case 'b':b=YES;break;
				case '-':{
					if( !cmpString(popt,"version") ) v=YES;
					if( !cmpString(popt,"help") ) printf(help);
					//if( !cmpString(popt,"byte") ) 
					break;
				}
				case ':':
					printf( "%s",fa[b](popt) );
					break;
			}
		}
		if(file==0) VERSION(v);	
	}
	printf("\n");
	exit(0);
}
/* reserve line below */
