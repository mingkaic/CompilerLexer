	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	retq
	.cfi_endproc

.zerofill __DATA,__bss,_a,4,2           ## @a
.zerofill __DATA,__bss,_b,4,2           ## @b
.zerofill __DATA,__bss,_c,4,2           ## @c

.subsections_via_symbols
