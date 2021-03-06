#!/usr/bin/perl -w

while (<>) {
    next unless /CAIRO_TEST \((.*),/; # XXX Parse multi-line macro
    push @names, $1;
}

print <<EOD
/* WARNING: Autogenerated file - see make-cairo-test-constructors.pl! */

#include "cairo-test-private.h"

EOD
;
print "extern void _register_$_ (void);\n" foreach (@names);
print "\nvoid\n_cairo_test_runner_register_tests (void)\n{\n";
print "    _register_$_ ();\n" foreach (reverse @names);
print "}\n";
