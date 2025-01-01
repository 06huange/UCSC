#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: complex.scm,v 1.1 2021-04-01 14:26:16-07 - - $

(define i (sqrt -1))

(define (complex-abs x)
    (sqrt (+ (sqr (real-part x))
             (sqr (imag-part x)))))

(printf "i = ~a~n" i)
(printf "(real-part i) = ~a~n" (real-part i))
(printf "(imag-part i) = ~a~n" (imag-part i))
(printf "(complex-abs i) = ~a~n" (complex-abs i))

