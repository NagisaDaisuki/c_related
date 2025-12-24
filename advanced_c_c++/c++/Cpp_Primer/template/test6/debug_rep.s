	.file	"debug_rep.cpp"
	.text
#APP
	.globl _ZSt21ios_base_library_initv
#NO_APP
	.section	.text._ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_,comdat
	.weak	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_
	.type	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_, @function
_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_:
.LFB2981:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	movq	%rdi, %rbx
	movq	%rsi, %rdi
	movq	8(%rsi), %rsi
	movsbl	%dl, %r8d
	movl	$1, %ecx
	movl	$0, %edx
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE14_M_replace_auxEmmmc@PLT
	movq	%rax, %rsi
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1EOS4_@PLT
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2981:
	.size	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_, .-_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_
	.section	.text._ZNSt15__new_allocatorIcED2Ev,"axG",@progbits,_ZNSt15__new_allocatorIcED5Ev,comdat
	.align 2
	.weak	_ZNSt15__new_allocatorIcED2Ev
	.type	_ZNSt15__new_allocatorIcED2Ev, @function
_ZNSt15__new_allocatorIcED2Ev:
.LFB2994:
	.cfi_startproc
	ret
	.cfi_endproc
.LFE2994:
	.size	_ZNSt15__new_allocatorIcED2Ev, .-_ZNSt15__new_allocatorIcED2Ev
	.weak	_ZNSt15__new_allocatorIcED1Ev
	.set	_ZNSt15__new_allocatorIcED1Ev,_ZNSt15__new_allocatorIcED2Ev
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag,comdat
	.align 2
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag:
.LFB3022:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$32, %rsp
	.cfi_def_cfa_offset 64
	movq	%rdi, %rbx
	movq	%rsi, %r12
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	subq	%rsi, %rdx
	movq	%rdx, %rbp
	movq	%rdx, 8(%rsp)
	cmpq	$15, %rdx
	ja	.L8
.L5:
	movq	%rbx, 16(%rsp)
	movq	(%rbx), %rdi
	movq	%rbp, %rdx
	movq	%r12, %rsi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7_S_copyEPcPKcm@PLT
	movq	$0, 16(%rsp)
	movq	8(%rsp), %rax
	movq	%rax, 8(%rbx)
	addq	(%rbx), %rax
	movb	$0, (%rax)
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L9
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	leaq	8(%rsp), %rsi
	movl	$0, %edx
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm@PLT
	movq	%rax, (%rbx)
	movq	8(%rsp), %rax
	movq	%rax, 16(%rbx)
	jmp	.L5
.L9:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3022:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag
	.section	.rodata._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"basic_string: construction from null is not valid"
	.section	.text._ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_,"axG",@progbits,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC5IS3_EEPKcRKS3_,comdat
	.align 2
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_
	.type	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_, @function
_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_:
.LFB2983:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	leaq	16(%rdi), %rax
	movq	%rax, (%rdi)
	testq	%rsi, %rsi
	je	.L13
	movq	%rdi, %rbp
	movq	%rsi, %rbx
	movq	%rsi, %rdi
	call	strlen@PLT
	leaq	(%rbx,%rax), %rdx
	movq	%rbx, %rsi
	movq	%rbp, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_M_constructIPKcEEvT_S8_St20forward_iterator_tag
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L13:
	.cfi_restore_state
	leaq	.LC0(%rip), %rdi
	call	_ZSt19__throw_logic_errorPKc@PLT
	.cfi_endproc
.LFE2983:
	.size	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_, .-_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_
	.weak	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_
	.set	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_,_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC2IS3_EEPKcRKS3_
	.section	.text._ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE,"axG",@progbits,_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE,comdat
	.weak	_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE
	.type	_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE, @function
_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE:
.LFB3083:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3083
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	movq	%rsi, %r14
	movq	%rdx, %r12
	movq	%rcx, %r13
	movq	%r8, %rbp
	leaq	16(%rdi), %rax
	movq	%rax, (%rdi)
	movq	$0, 8(%rdi)
	movb	$0, 16(%rdi)
	leaq	(%rdx,%r8), %rsi
.LEHB0:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE7reserveEm@PLT
	movq	%r12, %rdx
	movq	%r14, %rsi
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKcm@PLT
	movq	%rbp, %rdx
	movq	%r13, %rsi
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6appendEPKcm@PLT
.LEHE0:
	jmp	.L19
.L16:
	movq	%rax, %rbp
	movq	%rbx, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	%rbp, %rdi
.LEHB1:
	call	_Unwind_Resume@PLT
.LEHE1:
.L19:
	movq	%rbx, %rax
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3083:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table._ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE,"aG",@progbits,_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE,comdat
.LLSDA3083:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3083-.LLSDACSB3083
.LLSDACSB3083:
	.uleb128 .LEHB0-.LFB3083
	.uleb128 .LEHE0-.LEHB0
	.uleb128 .L16-.LFB3083
	.uleb128 0
	.uleb128 .LEHB1-.LFB3083
	.uleb128 .LEHE1-.LEHB1
	.uleb128 0
	.uleb128 0
.LLSDACSE3083:
	.section	.text._ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE,"axG",@progbits,_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE,comdat
	.size	_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE, .-_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE
	.section	.text._ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_,"axG",@progbits,_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_,comdat
	.weak	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_
	.type	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_, @function
_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_:
.LFB2980:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, %rbx
	movb	%sil, 12(%rsp)
	movq	%fs:40, %rax
	movq	%rax, 24(%rsp)
	xorl	%eax, %eax
	movq	(%rdx), %rcx
	leaq	12(%rsp), %rsi
	leaq	23(%rsp), %r9
	movq	8(%rdx), %r8
	movl	$1, %edx
	call	_ZSt12__str_concatINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEET_PKNS6_10value_typeENS6_9size_typeES9_SA_RKNS6_14allocator_typeE
	movq	24(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L23
	movq	%rbx, %rax
	addq	$32, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
.L23:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2980:
	.size	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_, .-_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_
	.text
	.globl	_Z9debug_repRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.type	_Z9debug_repRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, @function
_Z9debug_repRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE:
.LFB2713:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2713
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$56, %rsp
	.cfi_def_cfa_offset 80
	movq	%rdi, %rbx
	movq	%rsi, %rdx
	movq	%fs:40, %rax
	movq	%rax, 40(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %rbp
	movl	$34, %esi
	movq	%rbp, %rdi
.LEHB2:
	call	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EES5_RKS8_
.LEHE2:
	movl	$34, %edx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
.LEHB3:
	call	_ZStplIcSt11char_traitsIcESaIcEENSt7__cxx1112basic_stringIT_T0_T1_EEOS8_S5_
.LEHE3:
	movq	%rsp, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L31
	movq	%rbx, %rax
	addq	$56, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L28:
	.cfi_restore_state
	movq	%rax, %rbx
	movq	%rsp, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	40(%rsp), %rax
	subq	%fs:40, %rax
	je	.L26
	call	__stack_chk_fail@PLT
.L26:
	movq	%rbx, %rdi
.LEHB4:
	call	_Unwind_Resume@PLT
.LEHE4:
.L31:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2713:
	.section	.gcc_except_table,"a",@progbits
.LLSDA2713:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2713-.LLSDACSB2713
.LLSDACSB2713:
	.uleb128 .LEHB2-.LFB2713
	.uleb128 .LEHE2-.LEHB2
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB3-.LFB2713
	.uleb128 .LEHE3-.LEHB3
	.uleb128 .L28-.LFB2713
	.uleb128 0
	.uleb128 .LEHB4-.LFB2713
	.uleb128 .LEHE4-.LEHB4
	.uleb128 0
	.uleb128 0
.LLSDACSE2713:
	.text
	.size	_Z9debug_repRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE, .-_Z9debug_repRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
	.globl	_Z9debug_repB5cxx11Pc
	.type	_Z9debug_repB5cxx11Pc, @function
_Z9debug_repB5cxx11Pc:
.LFB2714:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2714
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$72, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, %rbx
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	leaq	15(%rsp), %rdx
	leaq	16(%rsp), %rbp
	movq	%rbp, %rdi
.LEHB5:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_
.LEHE5:
	movq	%rbp, %rsi
	movq	%rbx, %rdi
.LEHB6:
	call	_Z9debug_repRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE6:
	movq	%rbp, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L39
	movq	%rbx, %rax
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L36:
	.cfi_restore_state
	movq	%rax, %rbx
	leaq	16(%rsp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	je	.L34
	call	__stack_chk_fail@PLT
.L34:
	movq	%rbx, %rdi
.LEHB7:
	call	_Unwind_Resume@PLT
.LEHE7:
.L39:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2714:
	.section	.gcc_except_table
.LLSDA2714:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2714-.LLSDACSB2714
.LLSDACSB2714:
	.uleb128 .LEHB5-.LFB2714
	.uleb128 .LEHE5-.LEHB5
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB6-.LFB2714
	.uleb128 .LEHE6-.LEHB6
	.uleb128 .L36-.LFB2714
	.uleb128 0
	.uleb128 .LEHB7-.LFB2714
	.uleb128 .LEHE7-.LEHB7
	.uleb128 0
	.uleb128 0
.LLSDACSE2714:
	.text
	.size	_Z9debug_repB5cxx11Pc, .-_Z9debug_repB5cxx11Pc
	.globl	_Z9debug_repB5cxx11PKc
	.type	_Z9debug_repB5cxx11PKc, @function
_Z9debug_repB5cxx11PKc:
.LFB2715:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2715
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$72, %rsp
	.cfi_def_cfa_offset 96
	movq	%rdi, %rbx
	movq	%fs:40, %rax
	movq	%rax, 56(%rsp)
	xorl	%eax, %eax
	leaq	15(%rsp), %rdx
	leaq	16(%rsp), %rbp
	movq	%rbp, %rdi
.LEHB8:
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEC1IS3_EEPKcRKS3_
.LEHE8:
	movq	%rbp, %rsi
	movq	%rbx, %rdi
.LEHB9:
	call	_Z9debug_repRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
.LEHE9:
	movq	%rbp, %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L47
	movq	%rbx, %rax
	addq	$72, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
.L44:
	.cfi_restore_state
	movq	%rax, %rbx
	leaq	16(%rsp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	56(%rsp), %rax
	subq	%fs:40, %rax
	je	.L42
	call	__stack_chk_fail@PLT
.L42:
	movq	%rbx, %rdi
.LEHB10:
	call	_Unwind_Resume@PLT
.LEHE10:
.L47:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2715:
	.section	.gcc_except_table
.LLSDA2715:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2715-.LLSDACSB2715
.LLSDACSB2715:
	.uleb128 .LEHB8-.LFB2715
	.uleb128 .LEHE8-.LEHB8
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB9-.LFB2715
	.uleb128 .LEHE9-.LEHB9
	.uleb128 .L44-.LFB2715
	.uleb128 0
	.uleb128 .LEHB10-.LFB2715
	.uleb128 .LEHE10-.LEHB10
	.uleb128 0
	.uleb128 0
.LLSDACSE2715:
	.text
	.size	_Z9debug_repB5cxx11PKc, .-_Z9debug_repB5cxx11PKc
	.section	.text._Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB3101:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3101
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$384, %rsp
	.cfi_def_cfa_offset 416
	movq	%rdi, %rbx
	movq	%rsi, %rbp
	movq	%fs:40, %rax
	movq	%rax, 376(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %r12
	movq	%r12, %rdi
.LEHB11:
	call	_ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE11:
	pxor	%xmm0, %xmm0
	cvtss2sd	0(%rbp), %xmm0
	movq	%r12, %rdi
.LEHB12:
	call	_ZNSo9_M_insertIdEERSoT_@PLT
	leaq	8(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNKSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE12:
	movq	%rsp, %rdi
	call	_ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	376(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L55
	movq	%rbx, %rax
	addq	$384, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L52:
	.cfi_restore_state
	movq	%rax, %rbx
	movq	%rsp, %rdi
	call	_ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	376(%rsp), %rax
	subq	%fs:40, %rax
	je	.L50
	call	__stack_chk_fail@PLT
.L50:
	movq	%rbx, %rdi
.LEHB13:
	call	_Unwind_Resume@PLT
.LEHE13:
.L55:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3101:
	.section	.gcc_except_table
.LLSDA3101:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3101-.LLSDACSB3101
.LLSDACSB3101:
	.uleb128 .LEHB11-.LFB3101
	.uleb128 .LEHE11-.LEHB11
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB12-.LFB3101
	.uleb128 .LEHE12-.LEHB12
	.uleb128 .L52-.LFB3101
	.uleb128 0
	.uleb128 .LEHB13-.LFB3101
	.uleb128 .LEHE13-.LEHB13
	.uleb128 0
	.uleb128 0
.LLSDACSE3101:
	.section	.text._Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.weak	_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.type	_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, @function
_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_:
.LFB3100:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA3100
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$384, %rsp
	.cfi_def_cfa_offset 416
	movq	%rdi, %rbx
	movq	%rsi, %rbp
	movq	%fs:40, %rax
	movq	%rax, 376(%rsp)
	xorl	%eax, %eax
	movq	%rsp, %r12
	movq	%r12, %rdi
.LEHB14:
	call	_ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEEC1Ev@PLT
.LEHE14:
	movl	0(%rbp), %esi
	movq	%r12, %rdi
.LEHB15:
	call	_ZNSolsEi@PLT
	leaq	8(%rsp), %rsi
	movq	%rbx, %rdi
	call	_ZNKSt7__cxx1115basic_stringbufIcSt11char_traitsIcESaIcEE3strEv@PLT
.LEHE15:
	movq	%rsp, %rdi
	call	_ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	376(%rsp), %rax
	subq	%fs:40, %rax
	jne	.L63
	movq	%rbx, %rax
	addq	$384, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L60:
	.cfi_restore_state
	movq	%rax, %rbx
	movq	%rsp, %rdi
	call	_ZNSt7__cxx1119basic_ostringstreamIcSt11char_traitsIcESaIcEED1Ev@PLT
	movq	376(%rsp), %rax
	subq	%fs:40, %rax
	je	.L58
	call	__stack_chk_fail@PLT
.L58:
	movq	%rbx, %rdi
.LEHB16:
	call	_Unwind_Resume@PLT
.LEHE16:
.L63:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE3100:
	.section	.gcc_except_table
.LLSDA3100:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE3100-.LLSDACSB3100
.LLSDACSB3100:
	.uleb128 .LEHB14-.LFB3100
	.uleb128 .LEHE14-.LEHB14
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB15-.LFB3100
	.uleb128 .LEHE15-.LEHB15
	.uleb128 .L60-.LFB3100
	.uleb128 0
	.uleb128 .LEHB16-.LFB3100
	.uleb128 .LEHE16-.LEHB16
	.uleb128 0
	.uleb128 0
.LLSDACSE3100:
	.section	.text._Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,"axG",@progbits,_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_,comdat
	.size	_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_, .-_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
	.section	.text._Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_,"axG",@progbits,_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_,comdat
	.weak	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_
	.type	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_, @function
_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_:
.LFB3344:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movq	8(%rsi), %rdx
	movq	(%rsi), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3344:
	.size	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_, .-_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_
	.section	.text._Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_,"axG",@progbits,_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_,comdat
	.weak	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_
	.type	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_, @function
_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_:
.LFB3340:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	movq	%rdi, %rbx
	movq	%rdx, %rbp
	movq	8(%rsi), %rdx
	movq	(%rsi), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	movl	$44, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEERSoS6_RKT_
	addq	$8, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3340:
	.size	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_, .-_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_
	.section	.text._Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_,"axG",@progbits,_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_,comdat
	.weak	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_
	.type	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_, @function
_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_:
.LFB3324:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movq	%rdx, %rbp
	movq	%rcx, %r12
	movq	8(%rsi), %rdx
	movq	(%rsi), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	movl	$44, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_EERSoS6_RKT_DpRKT0_
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3324:
	.size	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_, .-_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_
	.section	.text._Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_,"axG",@progbits,_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_,comdat
	.weak	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_
	.type	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_, @function
_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_:
.LFB3303:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, %rbx
	movq	%rdx, %rbp
	movq	%rcx, %r12
	movq	%r8, %r13
	movq	8(%rsi), %rdx
	movq	(%rsi), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	movl	$44, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movq	%r13, %rcx
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_EERSoS6_RKT_DpRKT0_
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3303:
	.size	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_, .-_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_
	.section	.text._Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_,"axG",@progbits,_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_,comdat
	.weak	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	.type	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_, @function
_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_:
.LFB3271:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	movq	%rdx, %rbp
	movq	%rcx, %r12
	movq	%r8, %r13
	movq	%r9, %r14
	movq	8(%rsi), %rdx
	movq	(%rsi), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	movl	$44, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movq	%r14, %r8
	movq	%r13, %rcx
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_EERSoS6_RKT_DpRKT0_
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3271:
	.size	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_, .-_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	.section	.text._Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_,"axG",@progbits,_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_,comdat
	.weak	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	.type	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_, @function
_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_:
.LFB3196:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	movq	%rdx, %rbp
	movq	%rcx, %r12
	movq	%r8, %r13
	movq	%r9, %r14
	movq	8(%rsi), %rdx
	movq	(%rsi), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	movl	$44, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	movq	48(%rsp), %r9
	movq	%r14, %r8
	movq	%r13, %rcx
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3196:
	.size	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_, .-_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	.section	.text._Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_,"axG",@progbits,_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_,comdat
	.weak	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	.type	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_, @function
_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_:
.LFB3102:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movq	%rdi, %rbx
	movq	%rdx, %rbp
	movq	%rcx, %r12
	movq	%r8, %r13
	movq	%r9, %r14
	movq	8(%rsi), %rdx
	movq	(%rsi), %rsi
	call	_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l@PLT
	movq	%rax, %rdi
	movl	$44, %esi
	call	_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c@PLT
	subq	$8, %rsp
	.cfi_def_cfa_offset 56
	pushq	64(%rsp)
	.cfi_def_cfa_offset 64
	movq	64(%rsp), %r9
	movq	%r14, %r8
	movq	%r13, %rcx
	movq	%r12, %rdx
	movq	%rbp, %rsi
	movq	%rbx, %rdi
	call	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	addq	$16, %rsp
	.cfi_def_cfa_offset 48
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE3102:
	.size	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_, .-_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
	.section	.text._Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_,"axG",@progbits,_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_,comdat
	.weak	_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_
	.type	_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_, @function
_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_:
.LFB2985:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2985
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%r14
	pushq	%rbx
	subq	$272, %rsp
	.cfi_offset 14, -24
	.cfi_offset 3, -32
	movq	%rdi, %rbx
	movl	%esi, -260(%rbp)
	movl	%edx, -264(%rbp)
	movl	%ecx, -268(%rbp)
	movl	%r8d, -272(%rbp)
	movss	%xmm0, -276(%rbp)
	movq	%r9, %r14
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	leaq	-64(%rbp), %rdi
	movq	16(%rbp), %rsi
.LEHB17:
	call	_Z9debug_repB5cxx11PKc
.LEHE17:
	leaq	-96(%rbp), %rdi
	movq	%r14, %rsi
.LEHB18:
	call	_Z9debug_repB5cxx11PKc
.LEHE18:
	leaq	-128(%rbp), %rdi
	leaq	-276(%rbp), %rsi
.LEHB19:
	call	_Z9debug_repIfENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
.LEHE19:
	leaq	-160(%rbp), %rdi
	leaq	-272(%rbp), %rsi
.LEHB20:
	call	_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
.LEHE20:
	leaq	-192(%rbp), %rdi
	leaq	-268(%rbp), %rsi
.LEHB21:
	call	_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
.LEHE21:
	leaq	-224(%rbp), %rdi
	leaq	-264(%rbp), %rsi
.LEHB22:
	call	_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
.LEHE22:
	leaq	-256(%rbp), %rdi
	leaq	-260(%rbp), %rsi
.LEHB23:
	call	_Z9debug_repIiENSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERKT_
.LEHE23:
	leaq	-192(%rbp), %rcx
	leaq	-224(%rbp), %rdx
	leaq	-256(%rbp), %rsi
	leaq	-64(%rbp), %rax
	pushq	%rax
	leaq	-96(%rbp), %rax
	pushq	%rax
	leaq	-128(%rbp), %r9
	leaq	-160(%rbp), %r8
	movq	%rbx, %rdi
.LEHB24:
	.cfi_escape 0x2e,0x10
	call	_Z5printINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEJS5_S5_S5_S5_S5_S5_EERSoS6_RKT_DpRKT0_
.LEHE24:
	movq	%rax, %rbx
	addq	$16, %rsp
	leaq	-256(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	leaq	-224(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	leaq	-192(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	leaq	-160(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	leaq	-128(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	leaq	-96(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	leaq	-64(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	jne	.L97
	movq	%rbx, %rax
	leaq	-16(%rbp), %rsp
	popq	%rbx
	popq	%r14
	popq	%rbp
	.cfi_remember_state
	.cfi_def_cfa 7, 8
	ret
.L94:
	.cfi_restore_state
	movq	%rax, %rbx
	leaq	-256(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
.L80:
	leaq	-224(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
.L81:
	leaq	-192(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
.L82:
	leaq	-160(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
.L83:
	leaq	-128(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
.L84:
	leaq	-96(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
.L85:
	leaq	-64(%rbp), %rdi
	call	_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE10_M_disposeEv@PLT
	movq	-24(%rbp), %rax
	subq	%fs:40, %rax
	je	.L86
	call	__stack_chk_fail@PLT
.L93:
	movq	%rax, %rbx
	jmp	.L80
.L92:
	movq	%rax, %rbx
	jmp	.L81
.L91:
	movq	%rax, %rbx
	jmp	.L82
.L90:
	movq	%rax, %rbx
	jmp	.L83
.L89:
	movq	%rax, %rbx
	jmp	.L84
.L88:
	movq	%rax, %rbx
	jmp	.L85
.L86:
	movq	%rbx, %rdi
.LEHB25:
	call	_Unwind_Resume@PLT
.LEHE25:
.L97:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE2985:
	.section	.gcc_except_table
.LLSDA2985:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2985-.LLSDACSB2985
.LLSDACSB2985:
	.uleb128 .LEHB17-.LFB2985
	.uleb128 .LEHE17-.LEHB17
	.uleb128 0
	.uleb128 0
	.uleb128 .LEHB18-.LFB2985
	.uleb128 .LEHE18-.LEHB18
	.uleb128 .L88-.LFB2985
	.uleb128 0
	.uleb128 .LEHB19-.LFB2985
	.uleb128 .LEHE19-.LEHB19
	.uleb128 .L89-.LFB2985
	.uleb128 0
	.uleb128 .LEHB20-.LFB2985
	.uleb128 .LEHE20-.LEHB20
	.uleb128 .L90-.LFB2985
	.uleb128 0
	.uleb128 .LEHB21-.LFB2985
	.uleb128 .LEHE21-.LEHB21
	.uleb128 .L91-.LFB2985
	.uleb128 0
	.uleb128 .LEHB22-.LFB2985
	.uleb128 .LEHE22-.LEHB22
	.uleb128 .L92-.LFB2985
	.uleb128 0
	.uleb128 .LEHB23-.LFB2985
	.uleb128 .LEHE23-.LEHB23
	.uleb128 .L93-.LFB2985
	.uleb128 0
	.uleb128 .LEHB24-.LFB2985
	.uleb128 .LEHE24-.LEHB24
	.uleb128 .L94-.LFB2985
	.uleb128 0
	.uleb128 .LEHB25-.LFB2985
	.uleb128 .LEHE25-.LEHB25
	.uleb128 0
	.uleb128 0
.LLSDACSE2985:
	.section	.text._Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_,"axG",@progbits,_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_,comdat
	.size	_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_, .-_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"sss"
.LC2:
	.string	"alan"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2719:
	.cfi_startproc
	subq	$16, %rsp
	.cfi_def_cfa_offset 24
	leaq	.LC2(%rip), %rax
	pushq	%rax
	.cfi_def_cfa_offset 32
	leaq	.LC1(%rip), %r9
	movss	.LC3(%rip), %xmm0
	movl	$4, %r8d
	movl	$3, %ecx
	movl	$2, %edx
	movl	$1, %esi
	leaq	_ZSt4cout(%rip), %rdi
	call	_Z8errorMsgIJiiiifPKcS1_EERSoS2_DpKT_
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE2719:
	.size	main, .-main
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC3:
	.long	1091567616
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (GNU) 13.2.1 20230801"
	.section	.note.GNU-stack,"",@progbits
