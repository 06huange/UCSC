
(* $Id: p3-foldl.ml,v 1.7 2021-04-29 20:10:59-07 - - $ *)

let compose f g x = f (g x);;
let swap f x y = f y x;;
let cons a d = a::d;;

let even x = x mod 2 = 0;;
let odd = compose not even;;

let rec foldl fn unit list = match list with
    | [] -> unit
    | car::cdr -> foldl fn (fn unit car) cdr

let sum_rec list = 
    let rec sum lis acc = match lis with
        | [] -> acc
        | x::xs -> sum xs (acc + x)
    in  sum list 0;;

let sum_fold = foldl (+) 0;;
 
let rec len_rec list =
    let rec len lis acc = match lis with
        | [] -> acc
        | _::xs -> len xs (acc + 1)
    in  len list 0;;

let len_fold = foldl (fun u _ -> u + 1) 0;;

let reduce f list = match list with
    | [] -> failwith "reduce"
    | x::xs -> foldl f x xs;;

let reduce_opt f list = match list with
    | [] -> None
    | x::xs -> Some (foldl f x xs);;

let min x y = if x < y then x else y;;

let minlist list = reduce min list;;

let minlist_opt list = reduce min list;;

let reverse_rec list = 
    let rec rev lis accum = match lis with
        | [] -> accum
        | x::xs -> rev xs (x::accum)
    in rev list [];;

let reverse_fold = foldl (swap cons) [];;

let rec member_rec item list = match list with
    | [] -> false
    | x::_ when x = item -> true
    | _::xs -> member_rec item xs;;

let member_fold item =
    foldl (fun found x -> found || found = x) false;;

