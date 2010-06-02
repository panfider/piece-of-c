/*
 * piece-of-c  20092712
 * Pham The Chung
 *
 * */

//#include "piece/string.h"
#include "piece/itype.h"
#include "piece/piecetype.h"
/*check gcc*/
#define PIECE_compiler "unknown"
#ifdef __GNUC__
	#define PIECE_compiler "gcc"
#endif
#define PIECE_version "0.1"
#define PIECE_date_compile __DATE__
#define PIECE_time_compile __TIME__
#define PIECE_compiler_version (__GNUC__ * 1000 + __GNUC_MINOR__*100 +__GNUC_PATCHLEVEL__)
 
/*	from 100000	*/
#define series 99941
Private char piece_name[]="Piece-of-C library";
Private char piece_author[] = "Pham The Chung";
Private char piece_author1[]= "Pham The Chung library implementation";
Private char *piece_version= PIECE_version;
Public int piece_compiler_version(void){
	return PIECE_compiler_version;	
}

// reserve last line for compiler

