/*
	Copyright (c) 2010 Pham The Chung
	start 25/05/2010
*/
/*
	note x86_64 only
	register parameter order: di si dc
*/

#include "asm.h"
.text
.globl sqrtf,sqrt,rsqrtf, addv4f,subv4f

sqrtf:
	push %rbx
	sqrtss %xmm0,%xmm0
	pop %rbx
	ret
sqrt:
	push %rsp
	mov %rsp,%rbp
	sqrtsd %xmm0,%xmm0
	leave
	ret
rsqrtf:
	push %rbp
	mov %rsp,%rbp
	rsqrtss %xmm0,%xmm0
	leave
	ret
/*
	void  addv4f(v4f *V,v4f *R);
	V is array of two element
	R is return
*/
addps:
	push %rbx
	lea 0x10(%rdi),%rcx
	mov %rdi,%rbx
	movdqu (%rcx),%xmm0
	addps (%rbx),%xmm0
	mov %rsi,%rax
	movdqu %xmm0,(%rax)
	ret

subps:
	push %rbx
	lea 0x10(%rdi),%rcx
	mov %rdi,%rbx
	movdqu (%rcx),%xmm0
	subps (%rbx),%xmm0
	mov %rsi,%rax
	movdqu %xmm0,(%rax)
	ret

