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
	movl	$1, (%rsp)
	movl	$100, 4(%rsp)
	movl	(%rsp), %edi
	callq	_print_int
	movl	4(%rsp), %edi
	callq	_print_int
	movl	$2, 8(%rsp)
	movl	$2, %edi
	callq	_print_int
	movl	4(%rsp), %edi
	callq	_print_int
	movl	$3, 12(%rsp)
	movl	$3, %edi
	callq	_print_int
	movl	4(%rsp), %edi
	callq	_print_int
	movl	$4, 16(%rsp)
	movl	$4, %edi
	callq	_print_int
	movl	4(%rsp), %edi
	callq	_print_int
	movl	$5, 20(%rsp)
	movl	$5, %edi
	callq	_print_int
	movl	4(%rsp), %edi
	callq	_print_int
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
