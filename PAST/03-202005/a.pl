chomp(my $a = <STDIN>);
chomp(my $b = <STDIN>);

if ($a eq $b) {print "same\n";}
elsif ($a =~ m"$b"i) {print "case-insensitive\n";}
else {print "different\n";}
