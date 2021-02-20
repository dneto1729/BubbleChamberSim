# Builds the bubble__materials_(configuration).txt file
# Usage ./materials.py config.dat

from gemc_api_materials import *

def define_materials(configuration):
    # C3F8 density from https://detector-cooling.web.cern.ch/data/C3F8_Properties.pdf
    C3F8 = MyMaterial(
        name="C3F8",
        description="Chamber active fluid material",
        density="1.35", # g/cm^3 
        ncomponents="2",
        components="C 3 F 8")
    print_mat(configuration, C3F8)
    
    # Mineral oil 
    MineralOil = MyMaterial(
        name="MineralOil",
        description="Bubble Cell Oil",
        density="0.83", #g/cm^3
        ncomponents="2",
        components="G4_H 13.9*perCent G4_C 86.1*perCent")
    print_mat(configuration, MineralOil)