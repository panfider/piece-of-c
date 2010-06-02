/*
	Written by Pham The Chung
	June 1 2010
*/
#include <piece/piece_code.h>
#include <piece/itype.h>

#define NULL (0)
/*
	like strcmp()
*/
static long cmps( const char *a, const char *b )
{
	if( (a==0x0)&&(b==0x0) ) return 0;
	const char *s = a;
	const char *d = b;
	for ( ; *a==*b ; a++,b++ ) 
		if( (*a == 0x0)&&(*b==0x0) ) 
			return (a-s) - (b-d);
	return (++a-s);
}
Public char **cpyList( char *dest[],char *list[] ){
	if( dest==NULL||list==NULL) return dest;
	unsigned r=0;
	while( list[r]!=NULL ){
		cpyString(dest[r],list[r]);
		r++;
	}
	return dest;
}
Public char *catList( char*dest,char*list[] ){
	if( dest==NULL||list==NULL) return dest;
	unsigned r=0;
	while( list[r]!=NULL ){
		cpyStringat( dest,list[r],slen(dest) );
		r++;
	}
	return dest;
}

Public char *searchList( const char *key,const char *list[] ) {
	if( key==NULL||list==NULL ) return NULL;
	unsigned r=0;
	while( list[r]!=NULL ){
		if( !PIECE_CALL(strcmp)( key,list[r] ) ) return (char*)list[r];
		r++;
	}
	return NULL;
}
struct wc_ret{
	int nrline;
	int nrword;
	int nrcodeline;
};
long wc( const void *mem,struct *wc_ret ){
	if(mem==NULL) return -1;
	const char *pt=(const char*)mem;
	unsigned nline=0,nword=0,code_line=0;
	char in=0,out=1,cin=0,cout=1,cstate=0,comment_count=0,one=1,text=1;
	do{
		if( *pt=='/'&& *(pt+1)=='*' ) {
			one=0;
			cin=1;
			if( cin==1&&cout==1) {cstate=1;comment_count++;}
			cout=0;
		}
		if( *pt=='*'&&*(pt+1)=='/') {cin=0;
			if(cin==0&&cout==0) cstate=0;
			cout=1;
		}
		if( *pt==0xa&&cstate==0&&one==1 ) {code_line++;}
		if( *pt==0xa )	{nline++;one=1;}
		if( (*pt>=0x40&&*pt<=0x5f)||(*pt>=0x61&&*pt<=0x7a ) ) {
			in=1;
			if((in==1)&&(out==1)) ++nword;
			out=0;
		}
		if(*pt==0x20||*pt==0x09||*pt==0x0a) {
			in = 0;out= 1;		
		}
		pt++;
	}while( *pt!=NULL );
	if(wc_ret!=NULL){
		wc_ret->nrline=nline;
		wc_ret->nrword=nword;
		wc_ret->nrcodelone=code_line;
	}
	return nline;
}
