my $s = <STDIN>;
while ($s =~ m{\(([^()]*)\)}o) {
    my $a = $1;
    my $ra = join '', reverse(split '', $1);
    $s =~ s/\($a\)/$a$ra/;
}
print $s;
