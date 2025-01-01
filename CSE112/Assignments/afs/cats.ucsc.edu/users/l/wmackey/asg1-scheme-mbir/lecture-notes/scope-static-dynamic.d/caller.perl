#!/usr/bin/perl
# $Id: caller.perl,v 1.2 2021-03-04 11:08:12-08 - - $

sub display {
   my ($arg) = @_;
   print "$arg: ";
   for (my $i = 1;; ++$i) {
      my @caller = caller ($i);
      last unless @caller;
      $caller[3] =~ s/main:://;
      print "$caller[3]($caller[2]): ";
   }
   print "\n";
}

sub foo {
   display __LINE__;
}

sub bar {
   display __LINE__;
   foo();
   display __LINE__;
}

sub main {
   display __LINE__;
   bar();
   display __LINE__;
}

display __LINE__;
main();
display __LINE__;
