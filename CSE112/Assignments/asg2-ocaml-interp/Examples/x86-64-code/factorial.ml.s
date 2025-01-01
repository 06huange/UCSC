.... (* $Id: factorial.ml,v 1.1 2021-04-01 00:52:49-07 - - $ *)
.... let fac n =
....     let rec fac' n' r' =
....         if n < 1 then r'
....                  else fac' (n' - 1) (n' * r')
....     in fac' n 1;;
caml_negf_mask:
caml_absf_mask:
camlFactorial__1:
camlFactorial:
camlFactorial__gc_roots:
camlFactorial__fac_80:
	subq	$8, %rsp
.L101:
	movq	%rax, %rsi
.L102:
	subq	$40, %r15
	movq	caml_young_limit@GOTPCREL(%rip), %rax
	cmpq	(%rax), %r15
	jb	.L103
	leaq	8(%r15), %rdi
	movq	$4343, -8(%rdi)
	movq	caml_curry2@GOTPCREL(%rip), %rax
	movq	%rax, (%rdi)
	movq	$5, 8(%rdi)
	movq	camlFactorial__fac$27_82@GOTPCREL(%rip), %rax
	movq	%rax, 16(%rdi)
	movq	%rsi, 24(%rdi)
	movq	$3, %rbx
	movq	%rsi, %rax
	addq	$8, %rsp
	jmp	camlFactorial__fac$27_82@PLT
.L103:
	call	caml_call_gc@PLT
.L104:
	jmp	.L102
camlFactorial__fac$27_82:
.L107:
	movq	24(%rdi), %rsi
	cmpq	$3, %rsi
	jge	.L106
	movq	%rbx, %rax
	ret
.L106:
	movq	%rbx, %rsi
	sarq	$1, %rsi
	movq	%rax, %rbx
	decq	%rbx
	imulq	%rsi, %rbx
	incq	%rbx
	addq	$-2, %rax
	jmp	.L107
camlFactorial__entry:
.L108:
	movq	camlFactorial__1@GOTPCREL(%rip), %rax
	movq	camlFactorial@GOTPCREL(%rip), %rbx
	movq	%rax, (%rbx)
	movq	$1, %rax
	ret
camlFactorial__frametable:
