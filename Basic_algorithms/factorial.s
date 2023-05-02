	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 12, 0	sdk_version 13, 1
	.globl	_factorial                      ## -- Begin function factorial
	.p2align	4, 0x90
_factorial:                             ## @factorial
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	testq	%rdi, %rdi
	je	LBB0_1
## %bb.2:
	leaq	-1(%rdi), %rax
	movl	%edi, %r9d
	andl	$7, %r9d
	cmpq	$7, %rax
	jae	LBB0_4
## %bb.3:
	movl	$1, %eax
	testq	%r9, %r9
	jne	LBB0_8
	jmp	LBB0_9
LBB0_1:
	movl	$1, %eax
	popq	%rbp
	retq
LBB0_4:
	movq	%rdi, %r8
	andq	$-8, %r8
	negq	%r8
	movl	$1, %eax
	xorl	%esi, %esi
	.p2align	4, 0x90
LBB0_5:                                 ## =>This Inner Loop Header: Depth=1
	leaq	(%rdi,%rsi), %rdx
	imulq	%rax, %rdx
	leaq	(%rdi,%rsi), %rax
	addq	$-1, %rax
	leaq	(%rdi,%rsi), %rcx
	addq	$-2, %rcx
	imulq	%rax, %rcx
	imulq	%rdx, %rcx
	leaq	(%rdi,%rsi), %rdx
	addq	$-3, %rdx
	leaq	(%rdi,%rsi), %rax
	addq	$-4, %rax
	imulq	%rdx, %rax
	leaq	(%rdi,%rsi), %rdx
	addq	$-5, %rdx
	imulq	%rax, %rdx
	imulq	%rcx, %rdx
	leaq	(%rdi,%rsi), %rcx
	addq	$-6, %rcx
	leaq	(%rdi,%rsi), %rax
	addq	$-7, %rax
	imulq	%rcx, %rax
	imulq	%rdx, %rax
	addq	$-8, %rsi
	cmpq	%rsi, %r8
	jne	LBB0_5
## %bb.6:
	addq	%rsi, %rdi
	testq	%r9, %r9
	je	LBB0_9
	.p2align	4, 0x90
LBB0_8:                                 ## =>This Inner Loop Header: Depth=1
	imulq	%rdi, %rax
	addq	$-1, %rdi
	addq	$-1, %r9
	jne	LBB0_8
LBB0_9:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_factorial_tailrecursive        ## -- Begin function factorial_tailrecursive
	.p2align	4, 0x90
_factorial_tailrecursive:               ## @factorial_tailrecursive
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rsi, %rax
	testq	%rdi, %rdi
	je	LBB1_6
## %bb.1:
	leaq	-1(%rdi), %rcx
	movq	%rdi, %rdx
	andq	$7, %rdx
	je	LBB1_3
	.p2align	4, 0x90
LBB1_2:                                 ## =>This Inner Loop Header: Depth=1
	imulq	%rdi, %rax
	addq	$-1, %rdi
	addq	$-1, %rdx
	jne	LBB1_2
LBB1_3:
	cmpq	$7, %rcx
	jb	LBB1_6
## %bb.4:
	addq	$-7, %rdi
	.p2align	4, 0x90
LBB1_5:                                 ## =>This Inner Loop Header: Depth=1
	leaq	7(%rdi), %rcx
	imulq	%rax, %rcx
	leaq	6(%rdi), %rax
	leaq	5(%rdi), %rdx
	imulq	%rdx, %rax
	imulq	%rcx, %rax
	leaq	4(%rdi), %rcx
	leaq	3(%rdi), %rdx
	imulq	%rdx, %rcx
	leaq	2(%rdi), %rdx
	imulq	%rcx, %rdx
	imulq	%rax, %rdx
	leaq	1(%rdi), %rax
	imulq	%rdi, %rax
	imulq	%rdx, %rax
	addq	$-8, %rdi
	cmpq	$-7, %rdi
	jne	LBB1_5
LBB1_6:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
.subsections_via_symbols
