/*
	written by Pham The Chung
	June 1 2010
*/
/*
	 gcc -c piece/stdlib.c -Iinclude
*/
#include <piece/piece_code.h>
#include <piece/itype.h>
#define NULL (0)
Public PIECE_IMPLE(long ,atol)( char*a ){
        if( a==NULL ) return 0;
        inline long _C_pow10__(char base,char len){
                long val=base;
                while(len--)    val *= 10;
                return val;
        }
        long i=0;
        char r=0,flag=0,tmp,len=0;
        while( a[len]!=NULL ) len++;
        if( *a=='-' ) {flag=1;r++;len--;}
        char e=len-1;
        while( len-- ){
                tmp = a[r++]- 0x30;
                i += _C_pow10__(tmp,e--);
        }
        if(flag==1) i=-i;
        return i;
}
Private char i2a_buf[22];
Public PIECE_IMPLE(char *,ltoa)( long i ) {
        char *a=i2a_buf,run=0;  // 256 bytes
        long io=i;
        if(io<0){
                io = -io;
                a[run++]='-';
        }
        while(io){
                char tmp=io%10;
                a[run++] = tmp+0x30;
                io /= 10;
        }
        a[run]=NULL; //terminate string
        char e=run-1,r=0,h;
        if( a[0]=='-') {h=e/2;r=1;}
        else h=run/2;
        char tmp;
        while( h-- ){
                tmp = a[r];
		a[r++] = a[e];
                a[e--] = tmp;
        }
        return a;
}
Private char chex[]={   [0]='0', [1]='1', [2]='2', [3]='3',
                           [4]='4', [5]='5', [6]='6', [7]='7',
                           [8]='8', [9]='9', [10]='a',[11]='b',
                           [12]='c',[13]='d',[14]='e',[15]='f'  };

Private char i2ah_buf[32];
Public PIECE_IMPLE(char *,i2ah)( long i ){
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

