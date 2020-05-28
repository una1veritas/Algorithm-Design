	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 15	sdk_version 10, 15, 4
	.globl	_selectionSort          ## -- Begin function selectionSort
	.p2align	4, 0x90
_selectionSort:                         ## @selectionSort
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	$0, -32(%rbp)
LBB0_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB0_3 Depth 2
	movq	-32(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jge	LBB0_10
## %bb.2:                               ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -40(%rbp)
LBB0_3:                                 ##   Parent Loop BB0_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movq	-40(%rbp), %rax
	cmpq	-16(%rbp), %rax
	jge	LBB0_8
## %bb.4:                               ##   in Loop: Header=BB0_3 Depth=2
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	-8(%rbp), %rcx
	movq	-40(%rbp), %rdx
	cmpq	(%rcx,%rdx,8), %rax
	jle	LBB0_6
## %bb.5:                               ##   in Loop: Header=BB0_3 Depth=2
	movq	-8(%rbp), %rax
	movq	-32(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	%rax, -24(%rbp)
	movq	-8(%rbp), %rax
	movq	-40(%rbp), %rcx
	movq	(%rax,%rcx,8), %rax
	movq	-8(%rbp), %rcx
	movq	-32(%rbp), %rdx
	movq	%rax, (%rcx,%rdx,8)
	movq	-24(%rbp), %rax
	movq	-8(%rbp), %rcx
	movq	-40(%rbp), %rdx
	movq	%rax, (%rcx,%rdx,8)
LBB0_6:                                 ##   in Loop: Header=BB0_3 Depth=2
	jmp	LBB0_7
LBB0_7:                                 ##   in Loop: Header=BB0_3 Depth=2
	movq	-40(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -40(%rbp)
	jmp	LBB0_3
LBB0_8:                                 ##   in Loop: Header=BB0_1 Depth=1
	jmp	LBB0_9
LBB0_9:                                 ##   in Loop: Header=BB0_1 Depth=1
	movq	-32(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -32(%rbp)
	jmp	LBB0_1
LBB0_10:
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$96, %rsp
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -8(%rbp)
	movl	$0, -12(%rbp)
	movl	%edi, -16(%rbp)
	movq	%rsi, -24(%rbp)
	movl	-16(%rbp), %ecx
	decl	%ecx
	movslq	%ecx, %rax
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rsp, %rdx
	movq	%rdx, -40(%rbp)
	leaq	15(,%rax,8), %rdx
	andq	$-16, %rdx
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	movq	%rdx, %rax
	callq	____chkstk_darwin
	subq	%rax, %rsp
	movq	%rsp, %rax
	movq	-72(%rbp), %rdx         ## 8-byte Reload
	movq	%rdx, -48(%rbp)
	movq	$0, -56(%rbp)
	movq	%rax, -80(%rbp)         ## 8-byte Spill
LBB1_1:                                 ## =>This Inner Loop Header: Depth=1
	movq	-56(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jge	LBB1_4
## %bb.2:                               ##   in Loop: Header=BB1_1 Depth=1
	movq	-24(%rbp), %rax
	movq	-56(%rbp), %rcx
	addq	$1, %rcx
	movq	(%rax,%rcx,8), %rdi
	callq	_atol
	movq	-56(%rbp), %rcx
	movq	-80(%rbp), %rdx         ## 8-byte Reload
	movq	%rax, (%rdx,%rcx,8)
	movq	-56(%rbp), %rax
	movq	(%rdx,%rax,8), %rsi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
## %bb.3:                               ##   in Loop: Header=BB1_1 Depth=1
	movq	-56(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -56(%rbp)
	jmp	LBB1_1
LBB1_4:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-32(%rbp), %rsi
	movq	-80(%rbp), %rdi         ## 8-byte Reload
	movl	%eax, -84(%rbp)         ## 4-byte Spill
	callq	_selectionSort
	movq	$0, -64(%rbp)
LBB1_5:                                 ## =>This Inner Loop Header: Depth=1
	movq	-64(%rbp), %rax
	cmpq	-32(%rbp), %rax
	jge	LBB1_8
## %bb.6:                               ##   in Loop: Header=BB1_5 Depth=1
	movq	-64(%rbp), %rax
	movq	-80(%rbp), %rcx         ## 8-byte Reload
	movq	(%rcx,%rax,8), %rsi
	leaq	L_.str(%rip), %rdi
	movb	$0, %al
	callq	_printf
## %bb.7:                               ##   in Loop: Header=BB1_5 Depth=1
	movq	-64(%rbp), %rax
	addq	$1, %rax
	movq	%rax, -64(%rbp)
	jmp	LBB1_5
LBB1_8:
	leaq	L_.str.1(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movl	$0, -12(%rbp)
	movq	-40(%rbp), %rcx
	movq	%rcx, %rsp
	movl	-12(%rbp), %edx
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-8(%rbp), %rsi
	cmpq	%rsi, %rcx
	movl	%edx, -88(%rbp)         ## 4-byte Spill
	jne	LBB1_10
## %bb.9:
	movl	-88(%rbp), %eax         ## 4-byte Reload
	movq	%rbp, %rsp
	popq	%rbp
	retq
LBB1_10:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"%ld, "

L_.str.1:                               ## @.str.1
	.asciz	"\n\n"


.subsections_via_symbols
