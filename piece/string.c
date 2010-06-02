/*
 *	string.c create in 20 Nov 2009
 *	Copyright (c) Clib 2010 Pham The Chung
 *	Read terms below
 *	Chung terms(my terms):
 *		free to distribute and copy
 *		free for commercial purpose
 *	contact : pham.the.chung0@gmail.com
 *	for any question in this code
 *	last date : Fri 29 Jan 2010 01:33:18 PM ICT 
 *
 **/
/*
	continue at line 325
*/
#define string_series 7000
/* this is configure when compile with os */
#ifndef win
	#define win 0
	#define win32 0
#endif
#ifndef unix
	#define unix 1
#endif
/*	end of configure	*/
	#include "basetype.h"
	#include "itype.h"
#ifndef size_t 
	#define size_t dword
#endif
#define PATHBUF 4096
Private char s_buf[256];
Private char p_buf[PATHBUF];
/*	prototype function section	*/
Public void *cpymem( void *dest,const void *src,long n );
Public void uswap(  void*,void*,unsigned );
Public void swapc(long*,long*);
Public void *swapPointer( void**,void** );
Public long slen( char *s );
Public long cmpString( const char *a,const char *b);
Public long cmpStringn( const char *sa,const char *sb,int bytes);
Public char* cpyString ( char *dest,const char *src );
Public char* catString ( char *dest,const char *src );
Public char *i2a( long i );
Public long a2i( char *a );
Public char *cpyStringat( char*this, const char*source,int pos );
/*	implementation section	*/
/*
Private Object string_object;
Private Object_Pointer string_object_pointer=&string_object;
Private byte *string_u=
		"string object version 0.1 .In process implement of string";
Public void *string_action( void*vpt ){
	return "Pham The Chung string object implementation";
}
Public Object_Pointer get_string_object(void){
	string_object_pointer->self=string_object_pointer;
	cpyString( string_object_pointer->name,string_u );
	catString( string_object_pointer->name,i2a( string_series ) );
	string_object_pointer->val=string_series;
	string_object_pointer->action=string_action;
	return string_object_pointer;
}
*/
/*	I dont know cmpfun compare what	*/
Public void*bsearch( const void *key,
				 const void *base,
				 size_t nmemb,
				 size_t size,
				 int (*cmpfun)(const void *a,const void *b) )
{
	long how_many=nmemb*size;
	long run=0;
	const void *pt=base;
	while( run<nmemb ) {
		pt += run*size;
		if( !cmpfun(key,pt) ) return (void*)pt;
		run++;
	}
	return NULL;
}
/*	tested	*/
Public void swapc(long *a,long *b){
	long t;
	t = *a;
	*a = *b;
	*b = t;
}
/*	*tested* swap data in memory	*/
Public void uswap( void*a,void*b,unsigned many ){
	char t[many];
	cpymem( (void*)t,a,many );
	cpymem( a,b,many );
	cpymem(b,t,many);
}
/*	*tested*	*/
Public void*swapPointer(void**a,void**b){void*t;t=*a;*a=*b;*b=t;return(a);}
/*	
 *	search string in list compare by cmpfun()	
 **/
Public char* searchString( const char *key, const char *list[],unsigned how_many, 
				long (*cmpfun)(const char *a,const char *b)) {
	unsigned run=0;
	while( how_many--!=0 ) {
		if( !cmpfun( key,list[run] ) ) 
			return (char*)list[run];
		run++;
	}
	return (char*)NULL;
}
Public char *searchList( const char *key,const char *list[] ) {
	if( key==NULL||list==NULL ) return NULL;
	unsigned r=0;
	while( list[r]!=NULL ){
		if( !cmpString( key,list[r] ) ) return (char*)list[r];
		r++;
	}
	return NULL;
}

/*	>tested< return first bit set begining with 0	*/
Public int findBit(int n) {
	short i=8*sizeof(n),r=0;
	--i;
	while( r!=i ){
		if(get_bit(n,r)) break;
		r++;
	}
	if(r==i) return 0;
	return r;
}
	
/*	>tested< 1 cmp n bytes */
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

//  test 1;concatenate dest <-- src
Public char* catString ( char *dest,const char *src ) {
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
/*	*tested* 1;
	 cat n char from src to dest; 
	 at least dest has 1 char and terminate
*/
Public char *catStringn ( char *dest,const char *src,long n ) {
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
/*	--> test 2; checked <--*/
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
/*	test 1; copy n char from src to dest */
Public char *cpyStringn ( char *dest,const char *src,long n ) {
	if( n<0 ) n=-n;
	if( dest==NULL||src==NULL ) return dest;
	const char *s= src;
	char *d= dest;
	unsigned r=0;
	while( n--!=0 ) *d++ = *(s+r++);
	*d=0x0;
	return dest;
}
/*
 *	list[] must have NULL char at end of list
 * */
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
/*	
 * 	strcp: this <- source;  copy s->this at pos in this
 * */
Public char *cpyStringat( char*this, const char*source,int pos ) {
	if( source ==NULL||this==NULL ) return this;
	//char *is = source; 
	while( *source!= 0x0 ) 
		*(this+++pos) = *source++;
	*(this+pos) = 0x0;
	return this;
}
/* 
 * this function is under test status 
 * if completely same return 0 if no return position diff begin 1
 * target is compare exactly the same is aganst not shame
 * */
Public long cmps( const char *a, const char *b )
{
	if( (a==0x0)&&(b==0x0) ) return 0;
	const char *s = a;
	const char *d = b;
	for ( ; *a==*b ; a++,b++ ) 
		if( (*a == 0x0)&&(*b==0x0) ) 
			return (a-s) - (b-d);
	return (++a-s);
}
/*	must be complete same to return 0 	*/

Public long cmpString( const char *a,const char *b ){
	#define max(a,b) (a>b?a:b)
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
// count how many byte in string
Public long strlen( const char *s ) {
	if( s==0x0 ) return -1;
	const char *ss=s;
	while( *s++!=0x0 );
	return s-ss-1; 
}
// 
Public long slen( char *s ) {
	if( s==0x0 ) return ERROR;
	unsigned long run=0;
	// while( *(s+(++r) ) !=0x0 );
	while( *(s+run)!=NULL ) run++;
	return run;
}
/*	convert float to hex string 	*/
Private char chex[]={   [0]='0', [1]='1', [2]='2', [3]='3',
			   [4]='4', [5]='5', [6]='6', [7]='7',
			   [8]='8', [9]='9', [10]='a',[11]='b',
			   [12]='c',[13]='d',[14]='e',[15]='f'	};
Private char fpf2h_buf[4+1];
Public char *fpf2h(	float f ){
	char *pt=fpf2h_buf;
	
	return pt;
}
/* convert double to hex and reverse; need implementation */
Private char fpd2h_buf[8+1];
Public char * fpd2h( double f ){
	char *pt=fpd2h_buf;

	return pt;
}
/*
	convert a floating point number of string to double
*/
double a2fpd( char*a ){
	double ret;
	
	return ret;
}
/*	
	*tested* well working 
	convert a long int to char
*/
Private char i2a_buf[22];
Public char *i2a( long i ) {
	byte *a=i2a_buf,run=0;  // 256 bytes
	long io=i;
	if(io<0){
		io = -io;
		a[run++]='-';
	}
	while(io){
		byte tmp=io%10;
		a[run++] = tmp+0x30;
		io /= 10;
	}
	a[run]=NULL; //terminate string
	byte e=run-1,r=0,h;
	if( a[0]=='-') {h=e/2;r=1;}
	else h=run/2;
	byte tmp;
	while( h-- ){
		tmp = a[r];
		a[r++] = a[e];
		a[e--] = tmp;
	}
	return a;
} 
/*	*TESTED* convert string a to long 	
*/
Public long a2i( char*a ){
	if( a==NULL ) return 0;
	inline long _C_pow10__(byte base,byte len){
		long val=base;
		while(len--)	val *= 10;
		return val;
	}
	long i=0;
	byte r=0,flag=0,tmp,len=0;
	while( a[len]!=NULL ) len++;
	if( *a=='-' ) {flag=1;r++;len--;}
	byte e=len-1;
	while( len-- ){
		tmp = a[r++]- 0x30;
		i += _C_pow10__(tmp,e--);
	}
	if(flag==1) i=-i;
	return i;
}
/*	
	*tested* with positive
	convert long to hex	
	may be wrong with negative number
*/
Private char i2ah_buf[32];
Public char*i2ah( long i ){
	char *pt=i2ah_buf;
	char run=0;
	while( i ){
		long t;
		t=i%16;
		i/=16;
		pt[run++]=chex[t];
	}
	pt[run]='\0';
	char h=run-1,r=0,l=h/2;
	while( l-- ){
		char t=pt[r];
		pt[r++]=pt[h];
		pt[h--]=t;
	}
	return pt;
}

// set bpath from path ,return bpath
Public char *getPath ( const char *path,char *bpath ) {
	short i,len=0;
	while( *(path+len)!='\0' ) ++len;  //get lenght of path
	while( len!= 0) {
		len--;
		if(*(path+len)=='/')	break;
	}
	for( i=0;i<=len;i++ )
		*(bpath+i) = *(path+i);
	*(bpath+len+1)=NULL;
}
/* get filename of path set it to name
	bashname return if /root/abc.c then abc.c
*/
Public char *getName ( const char *path,char *name ) {
	short len=0;
	while( *(path+len)!='\0' ) ++len; // get lenght of path
	while( len!= 0) {
		len--;
		if(*(path+len)=='/'){
			len++;
			break;
		}
	}
	while( *(path+len)!=0x0) {
		*name++=*(path+len++) ;
	}
	*name = NULL;
}

/*	*tested* return pathname if has different in some case
	like this: path/to/file return : path/to
	but this : path/to/file/ return path/to/file
	if wanted to change this case may modify code
*/
Public char *pathname(char *path) {
	short i,len=0,alen;
	char *pt,sep='\\';
	if( win32 == 1 ) sep='\\';
	if( unix == 1 ) sep='/';
	while( *(path+len)!='\0' ) ++len;  //get lenght of path
	while( len!=0 ) {
		if( *(path+len)==sep ) break;
		len--;
	}
	len++;
	if( len<PATHBUF )
		pt = p_buf;//(char*) malloc(len);
	else return NULL;
	cpyStringn(pt,path,len); /*cpyStringn also terminate str */
	return pt;
}

/*	*tested_all* status of this function is very healthy	*/
Public char *basename(char *path) {
	short len=0;
	unsigned char *pt,r=0,sep;
	if( win == 1 ) sep='\\';
	if( unix == 1 ) sep='/';
	while( *( path+len )!=0x0) ++len;
	short alen=len;
	short first=len-1;
	char *one= path+len-1;
	// while loop get position of filename -->len
	do{
		if( *one--==sep )
			if( first==(len-1))
			{	first--;continue;	}
			else {break;}
	} while( --len!=0 );
	alen -= len;	// alen is string len of filename
	pt = s_buf; 	// need malloc function to repace global vaiable
	char *gap=path+len;
	while( *(gap)!=0x0 )  *(pt+r++) = *(gap++);
 	if( *(pt+r-1)!=sep ) *(pt+r) = 0x0;
	else *(pt+r-1) =0x0;
	return pt;
}
/* 
 * tested; find char int s string;  strchar like function
 * return -1 or 1 if null string or not found,
 * if found char return 0
 * */
Public long findChar( const char *s,const char ch ){
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
Public long searchChar( const char*str, char ch ){
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
 *	tested; return 0 if first occurence whole word str in long_string 
 *	else return the position differece not zero
 **/
Public long cmpstrstr(const char *long_string, const char *str) {
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
/*
 * 	count identifier, line ,
 * */
Public long wc( const void*mem,int return_what ){
	const char *pt=(const char*)mem;
	int what=return_what;
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
			in = 0;
			out= 1;		
		}
		pt++;
	}while( *pt!=NULL );
	switch(what){
		case 0:
		case 1:return nline;break;
		case 2:return nword;break;
		case 3:
		case 4:return code_line;break;
		default:return -1;break;
	}
}
/*	this region for memory function*/
Public void *cpymem( void *dest,const void *src,long n ) {
	if( dest==NULL||src==NULL ) return dest;
	char *d,*s;
	d = (char *)dest;
	s = (char *)src;
	while( n--!=0 ) *d++ = *s++;
	return dest;
}
/*	memset set char */
Public void *setmem( void *this, char n,long c ) {
	if(c<0) c=-c;
	if( this==NULL ) return this;
	long r=0;
	char *m = (char*)this;
	while( c--!=0 ){
		*( m+r++ ) = n;// 1 bytes
	}
	return this;
}
/*
 * return 0 if same
 * it can only compare forward not backward direction
 **/
Public long cmpmem( const void *a,const void *b, long c ) {
	if ( c==0 ) return 1;
	if( a==NULL&&b==NULL ) return 0;
	byte flag=0;
	if ( c<0 ) {c=-c;flag=1;};
	const char *x = (const char*) a;
	const char *y = (const char*) b;
	long run=0;
	while( c-- ){
		if( x[run]!=y[run++] ) return run;
	}
	return 0;
}
/* I reserve the line below */

