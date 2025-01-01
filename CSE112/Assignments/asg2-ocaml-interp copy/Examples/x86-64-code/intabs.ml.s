.... (* $Id: intabs.ml,v 1.3 2021-04-01 16:33:51-07 - - $ *)
.... let intabs n =
....     if n < 0 then -n
....              else n
caml_negf_mask:
caml_absf_mask:
camlIntabs__1:
camlIntabs:
camlIntabs__gc_roots:
camlIntabs__intabs_80:
.L101:
	cmpq	$1, %rax
	jge	.L100
	movq	$2, %rbx
	subq	%rax, %rbx
	movq	%rbx, %rax
	ret
.L100:
	ret
camlIntabs__entry:
.L102:
	movq	camlIntabs__1@GOTPCREL(%rip), %rax
	movq	camlIntabs@GOTPCREL(%rip), %rbx
	movq	%rax, (%rbx)
	movq	$1, %rax
	ret
camlIntabs__frametable:
