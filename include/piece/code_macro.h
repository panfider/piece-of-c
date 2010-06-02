/*
	Written by Pham The Chung
	create 1/4/2010
*/
#ifndef __SYS_MACRO_H
#define __SYS_MACRO_H

#define PROTOSYS(type,name) type __##name##_

#ifndef NULL
	#define NULL (0)
#endif
#ifndef CALL_SYS
	#define CALL_SYS(f,par) __##f##_ par
#endif

#endif

