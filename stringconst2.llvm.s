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
	leaq	L_gstr(%rip), %rdi
	callq	_print_string
	leaq	L_gstr.1(%rip), %rdi
	callq	_print_string
	xorl	%eax, %eax
	popq	%rcx
	retq
	.cfi_endproc

	.section	__TEXT,__cstring,cstring_literals
L_gstr:                                 ## @gstr
	.asciz	"hello,"

L_gstr.1:                               ## @gstr.1
	.asciz	" world\n"


.subsections_via_symbols
