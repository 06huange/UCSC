(* $Id: p4-foldr.ml,v 1.4 2021-04-29 11:51:55-07 - - $ *)


let rec foldr fn unit list = match list with
    | [] -> unit
    | car::cdr -> fn car (foldr fn unit cdr);;

let rec map_rec f list = match list with
    | [] -> []
    | x::xs -> f x :: map_rec f xs;;

let map_fold fn = foldr (fun h t -> fn h :: t) [];;

let rec filter_rec pred list = match list with
    | [] -> []
    | x::xs when pred x -> x :: filter_rec pred xs
    | _::xs -> filter_rec pred xs;;

let filter_fold pred =
    foldr (fun h t -> if pred h then h::t else t) [];;

let rec append_rec lis1 lis2 = match lis1 with
    | [] -> lis2
    | x::xs -> x :: append_rec xs lis2;;

let append_fold lis1 lis2 =
    foldr (fun a d -> a::d) lis1 lis2;;

