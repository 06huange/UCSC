#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: lazy-stream.scm,v 1.3 2021-04-09 19:59:12-07 - - $

(define-syntax zcons
    (syntax-rules ()
        ((_ ca cd)
         (cons ca (delay cd)))))

(define (zcar stream)
    (car stream))

(define (zcdr stream)
    (force (cdr stream)))

(define (zfrom n)
    (zcons n (zfrom (+ n 1))))

(define naturals (zfrom 1))

(define (ztake n stream)
    (cond ((<= n 0) '())
          ((null? stream) '())
          (else cons (zcar stream)
                     (ztake (- n 1) (zcdr stream)))))

(define (zdrop n stream)
    (cond ((<= n 0) stream)
          ((null? stream) '())
          (else (zdrop (- n 1) (zcdr stream)))))

(define (zfilter pred? stream)
    (if (null? stream) '()
        (let ((hcar (zcar stream))
              (hcdr (zfilter pred? (zcdr stream))))
             (if (pred? hcar) (cons hcar hcdr)
                              hcdr))))

(define (primes)
    (define (primes from)
        (let* ((prime (zcar from))
               (ok (lambda (n) (not (= (remainder n prime) 0)))))
              (zcons prime (zfilter ok (zcdr from)))))
    (primes (zfrom 2)))

