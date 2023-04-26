gcd_euclidean:
.LFB30:
	.file 1 "../gcd.c"
	.loc 1 14 78
	pushq	%rbp
	.seh_pushreg	%rbp
.LCFI0:
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
.LCFI1:
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
.L2:
	.loc 1 17 5 discriminator 1
	movq	16(%rbp), %rax
	movl	$0, %edx
	divq	24(%rbp)
	movq	%rdx, -8(%rbp)
	.loc 1 18 5 discriminator 1
	movq	24(%rbp), %rax
	movq	%rax, 16(%rbp)
	.loc 1 19 5 discriminator 1
	movq	-8(%rbp), %rax
	movq	%rax, 24(%rbp)
	.loc 1 21 13 discriminator 1
	cmpq	$0, 24(%rbp)
	jne	.L2
	.loc 1 22 9
	movq	16(%rbp), %rax
	.loc 1 23 1
	addq	$16, %rsp
	popq	%rbp
.LCFI2:
	ret
.LFE30:
	.seh_endproc


	.LFE30:
	.seh_endproc
	.globl	gcd_euclidean_while
	.def	gcd_euclidean_while;	.scl	2;	.type	32;	.endef
	.seh_proc	gcd_euclidean_while
gcd_euclidean_while:
.LFB31:
	.loc 1 25 84
	pushq	%rbp
	.seh_pushreg	%rbp
.LCFI3:
	movq	%rsp, %rbp
	.seh_setframe	%rbp, 0
.LCFI4:
	subq	$16, %rsp
	.seh_stackalloc	16
	.seh_endprologue
	movq	%rcx, 16(%rbp)
	movq	%rdx, 24(%rbp)
	.loc 1 27 8
	jmp	.L5
.L6:
	.loc 1 28 5
	movq	16(%rbp), %rax
	movl	$0, %edx
	divq	24(%rbp)
	movq	%rdx, -8(%rbp)
	.loc 1 29 5
	movq	24(%rbp), %rax
	movq	%rax, 16(%rbp)
	.loc 1 30 5
	movq	-8(%rbp), %rax
	movq	%rax, 24(%rbp)
.L5:
	.loc 1 27 11
	cmpq	$0, 24(%rbp)
	jne	.L6
	.loc 1 32 9
	movq	16(%rbp), %rax
	.loc 1 33 1
	addq	$16, %rsp
	popq	%rbp
.LCFI5:
	ret
.LFE31:
	.seh_endproc
