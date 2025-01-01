#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: commandline.scm,v 1.1 2021-04-01 14:26:16-07 - - $

(define args (vector->list (current-command-line-arguments)))

(define (show args)
    (when (not (null? args))
          (let ((arg (car args)))
               (printf "~s ~s ~s~n"
                   (string? arg)
                   (immutable? arg)
                   arg)
          (show (cdr args)))))

(show args)

