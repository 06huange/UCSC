#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: euler.scm,v 1.3 2021-04-07 01:09:29-07 - - $

(define i (sqrt -1))
(define pi (acos -1))

(define euler-exp '(lambda (x) (exp (* i x))))
(define euler-trig '(lambda (x) (+ (cos x) (* i (sin x)))))

(define (show expr)
    (printf "~s = ~s~n"  expr (eval expr)))

(show 'i)
(show 'pi)

(show 'euler-exp)
(show 'euler-trig)

(show '((eval euler-exp) pi))
(show '((eval euler-trig) pi))
(show '(- ((eval euler-exp) pi) ((eval euler-trig) pi)))

(show '((eval euler-exp) 0))
(show '((eval euler-trig) 0))
(show '(- ((eval euler-exp) 0) ((eval euler-trig) 0)))

