#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: mutualrec.scm,v 1.1 2021-03-31 22:35:41-07 - - $

(define (even list)
    (when (not (null? list))
          (printf "even: ~s~n" (car list))
          (odd (cdr list))))

(define (odd list)
    (when (not (null? list))
          (printf "odd: ~s~n" (car list))
          (even (cdr list))))

(even '(hello world foo bar baz qux))

