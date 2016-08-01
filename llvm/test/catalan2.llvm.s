	.section	__TEXT,__text,regular,pure_instructions
	.macosx_version_min 10, 11
	.globl	_cat
	.align	4, 0x90
_cat:                                   ## @cat
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp0:
	.cfi_def_cfa_offset 16
	movl	%edi, %eax
	movl	%eax, 4(%rsp)
	leal	(%rax,%rax), %edi
	movl	%eax, %esi
	callq	_choose
	movl	4(%rsp), %ecx
	incl	%ecx
	cltd
	idivl	%ecx
	popq	%rcx
	retq
	.cfi_endproc

	.globl	_choose
	.align	4, 0x90
_choose:                                ## @choose
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rbp
Ltmp1:
	.cfi_def_cfa_offset 16
	pushq	%rbx
Ltmp2:
	.cfi_def_cfa_offset 24
	pushq	%rax
Ltmp3:
	.cfi_def_cfa_offset 32
Ltmp4:
	.cfi_offset %rbx, -24
Ltmp5:
	.cfi_offset %rbp, -16
	movl	%edi, (%rsp)
	movl	%esi, 4(%rsp)
	movl	(%rsp), %edi
	callq	_fact
	movl	%eax, %ebx
	movl	4(%rsp), %edi
	callq	_fact
	movl	%eax, %ebp
	movl	(%rsp), %edi
	subl	4(%rsp), %edi
	callq	_fact
	movl	%eax, %ecx
	imull	%ebp, %ecx
	movl	%ebx, %eax
	cltd
	idivl	%ecx
	addq	$8, %rsp
	popq	%rbx
	popq	%rbp
	retq
	.cfi_endproc

	.globl	_fact
	.align	4, 0x90
_fact:                                  ## @fact
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rbx
Ltmp6:
	.cfi_def_cfa_offset 16
	subq	$16, %rsp
Ltmp7:
	.cfi_def_cfa_offset 32
Ltmp8:
	.cfi_offset %rbx, -16
	movl	%edi, 12(%rsp)
	movl	$1, %eax
	cmpl	$1, %edi
	je	LBB2_2
## BB#1:                                ## %else
	movl	12(%rsp), %ebx
	leal	-1(%rbx), %edi
	callq	_fact
	imull	%ebx, %eax
LBB2_2:                                 ## %ifcont
	addq	$16, %rsp
	popq	%rbx
	retq
	.cfi_endproc

	.globl	_main
	.align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## BB#0:                                ## %entry
	pushq	%rax
Ltmp9:
	.cfi_def_cfa_offset 16
	movl	$1430, %edi             ## imm = 0x596
	callq	_print_int
	popq	%rax
	retq
	.cfi_endproc


.subsections_via_symbols
