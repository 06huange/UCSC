#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: readnums.scm,v 1.2 2021-04-06 20:24:58-07 - - $

;;
;; Read numbers from stdin, stopping at end of file.
;;

{define (readnumber)
        (let ((object (read))
              (nan (/ 0.0 0.0)))
             (printf "object: ~a~n" object)
             (cond [(eof-object? object) object]
                   [(number? object) (+ object 0.0)]
                   [else nan]))}

{define (testinput)
        (let ((number (readnumber)))
             (if (eof-object? number)
                 (printf "*EOF* ~a~n" number)
                 (begin (printf "number = ~a~n" number)
                        (testinput)))) }

(testinput)

