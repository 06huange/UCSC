#!/usr/bin/perl
# $Id: dynamic-scope.perl,v 1.4 2021-03-04 11:08:12-08 - - $

# Perl program with static scoping.

sub display {
   my ($line, $xx, $yy) = @_;
   my @callers;
   for (my $i = 1;; ++$i) {
      my @call = caller ($i);
      last unless @call;
      $call[3] =~ s/main:://;
      unshift @callers, "$call[3]($call[2])";
   }
   print "Line $line x=$xx, y=$yy :@callers\n";
}

local $x = 1;
local $y = 2;

sub foo {
   display __LINE__, $x, $y;
   local $x = 3;
   display __LINE__, $x, $y;
   {
      local $y = 4;
      display __LINE__, $x, $y;
   }
   display __LINE__, $x, $y;
}

sub bar {
   display __LINE__, $x, $y;
   local $y = 5;
   display __LINE__, $x, $y;
   foo();
   display __LINE__, $x, $y;
}

sub main {
   display __LINE__, $x, $y;
   local $x = 6;
   display __LINE__, $x, $y;
   bar();
   display __LINE__, $x, $y;
}

display __LINE__, $x, $y;
main();
display __LINE__, $x, $y;

