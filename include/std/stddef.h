#ifndef _STDDEF_H
#define _STDDEF_H
#ifndef __need_NULL
#  ifdef __cplusplus
	#define NULL (void*(0))
#  else
	#define NULL (0x0)
#endif
#endif
#ifndef __need_size_t
	#define size_t int
#endif

#undef __need_NULL
#undef __need_size_t

#endif
