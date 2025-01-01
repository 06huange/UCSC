.... // $Id: longabs.c,v 1.1 2021-04-01 00:52:49-07 - - $
.... long longabs (long n) {
....    if (n < 0) return -n;
....    return n;
.... }
longabs:
.LFB0:
	movq	%rdi, %rdx
	movq	%rdi, %rax
	sarq	$63, %rdx
	xorq	%rdx, %rax
	subq	%rdx, %rax
	ret
.LFE0:
