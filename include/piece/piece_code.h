/*
	Written by Pham The Chung
	create	27/05/2010
*/
#ifndef __PIECE_CODE_H
#define __PIECE_CODE_H

#define PIECE piece
#define STR(X) # X
#define CNAME(C) C

#define PIECE_PRE CNAME(PIECE)
#define CALL_USUAL(f,par) f par
#define PIECE_PROTO(t,f) t  piece##_##f
#define PIECE_IMPLE(t,f) t  piece##_##f
#define PIECE_CALL(f,par)    piece##_##f par

/*make it can easy to call and proto*/
#define _PP(t,f) PIECE_PROTO(t,f)
#define _PI(t,f) PIECE_IMPLE(t,f)
#define _PC(f,p) PIECE_CALL(f,p)

/*
	IMPLEMENT
	CALL
*/
#ifndef IMPLEMENT
 #define IMPLEMENT(t,name) PIECE_IMPLE(t,name)
#endif



#endif

