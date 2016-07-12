	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	subq	$136, %rsp
Ltmp0:
	.cfi_def_cfa_offset 144
	movl	$34, 12(%rsp)
	movl	$49, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$116, 12(%rsp)
	movl	$50, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$118, 12(%rsp)
	movl	$51, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$114, 12(%rsp)
	movl	$52, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$110, 12(%rsp)
	movl	$53, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$97, 12(%rsp)
	movl	$54, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$102, 12(%rsp)
	movl	$55, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$98, 12(%rsp)
	movl	$56, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$57, 12(%rsp)
	movl	$92, 12(%rsp)
	movl	$34, 12(%rsp)
	movl	$49, 12(%rsp)
	movl	$48, 12(%rsp)
	movl	$34, 12(%rsp)
	leaq	12(%rsp), %rdi
	callq	_print_string
	xorl	%eax, %eax
	addq	$136, %rsp
	retq
	.cfi_endproc


.subsections_via_symbols
