(* $Id: qsort.ml,v 1.1 2021-01-26 00:12:08-08 - - $ *)

(*
* Tricky version of qsort.  
* Note:  O(n^2) if pivot is badly chosen.
*)

let filter = List.filter ;;
let compose f g x = f (g x) ;;

let rec qsort (<?) list = match list with
    | [] -> []
    | car::[] -> list
    | car::cdr -> 
      let (large) = filter ((<?) car) cdr
      and (small) = filter (compose not ((<?) car)) cdr
      in qsort (<?) small @ [car] @ qsort (<?) large
    ;;

let thelist = [6; 7; 11; 8; 4; 2; 9; -4; 10] ;;

qsort (<) thelist ;;
qsort (>) thelist ;;

