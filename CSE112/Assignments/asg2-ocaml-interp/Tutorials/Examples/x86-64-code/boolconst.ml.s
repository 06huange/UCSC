.... (* $Id: boolconst.ml,v 1.1 2021-04-01 00:52:49-07 - - $ *)
.... let flag = false;;
.... if flag then Printf.printf "Flag is true\n";;
caml_negf_mask:
caml_absf_mask:
camlBoolconst:
camlBoolconst__gc_roots:
camlBoolconst__entry:
.L100:
	movq	camlBoolconst@GOTPCREL(%rip), %rax
	movq	$1, (%rax)
	movq	$1, %rax
	ret
camlBoolconst__frametable:
