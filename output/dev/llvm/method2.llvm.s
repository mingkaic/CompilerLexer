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
	movl	$1, 4(%rsp)
	movl	$1, %edi
	callq	_print_int
	movl	4(%rsp), %edi
	leal	1(%rdi), %esi
	callq	_test
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc

	.globl	_test
	.align	4, 0x90
_test:                                  ## @test
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$24, %rsp
Ltmp1:
	.cfi_def_cfa_offset 32
	movl	%edi, 12(%rsp)
	movl	%esi, 16(%rsp)
	movl	$1, 20(%rsp)
	movl	12(%rsp), %edi
	callq	_print_int
	movl	16(%rsp), %edi
	callq	_print_int
	movl	20(%rsp), %edi
	callq	_print_int
	addq	$24, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
