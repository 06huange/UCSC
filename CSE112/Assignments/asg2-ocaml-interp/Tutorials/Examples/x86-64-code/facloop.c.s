.... // $Id: facloop.c,v 1.1 2021-04-01 00:52:49-07 - - $
.... long factorial (long n) {
....    long m = 1;
....    while (n > 1) m *= n--;
....    return m;
.... }
factorial:
.LFB0:
	movl	$1, %eax
	cmpq	$1, %rdi
	jle	.L4
.L3:
	imulq	%rdi, %rax
	subq	$1, %rdi
	cmpq	$1, %rdi
	jne	.L3
	ret
.L4:
	ret
.LFE0:
