	.text
	.file	"temp.ll"
	.globl	main
	.align	16, 0x90
	.type	main,@function
main:                                   # @main
	.cfi_startproc
# BB#0:                                 # %entry
	pushq	%rax
.Ltmp0:
	.cfi_def_cfa_offset 16
	movl	$.L__unnamed_1, %edi
	movl	$t, %esi
	callq	scanf
	cmpl	$0, t(%rip)
	movl	$1, i(%rip)
	je	.LBB0_4
	.align	16, 0x90
.LBB0_1:                                # %loopBlock
                                        # =>This Loop Header: Depth=1
                                        #     Child Loop BB0_2 Depth 2
	movl	$.L__unnamed_2, %edi
	movl	$n, %esi
	movl	$r, %edx
	callq	scanf
	movl	$1, num(%rip)
	cmpl	$0, r(%rip)
	movl	$1, j(%rip)
	je	.LBB0_3
	.align	16, 0x90
.LBB0_2:                                # %loopBlock1
                                        #   Parent Loop BB0_1 Depth=1
                                        # =>  This Inner Loop Header: Depth=2
	movl	n(%rip), %eax
	subl	j(%rip), %eax
	incl	%eax
	movl	%eax, den(%rip)
	imull	num(%rip), %eax
	xorl	%edx, %edx
	divl	j(%rip)
	movl	%eax, num(%rip)
	movl	j(%rip), %eax
	incl	%eax
	cmpl	r(%rip), %eax
	movl	%eax, j(%rip)
	jbe	.LBB0_2
.LBB0_3:                                # %nextBlock2
                                        #   in Loop: Header=BB0_1 Depth=1
	movl	num(%rip), %esi
	movl	$.L__unnamed_3, %edi
	callq	printf
	movl	i(%rip), %eax
	incl	%eax
	cmpl	t(%rip), %eax
	movl	%eax, i(%rip)
	jbe	.LBB0_1
.LBB0_4:                                # %nextBlock
	xorl	%eax, %eax
	popq	%rcx
	retq
.Lfunc_end0:
	.size	main, .Lfunc_end0-main
	.cfi_endproc

	.type	t,@object               # @t
	.comm	t,4,4
	.type	num,@object             # @num
	.comm	num,4,4
	.type	j,@object               # @j
	.comm	j,4,4
	.type	i,@object               # @i
	.comm	i,4,4
	.type	den,@object             # @den
	.comm	den,4,4
	.type	val,@object             # @val
	.comm	val,4,4
	.type	r,@object               # @r
	.comm	r,4,4
	.type	n,@object               # @n
	.comm	n,4,4
	.type	.L__unnamed_1,@object   # @0
	.section	.rodata.str1.1,"aMS",@progbits,1
.L__unnamed_1:
	.asciz	"%d"
	.size	.L__unnamed_1, 3

	.type	.L__unnamed_2,@object   # @1
.L__unnamed_2:
	.asciz	"%d%d"
	.size	.L__unnamed_2, 5

	.type	.L__unnamed_3,@object   # @2
.L__unnamed_3:
	.asciz	"%d \n"
	.size	.L__unnamed_3, 5


	.section	".note.GNU-stack","",@progbits
