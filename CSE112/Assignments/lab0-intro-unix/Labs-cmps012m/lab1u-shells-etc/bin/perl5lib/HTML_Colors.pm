#!/usr/bin/perl
# $Id: HTML_Colors.pm,v 1.10 2021-04-14 08:23:25-07 - - $

package HTML_Colors;

require Exporter;
@ISA = qw (Exporter);
@EXPORT = qw (HTML_Colors);

use strict;
use warnings;

my $AMBER = "#FFBF00";
my $GREEN = "#00FF00";
my $LIGHT_GREEN = "#3FFF3F";
my $BRIGHT_GREEN = "7FFF7F";
my $WHITE = "#FFFFFF";

my $MAINTEXT = $GREEN;

my %COLOR = (

   BDR_DATA   => "#00FFFF", # cyan
   BDR_DUE    => "#FFFF00", # yellow
   BDR_EMPTY  => $MAINTEXT, #
   BDR_EXAM   => "#FF0000", # red
   BG_DATA    => "#005F5F", # dark cyan
   BG_DUE     => "#5F5F00", # dark yellow
   BG_EMPTY   => "#000000", # black
   BG_EXAM    => "#5F0000", # dark red
   FG_HOVER   => "#FF0000", # red
   FG_LINK    => "#FFFF00", # yellow
   FG_PLAIN   => $MAINTEXT, # green
   FG_VISITED => "#00FFFF", # cyan

);

sub HTML_Colors() {
   return %COLOR;
}

1;
