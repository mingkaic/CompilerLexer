	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$24, %rsp
Ltmp0:
	.cfi_def_cfa_offset 32
	movl	$958, 8(%rsp)           ## imm = 0x3BE
	imull	$-30, 20(%rsp), %eax
	leal	80(%rax), %ecx
	movl	%ecx, 16(%rsp)
	movl	$-80, %ecx
	subl	%eax, %ecx
	movl	%ecx, 20(%rsp)
	movl	$0, 12(%rsp)
	movl	8(%rsp), %edi
	callq	_print_int
	xorl	%eax, %eax
	addq	$24, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
