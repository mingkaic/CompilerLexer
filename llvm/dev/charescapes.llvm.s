	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movl	$9, 4(%rsp)
	movl	$9, %edi
	callq	_print_int
	movl	$11, 4(%rsp)
	movl	$11, %edi
	callq	_print_int
	movl	$13, 4(%rsp)
	movl	$13, %edi
	callq	_print_int
	movl	$10, 4(%rsp)
	movl	$10, %edi
	callq	_print_int
	movl	$7, 4(%rsp)
	movl	$7, %edi
	callq	_print_int
	movl	$12, 4(%rsp)
	movl	$12, %edi
	callq	_print_int
	movl	$8, 4(%rsp)
	movl	$8, %edi
	callq	_print_int
	movl	$92, 4(%rsp)
	movl	$92, %edi
	callq	_print_int
	movl	$39, 4(%rsp)
	movl	$39, %edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
