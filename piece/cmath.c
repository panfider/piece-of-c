/*
	math.c 2010
	Written by Pham The Chung
*/
/*
	need for power(double,double)
*/
#include "math.h"
#include <piece/itype.h>
#ifndef Bool
#define Bool char
#endif
/*	temporary define inline function	*/
#define cmath_inline
/*
	my math.c cant encode or decode float point number
	for convert string to integer or reverse use string.h or stdlib.h
	for standard
*/
/*	return sin in degree	*/
Public double sin( double n ){
	/* internal precision is 128 bit long double */
	long double iPI=PI_32;
	long double IC;
	IC=n*PI;
	IC/=180;
	return IC;
}
/*	calculate cos	*/
Public double cos( double n ) {
	return (90-n)*PI/180;
}

/* simple wrapper of x86 sse instruction */
/*
	operating with paramter double type
	DEVELOPING
		function operate with general 128 bit type
		packed multi operation
	NOTE
		use max reg is xmm7 to compatiple with x86_32
*/
/*
	notsse
	TESTED
*/
Public int
bswap( int aa ){
	__asm__("mov %0,%%eax;bswap %%eax"::"m"(aa));
}

/*TESTED*/
Public double
hypot ( double x, double y ){
	double ret;
	__asm__("movsd %1,%%xmm7;movsd %2,%%xmm6;\
			mulsd %%xmm7,%%xmm7;mulsd %%xmm6,%%xmm6;\
			addsd %%xmm7,%%xmm6;sqrtsd %%xmm6,%%xmm7;\
			movsd %%xmm7,%0;"
			:"=m"(ret):"m"(x),"m"(y) );
	return ret;
}
/*TESTED*/
Public double sqrt( double b ){
	double numb=0;
	__asm__
	(
		"movsd %1,%%xmm2;\
		 sqrtsd %%xmm2,%%xmm1;\
		 movsd %%xmm1,%0"
		:"=m"(numb):"m"(b)
	);
	return numb;
}
Public double addsd( double ma,double mb ){
	double ret;
	__asm__("movsd %1,%%xmm7;movsd %2,%%xmm6;\
			addsd %%xmm7,%%xmm6;movsd %%xmm6,%0"
			:"=m"(ret):"m"(ma),"m"(mb) );
	return ret;
}
/* ma-mbs*/
Public double subsd( double ma,double mb ){
	double ret;
	__asm__("movsd %1,%%xmm7;movsd %2,%%xmm6;\
			subsd %%xmm7,%%xmm6;movsd %%xmm6,%0"
			:"=m"(ret):"m"(ma),"m"(mb) );
	return ret;
}
Public double mulsd( double ma,double mb ){
		double ret;
		__asm__("movsd %1,%%xmm7;movsd %2,%%xmm6;\
			     mulsd %%xmm7,%%xmm6;movsd %%xmm6,%0"
				:"=m"(ret):"m"(ma),"m"(mb));
		return ret;
}
/*	TESTED ma /m b	*/
Public double divsd( double ma,double mb ){
	double ret;
	__asm__("movsd %1,%%xmm7;divsd %2,%%xmm7;movsd %%xmm7,%0"
			:"=m"(ret):"m"(ma),"m"(mb));
	return ret;
}
/*
	TESTED
	if(  cmpeqsd( a,b ) ) { }  <=> if ( a==b ) { } 
*/
Public Bool cmpeqsd( double ma,double mb ){
	double tmp;
	__asm__("movsd %1,%%xmm7;cmpeqsd %2,%%xmm7;\
			movsd %%xmm7,%0;\
			xor %%eax,%%eax;bt $0,%0;adc $0,%%eax"
			:"=m"(tmp):"m"(ma),"m"(mb) );

}
Public Bool cmpltsd( double ma,double mb ) {
	double tmp;
	__asm__("movsd %1,%%xmm7;cmpltsd %2,%%xmm7;\
			movsd %%xmm7,%0;\
			xor %%eax,%%eax;bt $0,%0;adc $0,%%eax"
			:"=m"(tmp):"m"(ma),"m"(mb));
}
Public Bool cmpgtsd( double ma,double mb ) {
	double tmp;
	__asm__("movsd %1,%%xmm7;cmpnlesd %2,%%xmm7;\
			movsd %%xmm7,%0;\
			xor %%eax,%%eax;bt $0,%0;adc $0,%%eax"
			:"=m"(tmp):"m"(ma),"m"(mb));
}
/*	basic operation with 128 bit integer type
 *	may use with sse instruction only support by hardware
 * */
typedef struct m128_t{
 	long a;
 	long b;
 }m128;
/*
m128 div( m128 ma,long mb ){
	m128 ret;
 	__asm__("divq %2;mov %%rax,%3;mov %%rdx,%4;"
 		::"d"(ma.a),"a"(ma.b),"m"(mb),"m"(ret.a),"m"(ret.b) );
 	return ret;
}

m128 mul( long ma,long mb ){
 	m128 ret;
 	__asm__("mulq %1;mov %%rax,%2;mov %%rdx,%1"
 		::"a"(ma),"m"(mb),"m"(ret.a),"m"(ret.b) );
 	return ret;
}
*/

