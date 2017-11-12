	.text
	.file	"temp.bc"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$10, i(%rip)
	movl	$0, sum(%rip)
	cmpl	$10, i(%rip)
	je	.LBB0_2
	jmp	.LBB0_3
	.align	16, 0x90
.LBB0_1:                                # %loopBlock
                                        #   in Loop: Header=BB0_2 Depth=1
	movl	i(%rip), %eax
	incl	%eax
	movl	%eax, i(%rip)
	addl	%eax, sum(%rip)
.LBB0_2:                                # %loopBlock
                                        # =>This Inner Loop Header: Depth=1
	cmpl	$100000, i(%rip)        # imm = 0x186A0
	jb	.LBB0_1
.LBB0_3:                                # %contBlock
	movl	i(%rip), %esi
	movl	$.L__unnamed_1, %edi
	callq	printf
	movl	sum(%rip), %edx
	leal	1(%rdx), %esi
	movl	$.L__unnamed_2, %edi
	callq	printf
	xorl	%eax, %eax
	popq	%rcx
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	sum,@object             # @sum
	.comm	sum,4,4
	.type	i,@object               # @i
	.comm	i,4,4
	.type	data,@object            # @data
	.comm	data,400,4
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"i:  %d "
	.size	.L__unnamed_1, 8

	.type	.L__unnamed_3,@object   # @1
.L__unnamed_3:
	.asciz	"i: "
	.size	.L__unnamed_3, 4

	.type	.L__unnamed_2,@object   # @2
.L__unnamed_2:
	.asciz	"Sum:  %d %d \n"
	.size	.L__unnamed_2, 14

	.type	.L__unnamed_4,@object   # @3
.L__unnamed_4:
	.asciz	"Sum: "
	.size	.L__unnamed_4, 6


	.section	".note.GNU-stack","",@progbits
