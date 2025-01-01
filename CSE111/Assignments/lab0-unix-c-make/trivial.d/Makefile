# $Id: Makefile,v 1.1 2020-10-01 15:41:24-07 - - $

MKFILE      = Makefile
DEPFILE     = ${MKFILE}.dep
NOINCL      = ci clean spotless
NEEDINCL    = ${filter ${NOINCL}, ${MAKECMDGOALS}}
GMAKE       = ${MAKE} --no-print-directory
GPPWARN     = -Wall -Wextra -Werror -Wpedantic -Wshadow -Wold-style-cast
GPPOPTS     = ${GPPWARN} -fdiagnostics-color=never
COMPILECPP  = g++ -g -O0 -std=gnu++17 ${GPPOPTS}
MAKEDEPCPP  = g++ -MM -std=gnu++17 ${GPPOPTS}

CPPHEADER   = hello.h
CPPSOURCE   = hello.cpp main.cpp
ALLCPPSRC   = ${CPPHEADER} ${CPPSOURCE}
OBJECTS     = ${CPPSOURCE:.cpp=.o}
EXECBIN     = hello
OTHERS      = ${MKFILE}
ALLSOURCES  = ${ALLCPPSRC} ${OTHERS}
LISTING     = Listing.ps

all : ${EXECBIN}

${EXECBIN} : ${OBJECTS}
	${COMPILECPP} -o $@ ${OBJECTS}

%.o : %.cpp
	- checksource $<
	- cpplint.py.perl $<
	${COMPILECPP} -c $<

ci : ${ALLSOURCES}
	cid -is ${ALLSOURCES}

clean :
	- rm ${OBJECTS} ${DEPFILE} core test.out files.log

spotless : clean
	- rm ${EXECBIN} ${LISTING} ${LISTING:.ps=.pdf}

test : ${EXECBIN}
	./${EXECBIN} foo bar baz qux

dep : ${ALLCPPSRC}
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEPCPP} ${CPPSOURCE} >>${DEPFILE}

${DEPFILE} : ${MAKEFILE}
	@ touch ${DEPFILE}
	${GMAKE} dep

ifeq (${NEEDINCL}, )
include ${DEPFILE}
endif
