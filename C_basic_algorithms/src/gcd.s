	.arch armv8-a
	.text
	.globl _counter
	.zerofill __DATA,__common,_counter,8,3
	.text
	.align	2
	.globl _gcd_euclidean_do
_gcd_euclidean_do:
LFB1:
	sub	sp, sp, #32
LCFI0:
	str	x0, [sp, 8]
	str	x1, [sp]
L2:
	ldr	x0, [sp, 8]
	ldr	x1, [sp]
	udiv	x2, x0, x1
	ldr	x1, [sp]
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 24]
	ldr	x0, [sp]
	str	x0, [sp, 8]
	ldr	x0, [sp, 24]
	str	x0, [sp]
	ldr	x0, [sp]
	cmp	x0, 0
	bne	L2
	ldr	x0, [sp, 8]
	add	sp, sp, 32
LCFI1:
	ret
LFE1:
	.align	2
	.globl _gcd_euclidean
_gcd_euclidean:
LFB2:
	sub	sp, sp, #32
LCFI2:
	str	x0, [sp, 8]
	str	x1, [sp]
	b	L5
L6:
	ldr	x0, [sp, 8]
	ldr	x1, [sp]
	udiv	x2, x0, x1
	ldr	x1, [sp]
	mul	x1, x2, x1
	sub	x0, x0, x1
	str	x0, [sp, 24]
	ldr	x0, [sp]
	str	x0, [sp, 8]
	ldr	x0, [sp, 24]
	str	x0, [sp]
L5:
	ldr	x0, [sp]
	cmp	x0, 0
	bne	L6
	ldr	x0, [sp, 8]
	add	sp, sp, 32
LCFI3:
	ret
LFE2:
	.align	2
	.globl _gcd_naive
_gcd_naive:
LFB3:
	sub	sp, sp, #32
LCFI4:
	str	x0, [sp, 8]
	str	x1, [sp]
	ldr	x0, [sp, 8]
	str	x0, [sp, 24]
	ldr	x1, [sp]
	ldr	x0, [sp, 8]
	cmp	x1, x0
	bcs	L10
	ldr	x0, [sp]
	str	x0, [sp, 24]
	b	L10
L13:
	ldr	x0, [sp, 8]
	ldr	x1, [sp, 24]
	udiv	x2, x0, x1
	ldr	x1, [sp, 24]
	mul	x1, x2, x1
	sub	x0, x0, x1
	cmp	x0, 0
	bne	L11
	ldr	x0, [sp]
	ldr	x1, [sp, 24]
	udiv	x2, x0, x1
	ldr	x1, [sp, 24]
	mul	x1, x2, x1
	sub	x0, x0, x1
	cmp	x0, 0
	beq	L15
L11:
	ldr	x0, [sp, 24]
	sub	x0, x0, #1
	str	x0, [sp, 24]
L10:
	ldr	x0, [sp, 24]
	cmp	x0, 1
	bhi	L13
	b	L12
L15:
	nop
L12:
	ldr	x0, [sp, 24]
	add	sp, sp, 32
LCFI5:
	ret
LFE3:
	.section __TEXT,__eh_frame,coalesced,no_toc+strip_static_syms+live_support
EH_frame1:
	.set L$set$0,LECIE1-LSCIE1
	.long L$set$0
LSCIE1:
	.long	0
	.byte	0x3
	.ascii "zR\0"
	.uleb128 0x1
	.sleb128 -8
	.uleb128 0x1e
	.uleb128 0x1
	.byte	0x10
	.byte	0xc
	.uleb128 0x1f
	.uleb128 0
	.align	3
LECIE1:
LSFDE1:
	.set L$set$1,LEFDE1-LASFDE1
	.long L$set$1
LASFDE1:
	.long	LASFDE1-EH_frame1
	.quad	LFB1-.
	.set L$set$2,LFE1-LFB1
	.quad L$set$2
	.uleb128 0
	.byte	0x4
	.set L$set$3,LCFI0-LFB1
	.long L$set$3
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE1:
LSFDE3:
	.set L$set$5,LEFDE3-LASFDE3
	.long L$set$5
LASFDE3:
	.long	LASFDE3-EH_frame1
	.quad	LFB2-.
	.set L$set$6,LFE2-LFB2
	.quad L$set$6
	.uleb128 0
	.byte	0x4
	.set L$set$7,LCFI2-LFB2
	.long L$set$7
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.set L$set$8,LCFI3-LCFI2
	.long L$set$8
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE3:
LSFDE5:
	.set L$set$9,LEFDE5-LASFDE5
	.long L$set$9
LASFDE5:
	.long	LASFDE5-EH_frame1
	.quad	LFB3-.
	.set L$set$10,LFE3-LFB3
	.quad L$set$10
	.uleb128 0
	.byte	0x4
	.set L$set$11,LCFI4-LFB3
	.long L$set$11
	.byte	0xe
	.uleb128 0x20
	.byte	0x4
	.set L$set$12,LCFI5-LCFI4
	.long L$set$12
	.byte	0xe
	.uleb128 0
	.align	3
LEFDE5:
	.ident	"GCC: (Homebrew GCC 13.1.0) 13.1.0"
	.subsections_via_symbols
