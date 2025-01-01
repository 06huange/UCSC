#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/ocaml/bin/ocaml
(* $Id: find-opt-exn.ml,v 1.4 2021-04-22 20:37:53-07 - - $ *)

(*
* Linear search to find an item in a list of (key*value) tuples.
*)

open Printf;;

(*
* type 'a option = None | Some 'a
*)

let rec find_opt eq want list = match list with
    | [] -> None
    | (key,value)::_ when eq want key -> Some value
    | _::tail -> find_opt eq want tail;;

(*
* val find_opt : ('a -> 'b -> bool)
*              -> 'a
*              -> ('b * 'c) list
*              -> 'c option = <fun>
*)

let rec find_exn eq want list = match list with
    | [] -> raise Not_found
    | (key,value)::_ when eq want key -> value
    | _::tail -> find_exn eq want tail;;

(*
* val find_exn : ('a -> 'b -> bool)
*              -> 'a
*              -> ('b * 'c) list
*              -> 'c = <fun>
*)

let data = [1,"one"; 3,"three"; 5,"five"; 7,"seven"; ];;

printf "Data:\n";;
List.iter (fun (key,value) -> printf "(%d, %s)\n" key value)
          data;;

let search_opt key =
    let result = find_opt (=) key data
    in  match result with
        | None -> printf "%d -> None\n" key
        | Some value -> printf "%d -> Some %s\n" key value;;

let search_exn key =
    try printf "%d -> %s\n" key (find_exn (=) key data)
    with Not_found -> printf "%d: Not found\n" key;;

printf "\nsearch_opt:\n";
List.iter search_opt [1; 5; 7; 9; 11];;

printf "\nsearch_exn:\n";
List.iter search_exn [1; 5; 7; 9; 11];;

