(* $Id: p5-zip.ml,v 1.1 2021-04-29 11:29:19-07 - - $ *)

let rec foldl fn unit list = match list with
    | [] -> unit
    | car::cdr -> foldl fn (fn unit car) cdr

let rec unzip list = match list with
    | [] -> [],[]
    | (a,b)::xs -> let axs,bxs = unzip xs
                   in  a::axs, b::bxs;;

let rec zip ls1 ls2 = match ls1, ls2 with
    | [], [] -> []
    | [], _ -> failwith "zip"
    | _, [] -> failwith "zip"
    | x::xs, y::ys -> (x,y) :: zip xs ys;;

let rec zipwith fn ls1 ls2 = match ls1, ls2 with
    | [], [] -> []
    | [], _ -> failwith "zipwith"
    | _, [] -> failwith "zipwith"
    | x::xs, y::ys -> fn x y :: zipwith fn xs ys;;

let innerprod lis1 lis2 =
    foldl (+.) 0. (zipwith ( *.) lis1 lis2);;
    
