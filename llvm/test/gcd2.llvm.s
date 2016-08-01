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
	movl	(%rsp), %edi
	callq	_iszero
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc

	.globl	_iszero
	.align	4, 0x90
_iszero:                                ## @iszero
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp1:
	.cfi_def_cfa_offset 16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	testl	%esi, %esi
	je	LBB1_2
## BB#1:                                ## %else
	movl	4(%rsp), %edi
	movl	(%rsp), %eax
	cltd
	idivl	%edi
	movl	%edx, %esi
	callq	_gcd
LBB1_2:                                 ## %ifcont
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp2:
	.cfi_def_cfa_offset 16
	movl	$0, 4(%rsp)
	movl	_a(%rip), %edi
	movl	_b(%rip), %esi
	callq	_gcd
	movl	%eax, %edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
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
