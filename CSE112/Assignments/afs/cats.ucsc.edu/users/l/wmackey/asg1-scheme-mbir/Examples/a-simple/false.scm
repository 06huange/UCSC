#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: false.scm,v 1.1 2021-04-01 14:26:34-07 - - $

(define (tf arg)
    (if arg 'true 'false))

(define (fn arg . rem)
    (printf "~n")
    (printf "arg: ~s ~s~n" (tf arg) arg)
    (printf "rem: ~s ~s~n" (tf rem) rem))

(fn #t)
(fn #f)
(fn 0)
(fn "")
(fn '())
(fn 1 2 3 4)

