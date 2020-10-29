	.section	.rodata
STR0:
	.string	"%d"
STR1:
    .string "%d\n"

	.text
	.globl	main
	.type	main, @function
main:
    # endbr32
    pushl %ebp
    pushl %eax
    movl %esp, %ebp
    subl $16, %esp

    # scanf("%d", &n)
    leal -8(%ebp), %eax
    pushl %eax
    pushl $STR0
    call scanf
    addl $8, %esp

    # i = 2
    movl $2, -4(%ebp)
    # f = 1
    movl $1, (%ebp)
    jmp .L3

.L2:
    # f = f * i
    movl (%ebp), %eax
    imull -4(%ebp), %eax
    movl %eax, (%ebp)

    # i = i + 1
    movl -4(%ebp), %eax
    addl $1, %eax
    movl %eax, -4(%ebp)

.L3:
    # i <= n
    movl -8(%ebp), %eax
        # check i - n <= 0
    cmpl %eax, -4(%ebp)
    jle .L2

    # printf("%d\n", f)
    movl (%ebp), %eax
    pushl %eax
    pushl $STR1
    call printf
    addl $8, %esp

.END:
    movl %ebp, %esp
    popl %eax
    popl %ebp
 
    # return 0
    movl $0, %eax
    ret

    # .hidden __stack_chk_fail_local
    # .ident "GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
    .section .note.GNU-stack,"",@progbits
    # .section .note.gnu.property,"a"