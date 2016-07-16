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
	movl	$1, %edi
	movl	$2, %esi
	callq	_foo
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc

	.globl	_foo
	.align	4, 0x90
_foo:                                   ## @foo
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp1:
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	movl	$1, (%rsp)
	movl	$1, 4(%rsp)
	movl	(%rsp), %edi
	callq	_print_int
	movl	4(%rsp), %edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
