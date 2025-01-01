#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/ocaml/bin/ocaml
(* $Id: eval1-simple.ml,v 1.2 2021-04-20 16:53:41-07 - - $ *)

type binfn = float -> float -> float;;

type expr = Expr of binfn * expr * expr
          | Num of float;;

let rec eval_expr expr = match expr with
    | Num value -> value
    | Expr (binfn, e1, e2) -> binfn (eval_expr e1) (eval_expr e2);;

eval_expr (Num 3.14);;

eval_expr (Expr ((+.), Num 3., Num 4.));;

eval_expr (Expr ((+.),
      Expr ((/.), Num 3., Num 4.),
      Expr ((/.), Num 7., Num 8.)));;

let e1 = Expr (( *.), Num 3., Num 3.);;
let e2 = Expr (( *.), Num 4., Num 4.);;

eval_expr (Expr ((+.), e1, e2));;
