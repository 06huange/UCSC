#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;; $Id: sysinfo.scm,v 1.2 2021-04-09 10:43:25-07 - - $
;;
;; Print system path information.

(define system-symbols '(

   addon-dir
   collects-dir
   desk-dir
   doc-dir
   exec-file
   home-dir
   init-dir
   init-file
   orig-dir
   pref-dir
   pref-file
   run-file
   sys-dir
   temp-dir

))

(define (print-sysinfo symbol)
        (for-each display
                  (list symbol " = " (find-system-path symbol)))
        (newline))

(for-each print-sysinfo system-symbols)
