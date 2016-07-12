	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$88, %rsp
Ltmp0:
	.cfi_def_cfa_offset 96
	movl	$34, 56(%rsp)
	movl	$104, 56(%rsp)
	movl	$101, 56(%rsp)
	movl	$108, 56(%rsp)
	movl	$111, 56(%rsp)
	movl	$44, 56(%rsp)
	movl	$34, 56(%rsp)
	leaq	56(%rsp), %rdi
	callq	_print_string
	movl	$34, 24(%rsp)
	movl	$32, 24(%rsp)
	movl	$119, 24(%rsp)
	movl	$111, 24(%rsp)
	movl	$114, 24(%rsp)
	movl	$108, 24(%rsp)
	movl	$100, 24(%rsp)
	movl	$34, 24(%rsp)
	leaq	24(%rsp), %rdi
	callq	_print_string
	movl	$34, 8(%rsp)
	movl	$92, 8(%rsp)
	movl	$110, 8(%rsp)
	movl	$34, 8(%rsp)
	leaq	8(%rsp), %rdi
	callq	_print_string
	xorl	%eax, %eax
	addq	$88, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
