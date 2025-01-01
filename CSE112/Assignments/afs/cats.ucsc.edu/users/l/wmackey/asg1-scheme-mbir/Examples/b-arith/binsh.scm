#!/bin/sh
":";exec mzscheme -qr $0 "$@"
;; $Id: binsh.scm,v 1.1 2021-04-01 14:26:16-07 - - $

;;
;; This file shows how to execute mzscheme using the shell
;; Normally a hashbang would refer to the actual binary.
;; This file is then bilingual.  When seen by the shell,
;; it execs mzscheme which must be somewhere in your path.
;; when seen by Scheme, the semi-colon in the exec line
;; appears as a comment.
;;

(printf "~a~n" "Hello, world!")
(printf "~s~n" (current-command-line-arguments))

;;TEST: binsh.scm
