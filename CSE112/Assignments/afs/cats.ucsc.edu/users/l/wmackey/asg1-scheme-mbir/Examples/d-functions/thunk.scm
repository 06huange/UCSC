#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: thunk.scm,v 1.2 2021-04-09 17:56:34-07 - - $

(define (f n)
    (define (g n m)
        (if (< n 1) m
            (g (- n 1) (* n m))))
    (g n 1))

(define (fac n)
    (let ((fn (f n)))
    (printf "computed: (fac ~a) = ~a~n" n fn)
    fn))

(display (fac 16)) (newline)

(display (fac 16)) (newline)

(define thunk32 (delay (fac 32)))

(display thunk32) (newline)

(display (force thunk32)) (newline)

(display (force thunk32)) (newline)

