	.arch armv8-a
	.text
	.cstring
	.align	3
lC0:
	.ascii "Run with argument(s).\0"
	.align	3
lC1:
	.ascii "Failed to interpret '%s' an argument to an integer.\12\0"
	.align	3
lC2:
	.ascii "inputs: %ld, %ld\12\0"
	.align	3
lC3:
	.ascii "swatch = %.3f sec.\12\0"
	.align	3
lC4:
	.ascii "By naive gcd = %llu\12\0"
	.align	3
lC5:
	.ascii "By Euclidean gcd = %llu\12\0"
	.text
	.align	2
	.globl _main
_main:
LFB29:
	stp	x29, x30, [sp, -96]!
LCFI0:
	mov	x29, sp
LCFI1:
	str	x19, [sp, 16]
	sub	sp, sp, #16
LCFI2:
	str	w0, [x29, 44]
	str	x1, [x29, 32]
	mov	x0, sp
	mov	x19, x0
	ldr	w0, [x29, 44]
	cmp	w0, 1
	bne	L2
	adrp	x0, lC0@PAGE
	add	x0, x0, lC0@PAGEOFF;momd
	bl	_puts
	mov	w0, 1
	b	L3
L2:
	ldr	w0, [x29, 44]
	sub	w0, w0, #1
	str	w0, [x29, 88]
	ldr	w0, [x29, 88]
	sxtw	x1, w0
	sub	x1, x1, #1
	str	x1, [x29, 80]
	sxtw	x1, w0
	mov	x8, x1
	mov	x9, 0
	lsr	x1, x8, 58
	lsl	x5, x9, 6
	orr	x5, x1, x5
	lsl	x4, x8, 6
	sxtw	x1, w0
	mov	x6, x1
	mov	x7, 0
	lsr	x1, x6, 58
	lsl	x3, x7, 6
	orr	x3, x1, x3
	lsl	x2, x6, 6
	sxtw	x0, w0
	lsl	x0, x0, 3
	add	x0, x0, 15
	lsr	x0, x0, 4
	lsl	x0, x0, 4
	sub	sp, sp, x0
	add	x0, sp, 16
	add	x0, x0, 7
	lsr	x0, x0, 3
	lsl	x0, x0, 3
	str	x0, [x29, 72]
	str	wzr, [x29, 92]
	b	L4
L6:
	ldrsw	x0, [x29, 92]
	add	x0, x0, 1
	lsl	x0, x0, 3
	ldr	x1, [x29, 32]
	add	x0, x1, x0
	ldr	x0, [x0]
	add	x1, x29, 48
	mov	w2, 0
	bl	_strtoll
	mov	x2, x0
	ldr	x0, [x29, 72]
	ldrsw	x1, [x29, 92]
	str	x2, [x0, x1, lsl 3]
	bl	___error
	ldr	w0, [x0]
	cmp	w0, 34
	bne	L5
	ldr	x0, [x29, 48]
	str	x0, [sp]
	adrp	x0, lC1@PAGE
	add	x0, x0, lC1@PAGEOFF;momd
	bl	_printf
	mov	w0, 1
	b	L3
L5:
	ldr	w0, [x29, 92]
	add	w0, w0, 1
	str	w0, [x29, 92]
L4:
	ldr	w1, [x29, 92]
	ldr	w0, [x29, 88]
	cmp	w1, w0
	blt	L6
	ldr	x0, [x29, 72]
	ldr	x0, [x0]
	ldr	x1, [x29, 72]
	ldr	x1, [x1, 8]
	str	x1, [sp, 8]
	str	x0, [sp]
	adrp	x0, lC2@PAGE
	add	x0, x0, lC2@PAGEOFF;momd
	bl	_printf
	bl	_clock
	str	x0, [x29, 64]
	ldr	x0, [x29, 72]
	ldr	x0, [x0]
	mov	x2, x0
	ldr	x0, [x29, 72]
	ldr	x0, [x0, 8]
	mov	x1, x0
	mov	x0, x2
	bl	_gcd_naive
	str	x0, [x29, 56]
	bl	_clock
	mov	x1, x0
	ldr	x0, [x29, 64]
	sub	x0, x1, x0
	str	x0, [x29, 64]
	ldr	x0, [x29, 64]
	ucvtf	s0, x0
	mov	w0, 9216
	movk	w0, 0x4974, lsl 16
	fmov	s1, w0
	fdiv	s0, s0, s1
	fcvt	d0, s0
	str	d0, [sp]
	adrp	x0, lC3@PAGE
	add	x0, x0, lC3@PAGEOFF;momd
	bl	_printf
	ldr	x0, [x29, 56]
	str	x0, [sp]
	adrp	x0, lC4@PAGE
	add	x0, x0, lC4@PAGEOFF;momd
	bl	_printf
	bl	_clock
	str	x0, [x29, 64]
	ldr	x0, [x29, 72]
	ldr	x0, [x0]
	mov	x2, x0
	ldr	x0, [x29, 72]
	ldr	x0, [x0, 8]
	mov	x1, x0
	mov	x0, x2
	bl	_gcd_euclidean
	str	x0, [x29, 56]
	bl	_clock
	mov	x1, x0
	ldr	x0, [x29, 64]
	sub	x0, x1, x0
	str	x0, [x29, 64]
	ldr	x0, [x29, 64]
	ucvtf	s0, x0
	mov	w0, 9216
	movk	w0, 0x4974, lsl 16
	fmov	s1, w0
	fdiv	s0, s0, s1
	fcvt	d0, s0
	str	d0, [sp]
	adrp	x0, lC3@PAGE
	add	x0, x0, lC3@PAGEOFF;momd
	bl	_printf
	ldr	x0, [x29, 56]
	str	x0, [sp]
	adrp	x0, lC5@PAGE
	add	x0, x0, lC5@PAGEOFF;momd
	bl	_printf
	mov	w0, 10
	bl	_putchar
	mov	w0, 0
L3:
	mov	sp, x19
	mov	sp, x29
	ldr	x19, [sp, 16]
	ldp	x29, x30, [sp], 96
LCFI3:
	ret
LFE29:
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
	.quad	LFB29-.
	.set L$set$2,LFE29-LFB29
	.quad L$set$2
	.uleb128 0
	.byte	0x4
	.set L$set$3,LCFI0-LFB29
	.long L$set$3
	.byte	0xe
	.uleb128 0x60
	.byte	0x9d
	.uleb128 0xc
	.byte	0x9e
	.uleb128 0xb
	.byte	0x4
	.set L$set$4,LCFI1-LCFI0
	.long L$set$4
	.byte	0xd
	.uleb128 0x1d
	.byte	0x4
	.set L$set$5,LCFI2-LCFI1
	.long L$set$5
	.byte	0x93
	.uleb128 0xa
	.byte	0x4
	.set L$set$6,LCFI3-LCFI2
	.long L$set$6
	.byte	0xde
	.byte	0xdd
	.byte	0xd3
	.byte	0xc
	.uleb128 0x1f
	.uleb128 0
	.align	3
LEFDE1:
	.ident	"GCC: (Homebrew GCC 13.1.0) 13.1.0"
	.subsections_via_symbols
