	.file	"selection_sort.c"
	.text
	.globl	selection_sort
	.def	selection_sort;	.scl	2;	.type	32;	.endef
	.seh_proc	selection_sort
selection_sort:
	pushq	%rdi
	.seh_pushreg	%rdi
	pushq	%rsi
	.seh_pushreg	%rsi
	pushq	%rbx
	.seh_pushreg	%rbx
	.seh_endprologue
	testl	%edx, %edx
	jle	.L1
	leaq	4(%rcx), %r8
	leal	-1(%rdx), %edi
	movl	%edx, %esi
	movslq	%edx, %r11
	movl	$1, %r10d
	leaq	8(%rcx), %rbx
	jmp	.L5
.L3:
	addq	$4, %rax
	cmpq	%r9, %rax
	je	.L8
.L4:
	movl	-4(%r8), %edx
	movl	(%rax), %ecx
	cmpl	%ecx, %edx
	jle	.L3
	movl	%ecx, -4(%r8)
	movl	%edx, (%rax)
	jmp	.L3
.L8:
	leaq	1(%r10), %rax
	addq	$4, %r8
	cmpq	%r11, %r10
	je	.L1
	movq	%rax, %r10
.L5:
	cmpq	%rsi, %r10
	je	.L1
	movl	%edi, %eax
	subl	%r10d, %eax
	leaq	-1(%r10,%rax), %rax
	leaq	(%rbx,%rax,4), %r9
	movq	%r8, %rax
	jmp	.L4
.L1:
	popq	%rbx
	popq	%rsi
	popq	%rdi
	ret
	.seh_endproc
	.globl	selection_sort_reverse
	.def	selection_sort_reverse;	.scl	2;	.type	32;	.endef
	.seh_proc	selection_sort_reverse
selection_sort_reverse:
	.seh_endprologue
	leal	-1(%rdx), %r10d
	testl	%r10d, %r10d
	jle	.L9
	movslq	%r10d, %rax
	leaq	(%rcx,%rax,4), %rdx
	jmp	.L11
.L12:
	addq	$4, %rax
	cmpq	%rdx, %rax
	je	.L14
.L13:
	movl	(%rax), %r9d
	movl	(%rdx), %r8d
	cmpl	%r8d, %r9d
	jle	.L12
	movl	%r9d, (%rdx)
	movl	%r8d, (%rax)
	jmp	.L12
.L14:
	subq	$4, %rdx
	subl	$1, %r10d
	je	.L9
.L11:
	movq	%rcx, %rax
	testl	%r10d, %r10d
	jg	.L13
	jmp	.L14
.L9:
	ret
	.seh_endproc
	.ident	"GCC: (Rev10, Built by MSYS2 project) 12.2.0"
