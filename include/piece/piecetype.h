
/* 
*	Written by Pham The Chung
	LASTDATE 7 Jan 2010Sat 30 Jan 2010 08:40:29 PM ICT 
	pham.the.chung0@gmail.com

	header for define macro and type for most code in project
*/

#ifndef __PIECETYPE_H
/*	define this object file	*/
#define __PIECETYPE_H
#define PIECETYPE_SERIES 1
#define PIECETYPE_COMPILE_TIME __TIME__
#define PIECETYPE_COMPILE_DATE __DATE__
/*use for detect arch x86*/
#ifndef __X86_64
	#define __BIT_PER_LONG 64
#else
	#define __BIT_PER_LONG 32
#endif

#ifndef NULL
	#define NULL (0x0)
#endif
#ifndef EOF
	#define EOF (-1)
#endif
/*	for easy understand of linkage	*/
#define PUBLIC

#ifndef PRIVATE
	#define PRIVATE static
#endif

#ifndef LINK
	#define LINK extern
#endif

#ifndef INLINE
	#define INLINE __inline__
#endif

#ifndef PIECE_WORD_NAME
#define PIECE_WORD_NAME
typedef unsigned char 	byte;
typedef signed   char 	sbyte;
typedef unsigned short word;
typedef signed short sword;
typedef unsigned int	dword;
typedef signed int	sdword;
typedef signed long	squadword;
typedef unsigned long quadword;
#endif

typedef char		Bool;
typedef void 		*__v;
typedef __v (*__f)( __v );
typedef long (*FuncPt)( __v );
typedef struct Object_object{
	char *name;
	struct Object_object *self;
	long val;
	__f act;
	int size;
	__v data;
}Object_type;
typedef Object_type *Object;
/*
	using Object type
	Object obj; //this is pointer to Object
*/
/*	operator defination	*/
	#define land  &&
	#define lor   ||
	#define xor   ^
	#define and   &
	#define or    |
	#define shr   >>
	#define shl   <<
	#define add   +
	#define sub   -
	#define mul   *
	#define div   /
	#define mod   %
	#define xore ^=
	#define ande &=
	#define ore |=
	#define shle <<=
	#define shre >>=
	#define adde +=
	#define sube -=
	#define mule *=
	#define dive /=
	#define mode %=
	#define addressof(x) (&(x))
	#define equal =
/*	the obj will change when use 3 macro */
/*	set or unset bit from 0->any base on type */
#define switch_bit(obj,th) (obj ^= equal (1 shl th))
#define unset_bit(obj,th) (obj &= ~(1 shl th))
#define set_bit(obj,th) (obj |= (1 shr th))
/*
	get_bit dont change the object pass to it.
	return 1 or 0 so useful with if statement
	use: bitarr=get_bit(numb,0);
	th range from pos 0->7
*/
#define get_bit(obj,th) (((obj&(1<<th))==(1<<th))?1:0)
#define det(n) (n==1?"directory":(n==2?"file":(n==-1?"not_exist":"undefine")))
#define dete(n) (n==-1?"not_exist":(n==0?"exist":"NoD"))
#endif
// reserve of a new line at EOF


