#!/usr/bin/env perl
use strict;

sub main(){
    my ($search_name, $source_file, $out_file, $data_file) = undef, undef, undef,undef;
    $search_name = shift @ARGV or $search_name="PadtsBot101"    ;
    $source_file = shift @ARGV or $source_file="search.cpp";
    $out_file    = shift @ARGV or $out_file   ="search.exe";  
    $data_file   = shift @ARGV or $data_file  ="data.dat"  ;

    my @steps = ("build", "download", "execute");
 
    my %commands = (
        "build"    => "g++ $source_file -o $out_file",
        "download" => "wget 162.243.155.132:3000 -O $data_file",
        "execute"  => "./search.exe $search_name $data_file",
    );
    
    print("Welcome the search test\n");    
    print("Looking for the nearest to $search_name\n");    
    
    foreach my $step  (@steps){
         print "-> $step: $commands{$step}\n";
         my $output = qx($commands{$step});
         print "\n\t\t$output\n\n" if $output; 
    } 
    
}

exit main();

