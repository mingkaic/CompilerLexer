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
	movl	$0, (%rsp)
	movb	$0, 6(%rsp)
	movb	$0, 7(%rsp)
	movl	$958, (%rsp)            ## imm = 0x3BE
	movl	$-958, (%rsp)           ## imm = 0xFFFFFFFFFFFFFC42
	movb	$1, 6(%rsp)
	movb	$0, 7(%rsp)
	movl	(%rsp), %edi
	negl	%edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
