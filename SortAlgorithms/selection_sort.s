	.file	"selection_sort.c"
	.text
	.p2align 4
	.def	printf;	.scl	3;	.type	32;	.endef
	.seh_proc	printf
printf:
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$56, %rsp
	.seh_stackalloc	56
	.seh_endprologue
	leaq	88(%rsp), %rsi
	movq	%rdx, 88(%rsp)
	movq	%rcx, %rbx
	movl	$1, %ecx
	movq	%r8, 96(%rsp)
	movq	%r9, 104(%rsp)
	movq	%rsi, 40(%rsp)
	call	*__imp___acrt_iob_func(%rip)
	movq	%rsi, %r8
	movq	%rbx, %rdx
	movq	%rax, %rcx
	call	__mingw_vfprintf
	addq	$56, %rsp
	popq	%rbx
	popq	%rsi
	ret
	.seh_endproc
	.p2align 4
	.globl	selection_sort
	.def	selection_sort;	.scl	2;	.type	32;	.endef
	.seh_proc	selection_sort
selection_sort:
	pushq	%rbx
	.seh_pushreg	%rbx
	.seh_endprologue
	testl	%edx, %edx
	jle	.L3
	movq	%rcx, %r10
	movl	%edx, %ebx
	movl	$1, %r11d
	cmpl	$1, %edx
	je	.L3
	.p2align 4,,10
	.p2align 3
.L7:
	movq	%r11, %rax
	.p2align 4,,10
	.p2align 3
.L9:
	movq	(%rcx,%rax,8), %r9
	movq	(%r10), %r8
	cmpq	%r8, %r9
	jnb	.L8
	movq	%r9, (%r10)
	movq	%r8, (%rcx,%rax,8)
.L8:
	addq	$1, %rax
	cmpl	%eax, %edx
	jg	.L9
	addq	$1, %r11
	addq	$8, %r10
	cmpq	%rbx, %r11
	jne	.L7
.L3:
	popq	%rbx
	ret
	.seh_endproc
	.section .rdata,"dr"
.LC0:
	.ascii "0: %ld, %ld\12\0"
.LC1:
	.ascii "1: %ld, %ld\12\0"
	.text
	.p2align 4
	.globl	selection_sort_reverse
	.def	selection_sort_reverse;	.scl	2;	.type	32;	.endef
	.seh_proc	selection_sort_reverse
selection_sort_reverse:
	pushq	%r14
	.seh_pushreg	%r14
	pushq	%r13
	.seh_pushreg	%r13
	pushq	%r12
	.seh_pushreg	%r12
	pushq	%rbp
	.seh_pushreg	%rbp
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	subq	$32, %rsp
	.seh_stackalloc	32
	.seh_endprologue
	leal	-1(%rdx), %ebp
	movq	%rcx, %rdi
	testl	%ebp, %ebp
	jle	.L15
	movslq	%ebp, %rbp
	leaq	.LC1(%rip), %r14
	leaq	.LC0(%rip), %r13
	leaq	(%rcx,%rbp,8), %rsi
	.p2align 4,,10
	.p2align 3
.L17:
	movl	%ebp, %r12d
	xorl	%ebx, %ebx
	testl	%ebp, %ebp
	jg	.L20
	jmp	.L21
	.p2align 4,,10
	.p2align 3
.L25:
	movq	%r13, %rcx
	call	printf
	movq	(%rdi,%rbx,8), %rdx
	movq	(%rsi), %rax
	movq	%rdx, (%rsi)
	movq	%rax, (%rdi,%rbx,8)
	addq	$1, %rbx
	cmpq	%rbx, %rbp
	je	.L21
.L20:
	movq	(%rdi,%rbx,8), %rdx
	movq	(%rsi), %rcx
	call	lessthan
	movl	%ebx, %r8d
	movl	%r12d, %edx
	testl	%eax, %eax
	jne	.L25
	movq	%r14, %rcx
	addq	$1, %rbx
	call	printf
	cmpq	%rbx, %rbp
	jne	.L20
.L21:
	subq	$1, %rbp
	subq	$8, %rsi
	testl	%ebp, %ebp
	jg	.L17
.L15:
	addq	$32, %rsp
	popq	%rbx
	popq	%rsi
	popq	%rdi
	popq	%rbp
	popq	%r12
	popq	%r13
	popq	%r14
	ret
	.seh_endproc
	.ident	"GCC: (Rev10, Built by MSYS2 project) 12.2.0"
	.def	__mingw_vfprintf;	.scl	2;	.type	32;	.endef
	.def	lessthan;	.scl	2;	.type	32;	.endef
