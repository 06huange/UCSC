(* $Id: p2-apply.ml,v 1.2 2021-04-29 11:47:37-07 - - $ *)

let rec apply_n f n x =
    if n < 0 then failwith "apply_n"
    else if n = 0 then x
    else apply_n f (n - 1) (f x);;

apply_n (fun x -> x + 1) 4 0;;

