.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.ds Quarter Spring\~2021
.TITLE CSE-112 \*[Quarter] "Study Guide"
.RCS \
"$Id: cse112-study-guide-2021-q2spring.mm,v 1.57 2021-05-05 22:24:48-07 - - $"
.PWD
.URL
.SA 0
.na
.nr Hy 0
.nh
.de HHH
.   DE
.   DS
.   fi
.   H 1 "\\$1"
..
.DS
.HHH "Week 1 \[em] Tuesday March 30"
.ALX a ()
.LI
Syllabus, pair programming, course overview.
Lab0 intro unix, and review of Data Structures labs.
Reference to study guides.
.LI
.V= Languages/Hello ,
.V= Languages/Collatz \[em]
Examples of simple programs in multiple languages\(::
Bash, C++, Ocaml, Perl, Prolog, Scheme, Smalltalk.
.LI
Lecture notes\(::
.V= scheme-1-language.pdf 
(p.\~1\[en]4).
.if n .sp
.LI
.V= Languages/scheme/Examples/a-simple
\[em]
Simple introductory Scheme programs\(::
.V= hello.scm ,
.V= false.scm ,
.V= factorial.scm ,
.V= fibonacci.scm
(with tracing).
.LE
.HHH "Week 1 \[em] Thursday April 1"
.ALX a ()
.LI
Finish
.V= a-simple/ .
.ALX 1 () "" 0
.LI
.V= derivation-factorial 
\[em]
whowing tail vs non-atil call formula derivations.
.LI
.V= stack-tail-usage.scm
\[em]
program using small stack space with tail recursion
but blowing up stack without tail calls.
.LE
.LI
.V= Examples/b-arith
\[em]
examples showing interaction with the command line,
hash-bang
.=V ( #! )
scripts,
and other examples.
.if n .sp
.LI
.V= asg1-scheme-mbir
specifications.
Writing an interpreter in Scheme for a small mini-basic language.
.LI
.V= code/mbir.scm
\[em]
brief overview of the starter code and introduction to
interpretation.
.LE
.HHH "Week 2 \[em] Tuesday April 6"
.ALX a ()
.LI
.V= Examples/c-evalexpr
\[em] examples related to evaluating expressions and scanning
for labels.
.ALX 1 () "" 0
.LI
.V= euler.scm
\[em]
simple examples of using built-in 
.V= eval
function to evaluate lists as expressions.
.LI
.V= simple-eval.scm
\[em]
hand-coded simple evaluator of expressions.
.LI
.V= evalexpr.scm
\[em]
hand-coded evaluator of expressions with operators and
variables stored in hash tables.
.LI
.V= hashexample.scm
\[em]
use of hash tables for storing infomration.
.LI
.V= labelhash.scm
\[em]
scanning a program list and identifying labels.
.LI
.V= readnums.scm
\[em]
reading numbers and detecting non-numbers and end of file.
.LE
.LI
.V= misc-cons-lists.d/
\[em]
Simple diagram of some node configurations.
.V= picture-21-let-if
contains a diagram of the 
.V= mbir
program structure.
.LI
.V= mbir.scm
\[em]
detailed dissection of the starter code for the interpreter.
.LE
.HHH "Week 2 \[em] Thursday April 8"
.ALX a ()
.LI
.V= Lecture-notes/scheme-1-language.pdf
\[em]
notes on Scheme made from Dybvig's text
(p.\~4\[en]13).
.LI
Numerous online examples.
.LE
.HHH "Week 3 \[em] Tuesday April 13"
.ALX a ()
.LI
.V= Lecture-notes/scheme-1-language.pdf
(p.\~13\[en]end).
.LI
.V= scheme-2-higherorder.pdf
\[em] Scheme higher order functions
(p.\~1\[en]12).
.LE
.HHH "Week 3 \[em] Thursday April 15"
.ALX a ()
.LI
.V= scheme-2-higherorder.pdf
\[em] Scheme higher order functions
(p.\~12\[en]end).
.LI
.V= Examples/d-functions
\[em] wrap up examples with some programs.
.V= mergesort.scm ,
.V= mutualrec.scm ,
.V= facfun.scm ,
.V= quine.scm
.LI
.V= Lecture-notes/ocaml-1-notes.pdf
(p.\~1\[en]2),
plus numerous online examples.
Introduction to Ocaml.
.LE
.HHH "Week 4 \[em] Tuesday April 20"
.ALX a ()
.LI
.V= Examples/a-simple
.ALX 1 () "" 0
.LI
.V= hello.ml ,
.V= helloworld.ml
.LI
.V= argv.ml
\[em] access to the command line
.LI
.V= epsilon.ml
\[em] showing 1 + \[*e] \[==] 1
.LI
.V= factorial.ml ,
.V= fibonacci.ml
\[em] repeat of examples from Scheme tail call and tail recursions 
discussion.
.LI
.V= length.ml
\[em] another example of internal function with tail recursion
.LE
.LI
.V= Examples/b-evalexpr
.ALX 1 () "" 0
.LI
.V= eval1-simple.ml ,
.V= eval2-symbols.ml
\[em] examples of recursive evaluations of expressions,
with and without a symbol table.
.LI
.V= find.ml
\[em]
example of type
.V= "\&'a option"
for returning an object that might not exist
.LE
.LI
Assignment 2 specifications
.LI
.V= asg2/code
.ALX 1 () "" 0
.LI
.V= absyn.mli
\[em] abstract syntax of the interpreter
.LI
.V= parser.mly ,
.V= scanner.mll
\[em] brief overview of parser and scanner (provided,
not written by students).
.LI
.V= main.ml
\[em] main function calling interpreter
.LE
.LE
.HHH "Week 4 \[em] Thursday April 22"
.ALX a ()
.LI
.V= asg2/code
\[em] finish discussion from last lecture.
.ALX a () "" 0
.LI
.V= interp.{mli,ml}
\[em] extensive discussion of interpreter,
where students do the majority of coding for this project.
.LI
.V= tables.{mli,ml}
\[em]
variable and function tables for maintaining data.
.LI
.V= dumper.{mli,ml}
\[em] data dumper and stringification functions for absyn.
.LI
.V= etc.{mli,ml}
\[em] miscellaneous other functions.
.LE
.LI
.V= Examples/b-evalexpr
.ALX 1 () "" 0
.LI
.V= find-opt-exn.ml
\[em] function for searching a list.
Type
.V= "\&'a option" .
.LI
.V= hashexample.ml
\[em] use of
.V= Hashtbl.find
and
.V= Hashtbl.find_opt 
.LI
.V= readnumber.ml
\[em] scanning input for individual numbers from stdin.
.LE
.LI
.V= Examples/c-functions
\[em] brief look during remaining lecture time
.LE
.HHH "Week 5 \[em] Tuesday April 27"
.ALX a ()
.LI
.V= Lecture-notes/ocaml-1-notes.pdf
\[em] review.
.LI
.V= Examples/c-functions
\[em] miscellaneous functions showing more Ocaml style\(::
.ALX 1 () "" 0
.LI
.V= ackermann.ml
\[em] test of computational complexity
.LI
.V= complex-nrs.ml
\[em] module
.V= Complex
and
.V= float
numbers
.LI
.V= exponent.ml
\[em] efficient integer exponent computation
.LI
.V= mergesort.ml
\[em] polymorphic efficient sorting of a list
.LI
.V= odd-even.ml
\[em] mututally recursive functions
.LE
.LI
.V= Examples/x86-64-code
\[em] generated x86-64 code showing how compilers eliminate
tail recursion and rewrite as loops.
Source code in Ocaml and C.
.ALX 1 () "" 0
.LI
.V= boolconst.ml.s ,
.V= boolvar.ml.s
\[em] constant propagation to eliminate a boolean test always false.
.LI
.V= length.ml.s ,
.V= facrec.c.s ,
.V= factorial.ml.s
\[em] tail recursive functions implemented as loops
by the code generator.
.LE
.LE
.HHH "Week 5 \[em] Thursday April 29"
.ALX a ()
.LI
.V= Lecture-notes/ocaml-2-higherorder.pdf
\[em] higher-order functions in Ocaml.
.LI
.V= Examples/d-higherorder
\[em] examples of higher-order functions in Ocaml.
.ALX 1 () "" 0
.LI
.V= p1-uncurry.ml
\[em] functions
.V= curry
and
.V= uncurry
.LI
.V= p2-apply.ml
\[em] appliction of function argument to other arguments.
.LI
.V= p3-foldl.ml
\[em] functions written directly using tail recursion,
and functions written as arguments to fold left\(::
.V= sum ,
.V= length ,
.V= reverse ,
.V= member .
.LI
.V= p3-foldl.ml
\[em] 
.V= reduce ,
exception producing folding, e.g.,
.V= find_minimum
using 
.V= failwith
and returning an
.V= "\&'a option" .
.LI
.V= p4-foldr.ml
\[em] fold right functions that can not be written tail
recursively,
implementation using direct recursion and as a parameter to
fold right\(::
.V= map ,
.V= filter ,
.V= append .
.LI
.V= p5-zip.ml
\[em] merging and splitting lists\(::
.V= unzip ,
.V= zip ,
.V= zipwith ,
.V= inner_product .
.LE
.LE
.HHH "Week 6 \[em] Tuesday May 4"
.ALX a ()
.LI
.V= Examples/a-trivial.d
.ALX 1 () "" 0
.LI
.V= hello.st ,
.V= usage.st ,
.V= echoargs.st ,
.V= showargv.st
\[em] trivial examples involving command line.
.LI
.V= arithmetic.st ,
.V= divide.st ,
.V= dictionary.st ,
.V= fns-radix.st ,
.V= intsort.st
\[em] simple examples showing arithmetic and some 
library data structures.
.LI
.V= collatz-block.st ,
.V= collatz-class.st
\[em] coding examples\(::
blocks and a simple class.
.LE
.LI
.V= Examples/b-simple.d
\[em] slightly more advanced examples.
.ALX 1 () "" 0
.LI
.V= arraysum.st ,
.V= ashex.st ,
.V= isgraph.st
\[em] extending a class on the fly with new methods.
.LI
.V= perform.st
\[em] use of keyword method
.V= perform: 
and
.V= perform:with:
as an analog to a functional language's
.V= apply
function.
.LI
.V= sillypet.st
\[em] simple example of class inheritance of methods,
dynamic typing,  and
``duck typing''.
.LI
.V= simple-eval.st
\[em]
example of a numeric and expression class with inheritance,
including
.V= value ,
.V= printOn: ,
and
.V= perform:with:\&
methods.
.LI
.V= filein.st ,
.V= parseargs.st ,
.V= priority.st ,
.V= string.st ,
.V= terminalecho.st
\[em] miscellaneous other simple examples.
.LE
.LE
.HHH "Week 6 \[em] Thursday May 6"
.ALX a ()
.LI
.LE
.HHH "Week 7 \[em] Tuesday May 11"
.ALX a ()
.LI
Midterm Examination.
.LE
.HHH "Week 7 \[em] Thursday May 13"
.ALX a ()
.LI
.LE
.HHH "Week 8 \[em] Tuesday May 18"
.ALX a ()
.LI
.LE
.HHH "Week 8 \[em] Thursday May 20"
.ALX a ()
.LI
.LE
.HHH "Week 9 \[em] Tuesday May 25"
.ALX a ()
.LI
.LE
.HHH "Week 9 \[em] Thursday May 27"
.ALX a ()
.LI
.LE
.HHH "Week 10 \[em] Tuesday June 1"
.ALX a ()
.LI
.LE
.HHH "Week 10 \[em] Thursday June 3"
.ALX a ()
.LI
.LE
.DE
