	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 2
	.globl	_selection_sort                 ; -- Begin function selection_sort
	.p2align	2
_selection_sort:                        ; @selection_sort
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #64
	stp	x29, x30, [sp, #48]             ; 16-byte Folded Spill
	add	x29, sp, #48
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	x1, [x29, #-16]
	str	xzr, [sp, #16]
	b	LBB0_1
LBB0_1:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_4 Depth 2
	ldr	x8, [sp, #16]
	ldur	x9, [x29, #-16]
	subs	x8, x8, x9
	b.ge	LBB0_3
	b	LBB0_2
LBB0_2:
	b	LBB0_11
LBB0_3:                                 ;   in Loop: Header=BB0_1 Depth=1
	ldr	x8, [sp, #16]
	add	x8, x8, #1
	str	x8, [sp, #8]
	b	LBB0_4
LBB0_4:                                 ;   Parent Loop BB0_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x8, [sp, #8]
	ldur	x9, [x29, #-16]
	subs	x8, x8, x9
	b.ge	LBB0_6
	b	LBB0_5
LBB0_5:                                 ;   in Loop: Header=BB0_1 Depth=1
	b	LBB0_10
LBB0_6:                                 ;   in Loop: Header=BB0_4 Depth=2
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #8]
	ldr	x0, [x8, x9, lsl #3]
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #16]
	ldr	x1, [x8, x9, lsl #3]
	bl	_lessthan
	cbnz	w0, LBB0_8
	b	LBB0_7
LBB0_7:                                 ;   in Loop: Header=BB0_4 Depth=2
	b	LBB0_9
LBB0_8:                                 ;   in Loop: Header=BB0_4 Depth=2
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #16]
	ldr	x8, [x8, x9, lsl #3]
	str	x8, [sp, #24]
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #8]
	ldr	x8, [x8, x9, lsl #3]
	ldur	x9, [x29, #-8]
	ldr	x10, [sp, #16]
	str	x8, [x9, x10, lsl #3]
	ldr	x8, [sp, #24]
	ldur	x9, [x29, #-8]
	ldr	x10, [sp, #8]
	str	x8, [x9, x10, lsl #3]
	b	LBB0_9
LBB0_9:                                 ;   in Loop: Header=BB0_4 Depth=2
	ldr	x8, [sp, #8]
	add	x8, x8, #1
	str	x8, [sp, #8]
	b	LBB0_4
LBB0_10:                                ;   in Loop: Header=BB0_1 Depth=1
	ldr	x8, [sp, #16]
	add	x8, x8, #1
	str	x8, [sp, #16]
	b	LBB0_1
LBB0_11:
	ldp	x29, x30, [sp, #48]             ; 16-byte Folded Reload
	add	sp, sp, #64
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_selection_sort_reverse         ; -- Begin function selection_sort_reverse
	.p2align	2
_selection_sort_reverse:                ; @selection_sort_reverse
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #80
	stp	x29, x30, [sp, #64]             ; 16-byte Folded Spill
	add	x29, sp, #64
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	x1, [x29, #-16]
	ldur	x8, [x29, #-16]
	subs	x8, x8, #1
	str	x8, [sp, #32]
	b	LBB1_1
LBB1_1:                                 ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB1_3 Depth 2
	ldr	x8, [sp, #32]
	subs	x8, x8, #0
	b.le	LBB1_11
	b	LBB1_2
LBB1_2:                                 ;   in Loop: Header=BB1_1 Depth=1
	str	xzr, [sp, #24]
	b	LBB1_3
LBB1_3:                                 ;   Parent Loop BB1_1 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x8, [sp, #24]
	ldr	x9, [sp, #32]
	subs	x8, x8, x9
	b.ge	LBB1_9
	b	LBB1_4
LBB1_4:                                 ;   in Loop: Header=BB1_3 Depth=2
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #32]
	ldr	x0, [x8, x9, lsl #3]
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #24]
	ldr	x1, [x8, x9, lsl #3]
	bl	_lessthan
	cbz	w0, LBB1_6
	b	LBB1_5
LBB1_5:                                 ;   in Loop: Header=BB1_3 Depth=2
	ldr	x10, [sp, #32]
	ldr	x8, [sp, #24]
	mov	x9, sp
	str	x10, [x9]
	str	x8, [x9, #8]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #32]
	ldr	x8, [x8, x9, lsl #3]
	stur	x8, [x29, #-24]
	ldur	x8, [x29, #-8]
	ldr	x9, [sp, #24]
	ldr	x8, [x8, x9, lsl #3]
	ldur	x9, [x29, #-8]
	ldr	x10, [sp, #32]
	str	x8, [x9, x10, lsl #3]
	ldur	x8, [x29, #-24]
	ldur	x9, [x29, #-8]
	ldr	x10, [sp, #24]
	str	x8, [x9, x10, lsl #3]
	b	LBB1_7
LBB1_6:                                 ;   in Loop: Header=BB1_3 Depth=2
	ldr	x10, [sp, #32]
	ldr	x8, [sp, #24]
	mov	x9, sp
	str	x10, [x9]
	str	x8, [x9, #8]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	bl	_printf
	b	LBB1_7
LBB1_7:                                 ;   in Loop: Header=BB1_3 Depth=2
	b	LBB1_8
LBB1_8:                                 ;   in Loop: Header=BB1_3 Depth=2
	ldr	x8, [sp, #24]
	add	x8, x8, #1
	str	x8, [sp, #24]
	b	LBB1_3
LBB1_9:                                 ;   in Loop: Header=BB1_1 Depth=1
	b	LBB1_10
LBB1_10:                                ;   in Loop: Header=BB1_1 Depth=1
	ldr	x8, [sp, #32]
	subs	x8, x8, #1
	str	x8, [sp, #32]
	b	LBB1_1
LBB1_11:
	ldp	x29, x30, [sp, #64]             ; 16-byte Folded Reload
	add	sp, sp, #80
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"0: %ld, %ld\n"

l_.str.1:                               ; @.str.1
	.asciz	"1: %ld, %ld\n"

.subsections_via_symbols
