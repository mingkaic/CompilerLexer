	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$24, %rsp
Ltmp0:
	.cfi_def_cfa_offset 32
	movl	$1, 12(%rsp)
	movl	$1, 16(%rsp)
	movl	12(%rsp), %edi
	andl	$1, %edi
	movl	%edi, 20(%rsp)
	callq	_print_int
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
