	.file	"What_language_standard_is_my_compiler_using.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.rodata
	.align 4
	.type	_ZL12numStandards, @object
	.size	_ZL12numStandards, 4
_ZL12numStandards:
	.long	7
	.align 32
	.type	_ZL7stdCode, @object
	.size	_ZL7stdCode, 56
_ZL7stdCode:
	.quad	199711
	.quad	201103
	.quad	201402
	.quad	201703
	.quad	202002
	.quad	202302
	.quad	202612
	.globl	stdName
.LC0:
	.string	"Pre-C++11"
.LC1:
	.string	"C++11"
.LC2:
	.string	"C++14"
.LC3:
	.string	"C++17"
.LC4:
	.string	"C++20"
.LC5:
	.string	"C++23"
.LC6:
	.string	"C++26"
	.section	.data.rel.local,"aw"
	.align 32
	.type	stdName, @object
	.size	stdName, 56
stdName:
	.quad	.LC0
	.quad	.LC1
	.quad	.LC2
	.quad	.LC3
	.quad	.LC4
	.quad	.LC5
	.quad	.LC6
	.text
	.globl	_Z14getCPPStandardv
	.type	_Z14getCPPStandardv, @function
_Z14getCPPStandardv:
.LFB2556:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$202002, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2556:
	.size	_Z14getCPPStandardv, .-_Z14getCPPStandardv
	.section	.rodata
	.align 8
.LC7:
	.string	"Error: Unable to determin your language standard. Sorry.\n"
.LC8:
	.string	"Your compiler is using "
.LC9:
	.string	" (language standard code "
.LC10:
	.string	"L)\n"
	.align 8
.LC11:
	.string	"Your compiler is using a preview / pre-release of "
	.text
	.globl	main
	.type	main, @function
main:
.LFB2557:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	call	_Z14getCPPStandardv
	movq	%rax, -8(%rbp)
	cmpq	$-1, -8(%rbp)
	jne	.L4
	leaq	.LC7(%rip), %rdx
	leaq	_ZSt4cout(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movl	$0, %eax
	jmp	.L5
.L4:
	movl	$0, -12(%rbp)
	jmp	.L6
.L10:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_ZL7stdCode(%rip), %rax
	movq	(%rdx,%rax), %rax
	cmpq	%rax, -8(%rbp)
	jne	.L7
	leaq	.LC8(%rip), %rdx
	leaq	_ZSt4cout(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	stdName(%rip), %rax
	movq	(%rcx,%rax), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	leaq	.LC9(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEl@PLT
	movq	%rax, %rdx
	leaq	.LC10(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L8
.L7:
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rdx
	leaq	_ZL7stdCode(%rip), %rax
	movq	(%rdx,%rax), %rax
	cmpq	%rax, -8(%rbp)
	jge	.L9
	leaq	.LC11(%rip), %rdx
	leaq	_ZSt4cout(%rip), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movl	-12(%rbp), %eax
	cltq
	leaq	0(,%rax,8), %rcx
	leaq	stdName(%rip), %rax
	movq	(%rcx,%rax), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	leaq	.LC9(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	movq	%rax, %rdx
	movq	-8(%rbp), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZNSolsEl@PLT
	movq	%rax, %rdx
	leaq	.LC10(%rip), %rax
	movq	%rax, %rsi
	movq	%rdx, %rdi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc@PLT
	jmp	.L8
.L9:
	addl	$1, -12(%rbp)
.L6:
	cmpl	$6, -12(%rbp)
	jle	.L10
.L8:
	movl	$0, %eax
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2557:
	.size	main, .-main
	.ident	"GCC: (GNU) 16.2.1 20260810"
	.section	.note.GNU-stack,"",@progbits
