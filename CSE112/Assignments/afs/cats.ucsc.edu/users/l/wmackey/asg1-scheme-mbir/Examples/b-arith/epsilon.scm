#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: epsilon.scm,v 1.2 2021-04-07 01:10:00-07 - - $

(define (find-epsilon epsilon)
    (let ((sum (+ 1 epsilon)))
         (printf "(+ 1.0 ~s) = ~s~n" epsilon (+ 1.0 epsilon))
         (when (> sum 1.0) (find-epsilon (/ epsilon 2.0)))))

(printf "What is epsilon?~n")
(find-epsilon 1.0)
