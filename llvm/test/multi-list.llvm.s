	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	retq
	.cfi_endproc

	.globl	_a                      ## @a
.zerofill __DATA,__common,_a,400,4
	.globl	_b                      ## @b
.zerofill __DATA,__common,_b,400,4
	.globl	_c                      ## @c
.zerofill __DATA,__common,_c,400,4

.subsections_via_symbols
