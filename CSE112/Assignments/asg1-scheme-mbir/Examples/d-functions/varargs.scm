#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: varargs.scm,v 1.2 2021-04-09 10:34:56-07 - - $

;;
;; load with (load "varargs.scm")
;;
;; example defining a function with a variable number of params
;;

(define (writeln . list) (map write list) (newline))

(define (foo fst snd . rem )
        (writeln "foo = " foo)
        (writeln "fst = " fst)
        (writeln "snd = " snd)
        (writeln "rem = " rem))

