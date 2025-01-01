(* $Id: factorial.ml,v 1.1 2021-04-01 00:52:49-07 - - $ *)
let fac n =
    let rec fac' n' r' =
        if n < 1 then r'
                 else fac' (n' - 1) (n' * r')
    in fac' n 1;;
