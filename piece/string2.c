/*
	Written by Pham The Chung
	create March 1 2010
	piece_string2.c
	gcc [-m32/64] -c string2.c -Iinclude
*/
/*
	compile success
*/
#include <piece/piece_code.h>
/*temporary def*/
#define NULL (0) 
typedef int size_t;

IMPLEMENT(long, strlen)( const char *s ) {
	if( s==(0x0) ) return 0;
	unsigned long run=0;
	while( *(s+run)!=NULL ) run++;
	return run;
}

IMPLEMENT(char *,strcpy) ( char *dest,const char *src ) {
	if( dest==NULL||src==NULL ) return dest;
	const char *this=src;
	unsigned r=0;
	while( *(this+r)!=NULL ) {
		*(dest+r) = *(this+r);
		r++;
	}
	*(dest+r)=NULL;
	return dest;
}
IMPLEMENT(char *,strncpy) (char *dest,const char *src,size_t n){
	if( n<0 ) n=-n;
	if( dest==NULL||src==NULL ) return dest;
	const char *s= src;
	char *d= dest;
	unsigned r=0;
	while( n--!=0 ) *d++ = *(s+r++);
	*d=0x0;
	return dest;
}
IMPLEMENT(long, strcmp)( const char *a,const char *b ){
	#define max(a,b) ((a)>(b)?(a):(b))
	// get the original of a and b
	const char *oa=a,*ob=b;  
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
IMPLEMENT(int,strncmp)(const char *sa,const char *sb,size_t n){
        const char *ss = sa;
        while( n-- ){
                if(*sa==*sb) {
                        if( *sa==0x0&&*sb==0x0 )
                                return 0;
                        sa++; sb++;
                }
                else return sa-ss+1;
        }
        return 0;
}
IMPLEMENT(char *,strcat) ( char *dest,const char *src ) {
	if( src ==0x0 ) return 0x0;
	const char *s=src; char *d=dest;
	int pos=0;
	while( *(d+pos)!=NULL ) pos++;
	while( *s!=NULL ){
		*(d+pos++) = *s++;
	}
	*(d+pos)=NULL;
	return dest;
}
IMPLEMENT(char *,strncat) ( char *dest,const char *src,size_t n ) {
	if( n<0 ) n=-n;
	if( dest==NULL||src==NULL ) return dest;
	char *s= (char*)src; char *d = dest;
	int r=0;
	while( *++d!=0x0 );
	while( n--!=0 ) {
		*d++ = *( s+r++ );
	}
	return dest;
}
IMPLEMENT(char *,cpyStringat)(char *this, const char *src,int pos) {
	if( src ==NULL||this==NULL ) return this;
	while( *src!= 0x0 ) 
		*(this+++pos) = *src++;
	*(this+pos) = 0x0;
	return this;
}
IMPLEMENT(long ,strstr)(const char *long_string, const char *str) {
	const char *word=long_string;
	unsigned ii=0,run=0,len;
	int ret;
	while( *(str+ii)!= NULL ) ii++;
	len = ii;
	ii=0;
	while( *(word+run) != NULL ) {
		if( *(word+run)==*str ) {
			str++;
			ii++;
		}
		else if( ii>0 ){
			return run;
		}
		if( ii==len ) break;
		run++;
	}
	return len-ii;
}

IMPLEMENT(void *,memcpy)(void *dest,const void *src,size_t n) {
	if( dest==NULL||src==NULL ) return dest;
	char *d,*s;
	d = (char *)dest;
	s = (char *)src;
	while( n--!=0 ) *d++ = *s++;
	return dest;
}

IMPLEMENT(int, memcmp)(const void *a,const void *b, size_t c) {
	if ( c==0 ) return 1;
	if( a==NULL&&b==NULL ) return 0;
	char flag=0;
	if ( c<0 ) {c=-c;flag=1;};
	const char *x = (const char*) a;
	const char *y = (const char*) b;
	long run=0;
	while( c-- ){
		if( x[run]!=y[run++] ) return run;
	}
	return 0;
}
/*	memset set char */
IMPLEMENT(void *,memset)(void *this, char n,long c){
	if(c<0) c=-c;
	if( this==NULL ) return this;
	long r=0;
	char *m = (char*)this;
	while( c--!=0 ){
		*( m+r++ ) = n;// 1 bytes
	}
	return this;
}
char name_buf[257];
IMPLEMENT(char *,basename)(const char *path) {
	short len=0;
	unsigned char *pt,r=0,sep;
	sep='/';
	while( *( path+len )!=NULL) ++len;
	short alen=len;
	short first=len-1;
	char *one= path+len-1;
	do{
		if( *one--==sep )
			if( first==(len-1))
			{	first--;continue;	}
			else {break;}
	} while( --len!=0 );
	alen -= len;	// alen is string len of filename
	pt = name_buf;
	char *gap=path+len;
	while( *(gap)!=NULL )  *(pt+r++) = *(gap++);
 	if( *(pt+r-1)!=sep ) *(pt+r) = NULL;
	else *(pt+r-1) =NULL;
	return pt;
}
