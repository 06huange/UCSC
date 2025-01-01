(require racket/trace)

;; non tail-recursive
(define (fac-non-tail n)
   (if (<= n 0) 1
       (* n (fac-non-tail (- n 1)))))

;; traceable tail recursive
(define (fac-tail-helper n acc)
    (if (<= n 0) acc
        (fac-tail-helper (- n 1) (* n acc))))
(define (fac-tail n)
    (fac-tail-helper n 1))

(trace fac-non-tail)
(trace fac-tail fac-tail-helper)

;; $Id: factorial.scm,v 1.3 2021-04-01 15:23:37-07 - - $
