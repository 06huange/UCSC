#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: quine.scm,v 1.2 2021-04-09 10:43:30-07 - - $

     ((lambda (x)
       (list x (list 'quote x)))
         '(lambda (x)
           (list x (list 'quote x))))

