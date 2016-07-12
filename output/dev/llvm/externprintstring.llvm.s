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
	movl	$1, 68(%rsp)
	movl	$34, 8(%rsp)
	movl	$104, 8(%rsp)
	movl	$101, 8(%rsp)
	movl	$108, 8(%rsp)
	movl	$111, 8(%rsp)
	movl	$32, 8(%rsp)
	movl	$119, 8(%rsp)
	movl	$111, 8(%rsp)
	movl	$114, 8(%rsp)
	movl	$108, 8(%rsp)
	movl	$100, 8(%rsp)
	movl	$92, 8(%rsp)
	movl	$110, 8(%rsp)
	movl	$34, 8(%rsp)
	leaq	8(%rsp), %rdi
	callq	_print_string
	xorl	%eax, %eax
	addq	$72, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
