#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: with-handler.scm,v 1.1 2021-03-31 22:35:41-07 - - $

(define (prtnl x) (display x) (newline))

(define (show x)
    (begin (printf "[[[[[[[[~n~a~n]]]]]]]]~n" x)
           (printf "[[[[[[[[~n~s~n]]]]]]]]~n" x)
           (prtnl (exn:fail:filesystem:errno-errno x))
           (let ((err (car (exn:fail:filesystem:errno-errno x))))
                (printf "can not open input file (errno=~a)~n" err))
))

(with-handlers
    ((exn:fail:filesystem:errno? show))
    (open-input-file "foo"))
