#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: isnan.scm,v 1.2 2021-04-11 14:31:58-07 - - $

(define (nan? x)
    (and (number? x)
         (not (= x x))))

(define (test x)
    (printf "(nan? ~s) = ~s~n" x (nan? x)))

(define nan (/ 0.0 0.0))

(test nan)
(test (/ 1.0 0.0))
(test 3)
(test 'hello)
(test "hello")
(test '(/ 0.0 0.0))

