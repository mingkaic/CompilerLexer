	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_quickSort
	.align	4, 0x90
_quickSort:                             ## @quickSort
	.cfi_startproc
## BB#0:                                ## %entry
	movl	%edi, -8(%rsp)
	movl	%esi, -4(%rsp)
	retq
	.cfi_endproc


.subsections_via_symbols
