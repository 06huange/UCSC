#!/usr/bin/perl
# $Id: HTML_Colors.test.perl,v 1.2 2020-08-22 13:36:57-07 - - $

use lib "/afs/cats.ucsc.edu/courses/cse110a-wm/bin/perl5lib/";

use HTML_Colors;
my %COLOR = HTML_Colors;

print "$0\n";
printf "%-10s => %s\n", $_, $COLOR{$_} for sort keys %COLOR;

