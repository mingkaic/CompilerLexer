	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$72, %rsp
Ltmp0:
	.cfi_def_cfa_offset 80
	movl	$34, 40(%rsp)
	movl	$104, 40(%rsp)
	movl	$101, 40(%rsp)
	movl	$108, 40(%rsp)
	movl	$111, 40(%rsp)
	movl	$44, 40(%rsp)
	movl	$34, 40(%rsp)
	leaq	40(%rsp), %rdi
	callq	_print_string
	movl	$34, (%rsp)
	movl	$32, (%rsp)
	movl	$119, (%rsp)
	movl	$111, (%rsp)
	movl	$114, (%rsp)
	movl	$108, (%rsp)
	movl	$100, (%rsp)
	movl	$92, (%rsp)
	movl	$110, (%rsp)
	movl	$34, (%rsp)
	leaq	(%rsp), %rdi
	callq	_print_string
	xorl	%eax, %eax
	addq	$72, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
