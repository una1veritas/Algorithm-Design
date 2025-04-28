	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 15, 4
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	stp	x24, x23, [sp, #-64]!           ; 16-byte Folded Spill
	stp	x22, x21, [sp, #16]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #32]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	sub	sp, sp, #16
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	mov	x19, x1
                                        ; kill: def $w0 killed $w0 def $x0
Lloh0:
	adrp	x8, ___stack_chk_guard@GOTPAGE
Lloh1:
	ldr	x8, [x8, ___stack_chk_guard@GOTPAGEOFF]
Lloh2:
	ldr	x8, [x8]
	stur	x8, [x29, #-56]
	sub	w8, w0, #1
	ubfiz	x9, x8, #3, #32
	add	x8, x9, #15
	and	x8, x8, #0xffffffff0
Lloh3:
	adrp	x16, ___chkstk_darwin@GOTPAGE
Lloh4:
	ldr	x16, [x16, ___chkstk_darwin@GOTPAGEOFF]
	blr	x16
	mov	x9, sp
	sub	x20, x9, x8
	mov	sp, x20
	cmp	w0, #2
	b.lt	LBB0_3
; %bb.1:
	sxtw	x22, w0
	mov	w21, #1                         ; =0x1
	mov	x23, x20
LBB0_2:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x0, [x19, x21, lsl #3]
	bl	_atol
	str	x0, [x23], #8
	add	x21, x21, #1
	cmp	x22, x21
	b.ne	LBB0_2
	b	LBB0_4
LBB0_3:
	mov	w21, #1                         ; =0x1
LBB0_4:
	mov	x23, #0                         ; =0x0
Lloh5:
	adrp	x22, ___stdoutp@GOTPAGE
Lloh6:
	ldr	x22, [x22, ___stdoutp@GOTPAGEOFF]
Lloh7:
	adrp	x19, l_.str@PAGE
Lloh8:
	add	x19, x19, l_.str@PAGEOFF
LBB0_5:                                 ; =>This Inner Loop Header: Depth=1
	ldr	x0, [x22]
	ldr	x8, [x20, x23, lsl #3]
	str	x8, [sp, #-16]!
	mov	x1, x19
	bl	_fprintf
	add	sp, sp, #16
	add	x23, x23, #1
	cmp	x21, x23
	b.ne	LBB0_5
; %bb.6:
	ldr	x1, [x22]
	mov	w0, #10                         ; =0xa
	bl	_fputc
	mov	x8, #0                          ; =0x0
	sub	x9, x21, #1
	add	x10, x20, x21, lsl #3
	sub	x10, x10, #8
	b	LBB0_8
LBB0_7:                                 ;   in Loop: Header=BB0_8 Depth=1
	add	x8, x8, #1
	cmp	x8, x21
	b.eq	LBB0_12
LBB0_8:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_10 Depth 2
	mov	x11, x10
	mov	x12, x9
	cmp	x9, x8
	b.hi	LBB0_10
	b	LBB0_7
LBB0_9:                                 ;   in Loop: Header=BB0_10 Depth=2
	sub	x12, x12, #1
	sub	x11, x11, #8
	cmp	x12, x8
	b.le	LBB0_7
LBB0_10:                                ;   Parent Loop BB0_8 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldp	x13, x14, [x11, #-8]
	cmp	x13, x14
	b.le	LBB0_9
; %bb.11:                               ;   in Loop: Header=BB0_10 Depth=2
	stp	x14, x13, [x11, #-8]
	b	LBB0_9
LBB0_12:
Lloh9:
	adrp	x19, l_.str@PAGE
Lloh10:
	add	x19, x19, l_.str@PAGEOFF
LBB0_13:                                ; =>This Inner Loop Header: Depth=1
	ldr	x0, [x22]
	ldr	x8, [x20], #8
	str	x8, [sp, #-16]!
	mov	x1, x19
	bl	_fprintf
	add	sp, sp, #16
	subs	x21, x21, #1
	b.ne	LBB0_13
; %bb.14:
	ldr	x1, [x22]
	mov	w0, #10                         ; =0xa
	bl	_fputc
	ldur	x8, [x29, #-56]
Lloh11:
	adrp	x9, ___stack_chk_guard@GOTPAGE
Lloh12:
	ldr	x9, [x9, ___stack_chk_guard@GOTPAGEOFF]
Lloh13:
	ldr	x9, [x9]
	cmp	x9, x8
	b.ne	LBB0_16
; %bb.15:
	mov	w0, #0                          ; =0x0
	sub	sp, x29, #48
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	ldp	x20, x19, [sp, #32]             ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #16]             ; 16-byte Folded Reload
	ldp	x24, x23, [sp], #64             ; 16-byte Folded Reload
	ret
LBB0_16:
	bl	___stack_chk_fail
	.loh AdrpLdrGotLdr	Lloh0, Lloh1, Lloh2
	.loh AdrpAdd	Lloh7, Lloh8
	.loh AdrpLdrGot	Lloh5, Lloh6
	.loh AdrpAdd	Lloh9, Lloh10
	.loh AdrpLdrGotLdr	Lloh11, Lloh12, Lloh13
	.loh AdrpLdrGot	Lloh3, Lloh4
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%ld, "

.subsections_via_symbols
