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
	movb	$0, (%rsp)
	movb	$0, 1(%rsp)
	movb	$0, 2(%rsp)
	movb	$0, 3(%rsp)
	movl	$0, 4(%rsp)
	movb	$1, 1(%rsp)
	movb	$0, 2(%rsp)
	movb	$1, 3(%rsp)
	movb	1(%rsp), %al
	andb	$1, %al
	movb	%al, (%rsp)
	movl	$0, 4(%rsp)
	xorl	%edi, %edi
	callq	_print_int
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc


.subsections_via_symbols
