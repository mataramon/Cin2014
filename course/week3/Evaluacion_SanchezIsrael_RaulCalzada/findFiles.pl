#!/usr/bin/perl

use strict;
use Getopt::Long;

my %Arg = ();

Getopt::Long::GetOptions ( \%Arg,
	"letter:s" ) 
		or die("Error in command line arguments\n");

if( !exists $Arg{letter} ) {
	printf STDERR "Falta argumento\n" ;
	exit 1;
} 

my $LetterRE = "$Arg{letter}";
my @AllResul = `find -iname '$LetterRE\*'`;
print "@AllResul";
	