(* $Id: p1-uncurry.ml,v 1.3 2021-04-29 19:14:01-07 - - $ *)

let uncurry f (x, y) = f x y;;

let curry f x y = f (x, y);;


