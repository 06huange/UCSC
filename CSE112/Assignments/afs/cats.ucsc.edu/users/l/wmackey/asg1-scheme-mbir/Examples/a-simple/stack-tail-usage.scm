#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: stack-tail-usage.scm,v 1.3 2021-04-01 14:40:40-07 - - $

;;
;; Blow the stack by infinite recursion.  This function is not
;; a tail call.
;;

(define args (vector->list (current-command-line-arguments)))
(define want-tail-rec (not (null? args)))

(define million (exact-round 1e6))
(define MiB (expt 2 20))

(define (force-non-tail x) (null? x))

(define (recur count)
    (define (mem-use-mib)
        (truncate (/ (current-memory-use) MiB)))
    (when (= (remainder count million) 0)
          (printf "mem ~a MiB, count ~ae6, tail-rec ~a~n"
                  (mem-use-mib) (/ count million)
                  (if want-tail-rec 'yes 'no)))
    (let ((next (+ 1 count)))
         (if want-tail-rec
             (recur next)
             (force-non-tail (recur next)))))

(recur 0)


