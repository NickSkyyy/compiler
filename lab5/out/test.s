	.section	.rodata
_CHAR:
	.string	"%c"
_INT:
	.string	"%d"
_STRING:
	.string	"%s"
	.text
	.globl	main
	.type	main, @function
main:
	pushl	%ebp
	pushl	%eax
	movl	%esp, %ebp
	# printf
	movl	$100, %eax
	pushl	%eax
	pushl	$_INT
	call	printf
	addl	$8, %esp
	# printf
	movl	$10, %eax
	pushl	%eax
	pushl	$_CHAR
	call	printf
	addl	$8, %esp
.END:
	movl	%ebp, %esp
	popl	%eax
	popl	%ebp
	movl	$0, %eax
	ret
	.section .note.GNU-stack,"",@progbits