#!/usr/bin/perl
# $Id: edit-sfile.perl,v 1.1 2021-04-01 00:52:49-07 - - $

#
# edit-sfile - edit an asm .s file
#
# Usage: edit-sfile sfile srcfile
#
# Edits an sfile.s removing directives, then adding the
# original source file at the beginning.
#

$0 =~ s|.*/||;
use strict;
use warnings;

my @directives = qw (

   \.align
   \.byte
   \.cfi_
   \.data$
   \.file
   \.globl
   \.ident
   \.long
   \.p2align
   \.quad
   \.section
   \.size
   \.space
   \.text$
   \.type
   \.word

);

my @suffixes = qw (
   _begin:
   _end:
);

sub stop {
   print STDERR "@_\n";
   exit 1
}

stop "Usage: $0 sfile.s srcfile\n" unless @ARGV == 2;
my ($sfilename, $srcfilename) = @ARGV;

sub charcount {
   my $sum;
   $sum += length $_ for @_;
   return $sum;
}

open my $file, "<$sfilename" or stop "$0: $sfilename: $!\n";
my @contents = <$file>;
close $file;

open $file, "<$srcfilename" or stop "$0: $srcfilename: $!\n";
my @source = <$file>;
close $file;

my $oldchars = charcount @contents;
my $oldlines = @contents;
my @output;
MAIN: for my $line (@contents) {
   for my $directive (@directives) {
      next MAIN if $line =~ m/^\s+$directive\s+/;
   }
   for my $suffix (@suffixes) {
      next MAIN if $line =~ m/$suffix$/;
   }
   next MAIN if $line =~ m/^\s+\.cfi_/;
   $line =~ s|/\*.*?\*/||;
   next MAIN if $line =~ m/^\s*$/;
   push @output, $line;
}
my $newchars = charcount @output;
my $newlines = @output;

open $file, ">$sfilename" or warn" $0: $sfilename: $!\n" and next;
print $file ".... $_" for @source;
print $file @output;
close $file;
print "$0: $sfilename: $oldlines $oldchars => $newlines $newchars\n";

