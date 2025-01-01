#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/ocaml/bin/ocaml
(* $Id: epsilon.ml,v 1.7 2021-04-20 13:57:04-07 - - $ *)

open Printf;;

let rec find_epsilon epsilon =
    let sum = 1.0 +. epsilon
    in (printf "1.0 +. %.17g = %.17g\n" epsilon (1.0 +. epsilon);
        if sum > 1.0 then find_epsilon (epsilon /. 2.0));;

printf "What is epsilon?\n";;
find_epsilon 1.0;;

