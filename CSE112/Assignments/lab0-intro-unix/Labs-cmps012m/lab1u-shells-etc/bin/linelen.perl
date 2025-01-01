#!/usr/bin/perl
# $Id: linelen.perl,v 1.3 2021-04-10 05:08:55-07 - - $

use strict;
use warnings;
$0 =~ s|.*/||;

sub key($) {
   my ($len) = @_;
   my $modulus = 10;
   my $limit = 70;
   $len = int ($len / $modulus) * $modulus;
   if ($len < $limit) {
      return sprintf "%2d..%2d", $len, $len + $modulus - 1;
   }else {
      return "$limit..**";
   }
}

my %lengths;
$lengths{key $_} = 0 for 0..72;

my $linect = 0;
while (my $line = <>) {
   chomp $line;
   ++$lengths{key length $line};
   ++$linect;
}

print "count  length   cumulative\n";
my $total = 0;
for my $key (sort keys %lengths) {
   my $len = $lengths{$key};
   $total += $len;
   printf "%5d  %5s %5d = %3d%%\n",
          $len, $key, $total, $total / $linect * 100;
}

