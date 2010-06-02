/*
	Copyright (C) 2010 Pham The Chung
	create 25/5/2010
*/
/*
	diary to write
	sin cos in radian
x
*/
#define PI 3.14159
.text
.globl sinf,sqrtf,rsqrtf,sqrt
/*incomplete*/
sinf:
	push %ebx
	mov $0,%eax
	ret
sqrtf:
	push %ebx
	sqrtss %xmm0,%xmm0
	ret
rsqrtf:
	push %ebx
	rsqrtss %xmm0,%xmm0
	ret
sqrt:
	push %ebx
	sqrtsd %xmm0,%xmm0
	ret
