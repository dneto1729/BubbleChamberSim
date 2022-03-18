# Builds the bubble__bank_(configuration).txt file
# Usage ./bank.py config.dat

from gemc_api_bank import *

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

bankId       = 2400
bankname = "bubble"

def define_bank(configuration):

    insert_bank_variable(configuration, bankname, "bankid", bankId, "Di", bankname+" bank ID")
    insert_bank_variable(configuration, bankname, "detId", 1, "Di", "paddle number")
    insert_bank_variable(configuration, bankname, "kinE", 2, "Dd", "Kinetic Energy")
    insert_bank_variable(configuration, bankname, "pid", 3, "Di", "particle id")
    insert_bank_variable(configuration, bankname, "trackE", 6, "Dd", "Kinetic Energy")
    insert_bank_variable(configuration, bankname, "avg_x", 8, "Dd", "Average X position in the global reference system (in mm)")
    insert_bank_variable(configuration, bankname, "avg_y", 9, "Dd", "Average Y position in the global reference system")
    insert_bank_variable(configuration, bankname, "px", 14, "Dd", "x component of momentum of the FP (in MeV)")
    insert_bank_variable(configuration, bankname, "py", 15, "Dd", "y component of momentum of the FP (in MeV)")
    insert_bank_variable(configuration, bankname, "pz", 16, "Dd", "z component of momentum of the FP (in MeV)")
    insert_bank_variable(configuration, bankname, "procID", 25, "Dd", "Process that created the FP")
    insert_bank_variable(configuration, bankname, "hitn", 99, "Di", "hit number")
