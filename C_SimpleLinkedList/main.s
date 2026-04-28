	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 2
	.globl	_recursive_print                ; -- Begin function recursive_print
	.p2align	2
_recursive_print:                       ; @recursive_print
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	str	x0, [sp, #16]
	ldr	x8, [sp, #16]
	cbnz	x8, LBB0_2
	b	LBB0_1
LBB0_1:
	stur	wzr, [x29, #-4]
	b	LBB0_3
LBB0_2:
	ldr	x8, [sp, #16]
	ldr	x8, [x8]
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	str	w0, [sp, #12]
	ldr	w8, [sp, #12]
	str	w8, [sp, #8]                    ; 4-byte Folded Spill
	ldr	x8, [sp, #16]
	ldr	x0, [x8, #16]
	bl	_recursive_print
	ldr	w8, [sp, #8]                    ; 4-byte Folded Reload
	add	w8, w8, w0
	stur	w8, [x29, #-4]
	b	LBB0_3
LBB0_3:
	ldur	w0, [x29, #-4]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_print                          ; -- Begin function print
	.p2align	2
_print:                                 ; @print
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #48
	stp	x29, x30, [sp, #32]             ; 16-byte Folded Spill
	add	x29, sp, #32
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	x0, [x29, #-8]
	stur	wzr, [x29, #-12]
	b	LBB1_1
LBB1_1:                                 ; =>This Inner Loop Header: Depth=1
	ldur	x8, [x29, #-8]
	cbz	x8, LBB1_4
	b	LBB1_2
LBB1_2:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldur	x8, [x29, #-8]
	ldr	x8, [x8]
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str@PAGE
	add	x0, x0, l_.str@PAGEOFF
	bl	_printf
	ldur	w8, [x29, #-12]
	add	w8, w8, w0
	stur	w8, [x29, #-12]
	b	LBB1_3
LBB1_3:                                 ;   in Loop: Header=BB1_1 Depth=1
	ldur	x8, [x29, #-8]
	ldr	x8, [x8, #16]
	stur	x8, [x29, #-8]
	b	LBB1_1
LBB1_4:
	ldur	w0, [x29, #-12]
	ldp	x29, x30, [sp, #32]             ; 16-byte Folded Reload
	add	sp, sp, #48
	ret
	.cfi_endproc
                                        ; -- End function
	.globl	_main                           ; -- Begin function main
	.p2align	2
_main:                                  ; @main
	.cfi_startproc
; %bb.0:
	sub	sp, sp, #96
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	add	x29, sp, #80
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	stur	wzr, [x29, #-4]
	stur	w0, [x29, #-8]
	stur	x1, [x29, #-16]
	str	xzr, [sp, #40]
	str	xzr, [sp, #48]
	str	xzr, [sp, #56]
	mov	w8, #1                          ; =0x1
	str	w8, [sp, #36]
	b	LBB2_1
LBB2_1:                                 ; =>This Inner Loop Header: Depth=1
	ldr	w8, [sp, #36]
	ldur	w9, [x29, #-8]
	subs	w8, w8, w9
	b.ge	LBB2_4
	b	LBB2_2
LBB2_2:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldur	x8, [x29, #-16]
	ldrsw	x9, [sp, #36]
	ldr	x1, [x8, x9, lsl #3]
	add	x0, sp, #40
	bl	_LinkedList_append
	b	LBB2_3
LBB2_3:                                 ;   in Loop: Header=BB2_1 Depth=1
	ldr	w8, [sp, #36]
	add	w8, w8, #1
	str	w8, [sp, #36]
	b	LBB2_1
LBB2_4:
	add	x8, sp, #40
	str	x8, [sp, #24]                   ; 8-byte Folded Spill
	ldr	x0, [sp, #40]
	bl	_print
	str	w0, [sp, #32]
	adrp	x0, l_.str.1@PAGE
	add	x0, x0, l_.str.1@PAGEOFF
	str	x0, [sp, #8]                    ; 8-byte Folded Spill
	bl	_printf
	ldr	w8, [sp, #32]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	adrp	x0, l_.str.2@PAGE
	add	x0, x0, l_.str.2@PAGEOFF
	str	x0, [sp, #16]                   ; 8-byte Folded Spill
	bl	_printf
	ldr	x0, [sp, #40]
	bl	_recursive_print
	mov	x8, x0
	ldr	x0, [sp, #8]                    ; 8-byte Folded Reload
	str	w8, [sp, #32]
	bl	_printf
	ldr	x0, [sp, #16]                   ; 8-byte Folded Reload
	ldr	w8, [sp, #32]
                                        ; kill: def $x8 killed $w8
	mov	x9, sp
	str	x8, [x9]
	bl	_printf
	ldr	x0, [sp, #24]                   ; 8-byte Folded Reload
	bl	_LinkedList_free
	mov	w0, #0                          ; =0x0
	ldp	x29, x30, [sp, #80]             ; 16-byte Folded Reload
	add	sp, sp, #96
	ret
	.cfi_endproc
                                        ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"%s, "

l_.str.1:                               ; @.str.1
	.asciz	"\n"

l_.str.2:                               ; @.str.2
	.asciz	"total length = %d\n"

.subsections_via_symbols
