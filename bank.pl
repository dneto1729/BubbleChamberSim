#!/usr/bin/perl -w

use strict;
use lib ("$ENV{GEMC}/api/perl");
#use lib ("$ENV{GEMC}/io");
use utils;
use bank;

use strict;
use warnings;

# Help Message
sub help()
{
    print "\n Usage: \n";
    print "   bank.pl <configuration filename>\n";
    print "   Will create the bubble bank\n";
    print "   Note: The passport and .visa files must be present to connect to MYSQL. \n\n";
    exit;
}

# Make sure the argument list is correct
if( scalar @ARGV != 1)
{
    help();
    exit;
}

# Loading configuration file and paramters
our %configuration = load_configuration($ARGV[0]);


# Variable Type is two chars.
# The first char:
#  R for raw integrated variables
#  D for dgt integrated variables
#  S for raw step by step variables
#  M for digitized multi-hit variables
#  V for voltage(time) variables
#
# The second char:
# i for integers
# d for doubles

my $bankId   = 2400;
my $bankname = "bubble";

sub define_bank
{	
    # uploading the hit definition
    insert_bank_variable(\%configuration, $bankname, "bankid", $bankId, "Di", "$bankname bank ID");
    insert_bank_variable(\%configuration, $bankname, "detId",       1,  "Di", "paddle number");
    insert_bank_variable(\%configuration, $bankname, "kinE",        2,  "Dd", "Kinetic Energy");
    insert_bank_variable(\%configuration, $bankname, "pid",         3,  "Di", "particle id");
    insert_bank_variable(\%configuration, $bankname, "trackE",      6,  "Dd", "Total energy of the FP");    
    insert_bank_variable(\%configuration, $bankname, "avg_x",       8,  "Dd", "Avg x pos global in mm");
    insert_bank_variable(\%configuration, $bankname, "avg_y",       9,  "Dd", "Avg y pos global in mm");
    insert_bank_variable(\%configuration, $bankname, "px",         14,  "Dd", "x component of momentum of the FP (in MeV)");
    insert_bank_variable(\%configuration, $bankname, "py",         15,  "Dd", "y component of momentum of the FP");
    insert_bank_variable(\%configuration, $bankname, "pz",         16,  "Dd", "z component of momentum of the FP");    
    insert_bank_variable(\%configuration, $bankname, "hitn",       99,  "Di", "hit number");
}

define_bank();

1;
