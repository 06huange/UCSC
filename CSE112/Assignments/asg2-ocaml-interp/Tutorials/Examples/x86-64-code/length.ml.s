.... (* $Id: length.ml,v 1.1 2021-04-01 00:52:49-07 - - $ *)
.... let length list =
....     let rec len list sum = match list with
....         | [] -> sum
....         | _::xs -> len xs (sum + 1)
....     in len list 0
caml_negf_mask:
caml_absf_mask:
camlLength__2:
camlLength__1:
camlLength:
camlLength__gc_roots:
camlLength__length_80:
.L102:
	cmpq	$1, %rax
	je	.L101
	movq	$3, %rbx
	movq	8(%rax), %rax
	jmp	camlLength__len_82@PLT
.L101:
	movq	$1, %rax
	ret
camlLength__len_82:
.L105:
	cmpq	$1, %rax
	je	.L104
	addq	$2, %rbx
	movq	8(%rax), %rax
	jmp	.L105
.L104:
	movq	%rbx, %rax
	ret
camlLength__entry:
.L106:
	movq	camlLength__1@GOTPCREL(%rip), %rax
	movq	camlLength@GOTPCREL(%rip), %rbx
	movq	%rax, (%rbx)
	movq	$1, %rax
	ret
camlLength__frametable:
