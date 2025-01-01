(* $Id: length.ml,v 1.1 2021-04-01 00:52:49-07 - - $ *)
let length list =
    let rec len list sum = match list with
        | [] -> sum
        | _::xs -> len xs (sum + 1)
    in len list 0
