	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_gcd
	.align	4, 0x90
_gcd:                                   ## @gcd
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	testl	%esi, %esi
	je	LBB0_1
## BB#2:                                ## %else
	movl	4(%rsp), %edi
	movl	(%rsp), %eax
	cltd
	idivl	%edi
	movl	%edx, %esi
	callq	_gcd
	popq	%rcx
	retq
LBB0_1:                                 ## %then
	movl	(%rsp), %eax
	popq	%rcx
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$24, %rsp
Ltmp1:
	.cfi_def_cfa_offset 32
	movl	$0, 12(%rsp)
	movl	$0, 16(%rsp)
	movl	$0, 20(%rsp)
	movl	_a(%rip), %eax
	movl	%eax, 12(%rsp)
	movl	_b(%rip), %esi
	movl	%esi, 16(%rsp)
	movl	12(%rsp), %edi
	callq	_gcd
	movl	%eax, 20(%rsp)
	movl	%eax, %edi
	callq	_print_int
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
	.cfi_endproc

	.section	__DATA,__data
	.align	2                       ## @a
_a:
	.long	10                      ## 0xa

	.align	2                       ## @b
_b:
	.long	20                      ## 0x14


.subsections_via_symbols
