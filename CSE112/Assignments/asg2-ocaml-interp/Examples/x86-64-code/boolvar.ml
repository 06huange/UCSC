(* $Id: boolvar.ml,v 1.1 2021-04-01 00:52:49-07 - - $ *)
let flag : bool ref = ref false;;
flag := true;;
if !flag then Printf.printf "Flag is true\n";;
