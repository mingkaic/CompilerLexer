	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_test3
	.align	4, 0x90
_test3:                                 ## @test3
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	movl	%esi, %edi
	callq	_print_int
	movl	(%rsp), %edi
	callq	_print_int
	popq	%rax
	retq
	.cfi_endproc

	.globl	_test2
	.align	4, 0x90
_test2:                                 ## @test2
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp1:
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	movl	(%rsp), %edi
	callq	_print_int
	movl	4(%rsp), %edi
	callq	_print_int
	movl	4(%rsp), %edi
	notl	%edi
	movl	(%rsp), %esi
	incl	%esi
	callq	_test3
	popq	%rax
	retq
	.cfi_endproc

	.globl	_test1
	.align	4, 0x90
_test1:                                 ## @test1
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp2:
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	movl	%esi, %edi
	callq	_print_int
	movl	(%rsp), %edi
	callq	_print_int
	movl	4(%rsp), %edi
	incl	%edi
	movl	(%rsp), %esi
	notl	%esi
	callq	_test2
	popq	%rax
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp3:
	.cfi_def_cfa_offset 16
	movl	$1, %edi
	movl	$1, %esi
	callq	_test1
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
