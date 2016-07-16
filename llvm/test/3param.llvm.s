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
	movl	$1, %edx
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
	subq	$24, %rsp
Ltmp1:
	.cfi_def_cfa_offset 32
	movl	%edi, 12(%rsp)
	movl	%esi, 16(%rsp)
	andl	$1, %edx
	movb	%dl, 23(%rsp)
	movl	$1, 12(%rsp)
	movl	$1, 16(%rsp)
	movb	$0, 23(%rsp)
	movl	12(%rsp), %edi
	callq	_print_int
	movl	16(%rsp), %edi
	callq	_print_int
	movzbl	23(%rsp), %edi
	andl	$1, %edi
	callq	_print_int
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
