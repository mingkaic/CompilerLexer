	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_initList
	.align	4, 0x90
_initList:                              ## @initList
	.cfi_startproc
## BB#0:                                ## %entry
	movl	%edi, -8(%rsp)
	movl	$0, -4(%rsp)
	retq
	.cfi_endproc


.subsections_via_symbols
