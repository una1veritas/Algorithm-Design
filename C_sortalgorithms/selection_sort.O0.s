	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 15, 0	sdk_version 26, 2
	.globl	_selection_sort                 ; -- Begin function selection_sort
	.p2align	2
_selection_sort:                        ; @selection_sort
	.cfi_startproc
; %bb.0:
	stp	x28, x27, [sp, #-96]!           ; 16-byte Folded Spill
	stp	x26, x25, [sp, #16]             ; 16-byte Folded Spill
	stp	x24, x23, [sp, #32]             ; 16-byte Folded Spill
	stp	x22, x21, [sp, #48]             ; 16-byte Folded Spill
	stp	x20, x19, [sp, #64]             ; 16-byte Folded Spill
	stp	x29, x30, [sp, #80]             ; 16-byte Folded Spill
	add	x29, sp, #80
	.cfi_def_cfa w29, 16
	.cfi_offset w30, -8
	.cfi_offset w29, -16
	.cfi_offset w19, -24
	.cfi_offset w20, -32
	.cfi_offset w21, -40
	.cfi_offset w22, -48
	.cfi_offset w23, -56
	.cfi_offset w24, -64
	.cfi_offset w25, -72
	.cfi_offset w26, -80
	.cfi_offset w27, -88
	.cfi_offset w28, -96
	subs	x22, x1, #1
	b.lt	LBB0_8
; %bb.1:
	mov	x19, x2						; x19 = entry address of compfunc
	mov	x20, x1						; n = x1
	mov	x21, x0						; x21 = (data *) d
	mov	x24, #0                     ; i = 0
	add	x23, x0, #8
	b	LBB0_3						; goto LBBO_3
LBB0_2:                                 ;   in Loop: Header=BB0_3 Depth=1
	sub	x22, x22, #1				; x22 = x22 - 1
	add	x23, x23, #8				; x23 = x23 + 8
	mov	x24, x25					; x25 = i
	cmp	x25, x20					; x25 > n ?
	b.eq	LBB0_8					; if i == x20 then goto "exit function"
LBB0_3:                             ; for 文の最後の ++i の実行   ; =>This Loop Header: Depth=1
                                        ;     Child Loop BB0_6 Depth 2
	add	x25, x24, #1				; i = i + 1
	cmp	x25, x20					; i > n ?
	b.ge	LBB0_2					; if i > n then goto LBB0_2
; %bb.4:                                ;   in Loop: Header=BB0_3 Depth=1
	mov	x26, x23					; x26 <- x23
	mov	x27, x22					; x27 <- x22
	b	LBB0_6						; jump to LBB0_6
LBB0_5:                                 ;   in Loop: Header=BB0_6 Depth=2
	add	x26, x26, #8
	subs	x27, x27, #1
	b.eq	LBB0_2
LBB0_6:                                 ;   Parent Loop BB0_3 Depth=1
                                        ; =>  This Inner Loop Header: Depth=2
	ldr	x0, [x26]
	ldr	x1, [x21, x24, lsl #3]
	blr	x19
	cbz	w0, LBB0_5
; %bb.7:                                ;   in Loop: Header=BB0_6 Depth=2
	ldr	x8, [x21, x24, lsl #3]
	ldr	x9, [x26]
	str	x9, [x21, x24, lsl #3]
	str	x8, [x26]
	b	LBB0_5
LBB0_8:								; exit function
	ldp	x29, x30, [sp, #80]         ; スタックに対比した変数値を復帰
	ldp	x20, x19, [sp, #64]         ; 16-byte Folded Reload
	ldp	x22, x21, [sp, #48]         ;
	ldp	x24, x23, [sp, #32]         ;
	ldp	x26, x25, [sp, #16]         ;
	ldp	x28, x27, [sp], #96         ;
	ret								; return
	
	.cfi_endproc
                                    ; -- End function
	.section	__TEXT,__cstring,cstring_literals
l_.str:                                 ; @.str
	.asciz	"0: %ld, %ld\n"

l_.str.1:                               ; @.str.1
	.asciz	"1: %ld, %ld\n"

.subsections_via_symbols
