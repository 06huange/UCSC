.... (* $Id: boolvar.ml,v 1.1 2021-04-01 00:52:49-07 - - $ *)
.... let flag : bool ref = ref false;;
.... flag := true;;
.... if !flag then Printf.printf "Flag is true\n";;
caml_negf_mask:
caml_absf_mask:
camlBoolvar:
camlBoolvar__gc_roots:
camlBoolvar__1:
	.ascii	"Flag is true\12"
camlBoolvar__2:
camlBoolvar__3:
	.ascii	"Flag is true\12"
camlBoolvar__4:
camlBoolvar__entry:
	subq	$8, %rsp
.L102:
	call	caml_alloc1@PLT
.L103:
	leaq	8(%r15), %rax
	movq	$1024, -8(%rax)
	movq	$1, (%rax)
	movq	camlBoolvar@GOTPCREL(%rip), %rbx
	movq	%rax, (%rbx)
	movq	(%rbx), %rax
	movq	$3, (%rax)
	movq	(%rbx), %rax
	movq	(%rax), %rax
	cmpq	$1, %rax
	je	.L101
	movq	camlBoolvar__4@GOTPCREL(%rip), %rbx
	movq	camlStdlib@GOTPCREL(%rip), %rax
	movq	304(%rax), %rax
	call	camlStdlib__printf__fprintf_166@PLT
.L100:
.L101:
	movq	$1, %rax
	addq	$8, %rsp
	ret
camlBoolvar__frametable:
.L104:
.L105:
	.ascii	"printf.ml\0"
