	.file	"factorial.c"
	.text
	.p2align 4
	.globl	factorial
	.def	factorial;	.scl	2;	.type	32;	.endef
	.seh_proc	factorial
factorial:
	.seh_endprologue
	movl	$1, %eax
	testl	%ecx, %ecx
	je	.L1
	.p2align 4,,10
	.p2align 3
.L2:
	imull	%ecx, %eax
	subl	$1, %ecx
	jne	.L2
.L1:
	ret
	.seh_endproc
	.ident	"GCC: (Rev10, Built by MSYS2 project) 12.2.0"
