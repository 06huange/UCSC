#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: simple-eval.scm,v 1.3 2021-04-01 21:08:36-07 - - $

(require racket/trace)

(define (eval-expr expr)
    (if (number? expr) (+ expr 0.0)
        (apply (car expr)
               (map eval-expr (cdr expr)))))

(define (print-eval expr)
    (printf "~s~n= ~s~n" expr (eval-expr expr)))

(print-eval 3)
(print-eval `(,/ 1 0))
(print-eval `(,+ 4.14 2.71))
(print-eval `(,sqrt -1))
(print-eval `(,+ (,* 2 3) (,* 4 5)))
(print-eval `(,* (,+ 8 3) (,+ (,* 2 9) 6)))

