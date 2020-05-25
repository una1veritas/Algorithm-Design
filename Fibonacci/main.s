	.text
	.p2align 4
	.globl _fibo
_fibo:
LFB4:
	cmpq	$1, %rdi
	jbe	L12
	pushq	%rbp
LCFI0:
	xorl	%ebp, %ebp
	pushq	%rbx
LCFI1:
	movq	%rdi, %rbx
	subq	$8, %rsp
LCFI2:
L2:
	addq	$1, _counter_fibo(%rip)
	leaq	-1(%rbx), %rdi
	subq	$2, %rbx
	call	_fibo
	addq	%rax, %rbp
	cmpq	$1, %rbx
	ja	L2
	leaq	1(%rbp), %rax
	addq	$8, %rsp
LCFI3:
	popq	%rbx
LCFI4:
	popq	%rbp
LCFI5:
	ret
	.p2align 4,,10
	.p2align 3
L12:
LCFI6:
	movl	$1, %eax
	ret
LFE4:
	.p2align 4
	.globl _fibo_loop
_fibo_loop:
LFB5:
	cmpq	$1, %rdi
	movl	$1, %r8d
	jbe	L13
	movl	$2, %eax
	movl	$1, %ecx
	movl	$1, %edx
	movq	_counter_fibo_loop(%rip), %rsi
	leaq	-1(%rsi), %r9
	jmp	L15
	.p2align 4,,10
	.p2align 3
L17:
	movq	%r8, %rdx
L15:
	leaq	(%r9,%rax), %rsi
	addq	$1, %rax
	leaq	(%rdx,%rcx), %r8
	cmpq	%rax, %rdi
	movq	%rdx, %rcx
	jnb	L17
	movq	%rsi, _counter_fibo_loop(%rip)
L13:
	movq	%r8, %rax
	ret
LFE5:
	.cstring
lC0:
	.ascii "input = %llu\12\0"
lC1:
	.ascii "f(%llu) = %llu.\12\0"
	.align 3
lC2:
	.ascii "the function fibo called %llu time, \0"
lC5:
	.ascii "took %g ms.\12\0"
lC6:
	.ascii "f(%llu) by loop = %llu.\12\0"
	.align 3
lC7:
	.ascii "iterations in fibo_loop %llu time, \0"
	.section __TEXT,__text_startup,regular,pure_instructions
	.p2align 4
	.globl _main
_main:
LFB6:
	pushq	%r13
LCFI7:
	pushq	%r12
LCFI8:
	pushq	%rbp
LCFI9:
	pushq	%rbx
LCFI10:
	subq	$8, %rsp
LCFI11:
	movq	8(%rsi), %rdi
	call	_atol
	leaq	lC0(%rip), %rdi
	movq	%rax, %rsi
	movq	%rax, %rbp
	xorl	%eax, %eax
	call	_printf
	call	_clock
	movq	%rbp, %rdi
	movq	%rax, %r12
	call	_fibo
	movq	%rax, %r13
	call	_clock
	movq	%r13, %rdx
	movq	%rbp, %rsi
	leaq	lC1(%rip), %rdi
	movq	%rax, %rbx
	xorl	%eax, %eax
	call	_printf
	movq	_counter_fibo(%rip), %rsi
	xorl	%eax, %eax
	leaq	lC2(%rip), %rdi
	call	_printf
	subq	%r12, %rbx
	js	L19
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rbx, %xmm0
L20:
	divsd	lC3(%rip), %xmm0
	mulsd	lC4(%rip), %xmm0
	movl	$1, %eax
	movl	$1, %r13d
	leaq	lC5(%rip), %rdi
	call	_printf
	call	_clock
	cmpq	$1, %rbp
	movq	%rax, %r12
	jbe	L21
	movl	$2, %eax
	movl	$1, %ecx
	movl	$1, %edx
	movq	_counter_fibo_loop(%rip), %rsi
	leaq	-1(%rsi), %rdi
	jmp	L22
	.p2align 4,,10
	.p2align 3
L26:
	movq	%r13, %rdx
L22:
	leaq	(%rdi,%rax), %rsi
	addq	$1, %rax
	leaq	(%rdx,%rcx), %r13
	cmpq	%rax, %rbp
	movq	%rdx, %rcx
	jnb	L26
	movq	%rsi, _counter_fibo_loop(%rip)
L21:
	call	_clock
	movq	%r13, %rdx
	movq	%rbp, %rsi
	leaq	lC6(%rip), %rdi
	movq	%rax, %rbx
	xorl	%eax, %eax
	call	_printf
	movq	_counter_fibo_loop(%rip), %rsi
	xorl	%eax, %eax
	leaq	lC7(%rip), %rdi
	call	_printf
	subq	%r12, %rbx
	js	L23
	pxor	%xmm0, %xmm0
	cvtsi2sdq	%rbx, %xmm0
L24:
	divsd	lC3(%rip), %xmm0
	mulsd	lC4(%rip), %xmm0
	movl	$1, %eax
	leaq	lC5(%rip), %rdi
	call	_printf
	addq	$8, %rsp
LCFI12:
	xorl	%eax, %eax
	popq	%rbx
LCFI13:
	popq	%rbp
LCFI14:
	popq	%r12
LCFI15:
	popq	%r13
LCFI16:
	ret
L19:
LCFI17:
	movq	%rbx, %rax
	andl	$1, %ebx
	pxor	%xmm0, %xmm0
	shrq	%rax
	orq	%rbx, %rax
	cvtsi2sdq	%rax, %xmm0
	addsd	%xmm0, %xmm0
	jmp	L20
L23:
	movq	%rbx, %rax
	andl	$1, %ebx
	pxor	%xmm0, %xmm0
	shrq	%rax
	orq	%rbx, %rax
	cvtsi2sdq	%rax, %xmm0
	addsd	%xmm0, %xmm0
	jmp	L24
LFE6:
	.globl _counter_fibo_loop
	.zerofill __DATA,__pu_bss3,_counter_fibo_loop,8,3
	.globl _counter_fibo
	.zerofill __DATA,__pu_bss3,_counter_fibo,8,3
	.literal8
	.align 3
lC3:
	.long	0
	.long	1093567616
	.align 3
lC4:
	.long	0
	.long	1083129856
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x1
	.ascii "zR\0"
	.byte	0x1
	.byte	0x78
	.byte	0x10
	.byte	0x1
	.byte	0x10
	.byte	0xc
	.byte	0x7
	.byte	0x8
	.byte	0x90
	.byte	0x1
	.align 3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB4-.
	.set L$set$2,LFE4-LFB4
	.quad L$set$2
	.byte	0
	.byte	0x4
	.set L$set$3,LCFI0-LFB4
	.long L$set$3
	.byte	0xe
	.byte	0x10
	.byte	0x86
	.byte	0x2
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xe
	.byte	0x18
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.set L$set$5,LCFI2-LCFI1
	.long L$set$5
	.byte	0xe
	.byte	0x20
	.byte	0x4
	.set L$set$6,LCFI3-LCFI2
	.long L$set$6
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$7,LCFI4-LCFI3
	.long L$set$7
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$8,LCFI5-LCFI4
	.long L$set$8
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$9,LCFI6-LCFI5
	.long L$set$9
	.byte	0xc3
	.byte	0xc6
	.align 3
LEFDE1:
LSFDE3:
	.set L$set$10,LEFDE3-LASFDE3
	.long L$set$10
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB5-.
	.set L$set$11,LFE5-LFB5
	.quad L$set$11
	.byte	0
	.align 3
LEFDE3:
LSFDE5:
	.set L$set$12,LEFDE5-LASFDE5
	.long L$set$12
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB6-.
	.set L$set$13,LFE6-LFB6
	.quad L$set$13
	.byte	0
	.byte	0x4
	.set L$set$14,LCFI7-LFB6
	.long L$set$14
	.byte	0xe
	.byte	0x10
	.byte	0x8d
	.byte	0x2
	.byte	0x4
	.set L$set$15,LCFI8-LCFI7
	.long L$set$15
	.byte	0xe
	.byte	0x18
	.byte	0x8c
	.byte	0x3
	.byte	0x4
	.set L$set$16,LCFI9-LCFI8
	.long L$set$16
	.byte	0xe
	.byte	0x20
	.byte	0x86
	.byte	0x4
	.byte	0x4
	.set L$set$17,LCFI10-LCFI9
	.long L$set$17
	.byte	0xe
	.byte	0x28
	.byte	0x83
	.byte	0x5
	.byte	0x4
	.set L$set$18,LCFI11-LCFI10
	.long L$set$18
	.byte	0xe
	.byte	0x30
	.byte	0x4
	.set L$set$19,LCFI12-LCFI11
	.long L$set$19
	.byte	0xa
	.byte	0xe
	.byte	0x28
	.byte	0x4
	.set L$set$20,LCFI13-LCFI12
	.long L$set$20
	.byte	0xe
	.byte	0x20
	.byte	0x4
	.set L$set$21,LCFI14-LCFI13
	.long L$set$21
	.byte	0xe
	.byte	0x18
	.byte	0x4
	.set L$set$22,LCFI15-LCFI14
	.long L$set$22
	.byte	0xe
	.byte	0x10
	.byte	0x4
	.set L$set$23,LCFI16-LCFI15
	.long L$set$23
	.byte	0xe
	.byte	0x8
	.byte	0x4
	.set L$set$24,LCFI17-LCFI16
	.long L$set$24
	.byte	0xb
	.align 3
LEFDE5:
	.ident	"GCC: (MacPorts gcc9 9.3.0_0) 9.3.0"
	.subsections_via_symbols
