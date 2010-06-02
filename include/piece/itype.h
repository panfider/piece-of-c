/*
	itype.h
	Designed by Pham The Chung
	LASTDATE May 30 2010 Sun
*/
/*	define class specifier	*/
#ifndef ITYPE_H
#define ITYPE_H
#define itype_series 2
#define itype_release 1
#define INLINE __inline__
#define Public
/*
	static to make var for function private in a object file
	static is dont link
*/
#define Private static
/*
	when Link it really link to object has in shared object file
*/
#define Link extern
/*	dont with (inline function in share lib)
	can use with no fun qualifier or extern
*/
#define YES 			(1)
#define NO 			(0)
#define ERROR 			(-1)
#define TRUE 			(1)
#define FALSE 			(0)
typedef long 			Long;
typedef int 			Int;
typedef short 			Short;
typedef char 			Char;
typedef unsigned char 		uChar;
typedef unsigned short 		uShort;
typedef unsigned int 		uInt;
typedef unsigned long 		uLong;
typedef void 			*Addr;
typedef float 			Float;
typedef double 			Double;
typedef long double 		LDouble;
typedef double 			FP;
typedef void 			NoThing;
typedef Addr (*FunPtr)(Addr);
/*
	Division type
*/
typedef struct Div_obj{
	uChar *name;
	Long val;
	Short state;
	struct Div_obj *self;
	FunPtr act; /* void *act(void*)*/
	Long size;
	Addr data;
}Div;
typedef Div *DivPtr;

typedef struct FrameObject{
	uInt head;
	Char *data[0];
}Frame;

#endif
/*I reserve line below*/
