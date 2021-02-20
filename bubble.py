#!/usr/bin/env python

# Build the geometry, materials, hit and bank files.
# usage ./bubble.py config.dat

import sys, os
import argparse	# Used to parse the command line arguments
#sys.path.append('/Users/jsgeorge/Documents/gemc/api/python')
from gemc_api_utils import *
#from gemc_api_parameters import *


# This section handles checking for the required configuration filename argument and also provides help and usage messages
desc_str = "   Will create the geometry, materials, bank and hit definitions.\n"
parser = argparse.ArgumentParser(description=desc_str)
parser.add_argument("config_filename", help="The name of the experiment configuration file")
if len(sys.argv)==1:
    parser.print_help()
    sys.exit(1)
args = parser.parse_args()
cfg_file = args.config_filename
print(cfg_file)


# Loading configuration file and paramters
configuration = load_configuration(cfg_file)

# Build bubble__materials_(variation).txt
from materials import *
init_materials_file(configuration)	#  Overwrites any existing materials file and starts with an empty file ready to append materials
define_materials(configuration)

# Build bubble__geometry_(variation).txt
from geometry import *
init_geom_file(configuration)	#  Overwrites any existing geometry file and starts with an empty file ready to append detectors
makeGeometry(configuration)

# Build bubble__hit_(variation).txt
from hit import *
init_hits_file(configuration)
define_hit(configuration)

# Build bubble__bank.txt
from bank import *
init_bank_file(configuration)
define_bank(configuration)
