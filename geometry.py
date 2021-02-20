# Builds the bubble__geometry_(configuration).txt file
# Usage ./geometry.py config.dat

from gemc_api_geometry import *

def makeGeometry(configuration):
    build_BeamPipe(configuration)
    build_Radiator(configuration)
    build_Collimator(configuration)
    build_BubbleChamberCell(configuration)
    build_PhotonDump(configuration)
    
def build_BeamPipe(configuration):
    # Build beam pipe 
    BeamPipe = MyDetector(
        name="BeamPipe",
        mother="root",
        description="Beam Pipe",
        color="aabbcc",
        type="Polycone",
        dimensions="0.0*deg 360*deg 4*counts 1.7399*cm 1.7399*cm 1.7399*cm 1.7399*cm 3.429*cm 3.429*cm 1.905*cm 1.905*cm 0*cm 1.1176*cm 1.1176*cm 5.4864*cm",
        material="G4_STAINLESS-STEEL",
        rotation="0*deg 0*deg 0*deg",
        pos="0*cm 0*cm -13.1064*cm",
        style="1")
    print_det(configuration, BeamPipe)
    
def build_Radiator(configuration):
    # Build radiator
    Radiator = MyDetector(
        name="Radiator",
        mother="root",
        description="Bubble Radiator",
        color="aaaa44",
        type="Polycone",
        dimensions="0.0*deg 360*deg 4*counts 1.305*cm 1.305*cm 0*cm 0*cm 1.905*cm 1.905*cm 1.905*cm 1.905*cm 0*cm 7.02*cm 7.02*cm 7.62*cm",
        material="G4_Cu",
        rotation="0*deg 0*deg 0*deg",
        pos="0*cm 0*cm -7.62*cm",
        style="1")
    print_det(configuration, Radiator)

    # Build vacuum inside radiator tube  (beam starts in vacuum)
    RadiatorVacuum = MyDetector(
        name="RadiatorVacuum",
        mother="root",
        description="Bubble Radiator Vacuum",
        color="ffffff3",
        type="Tube",
        #                  = 
        dimensions="0*cm  1.305*cm 1.5*inches 0*deg 360*deg",
        material="G4_Galactic",
        rotation="0*deg 0*deg 0*deg",
        pos="0*cm 0*cm -4.41*cm",
        style="1")
    print_det(configuration, RadiatorVacuum)

    # Build flux detector  (detect gammas comming out of radiator)
    RadiatorFlux = MyDetector(
        name="RadiatorFlux",
        mother="root",
        description="Bubble Radiator Flux",
        color="ff0000",
        type="Tube",
        dimensions="0*cm 10*cm 0.1*mm 0*deg 360*deg",
        material="G4_AIR",
        rotation="0*deg 0*deg 0*deg",
        pos="0*cm 0*cm 0.2*cm",
        visible="0",
        sensitivity="bubble",
        hit_type="bubble",
        identifiers="detId manual 1")
    print_det(configuration, RadiatorFlux)
    
def build_Collimator(configuration):
    # Build gamma collimator
    Collimator = MyDetector(
        name="Collimator",
        mother="root",
        description="Bubble Collimator",
        color="ffcc44",
        type="Tube",
        dimensions="0.40005*cm 5.08*cm 7.62*cm 0*deg 360*deg",
        material="G4_Cu",
        rotation="0*deg 0*deg 0*deg",
        pos="0*cm 0*cm 9.12*cm",
        style="1")
    print_det(configuration, Collimator)
    
def build_BubbleChamberCell(configuration):
    # Build bubble chamber
    GlassCell = MyDetector(
        name="GlassCell",
        mother="root",
        description="Bubble Chamber",
        color="aaaaaa4",
        type="Polycone",
        #                 =
        dimensions="0.0*deg 360*deg 4*counts 0*cm 0*cm 0*cm 0*cm 0.6*cm 0.6*cm 1.6*cm 1.6*cm 0*cm 1*cm 2*cm 7.1*cm",
        material="G4_Pyrex_Glass",
        rotation="90*deg 0*deg 0*deg",
        pos="0*cm -4.5*cm 37.6*cm",
        style="1")
    print_det(configuration, GlassCell)

    # Build detection cell (fluid inside bubble cell, detects gammas that reach the cell)
    c3f8cell = MyDetector(
        name="c3f8cell",
        mother="GlassCell",
        description="Bubble Chamber Fluid",
        color="44ffff4",
        type="Polycone",
        #                 = 
        dimensions="0.0*deg 360*deg 4*counts 0*cm 0*cm 0*cm 0*cm 0.5*cm 0.5*cm 1.5*cm 1.5*cm 0.1*cm 1*cm 2*cm 7*cm",
        material="G4_Pyrex_Glass", # testing, change to c3f8 defined in bubble__materials
        rotation="0*deg 0*deg 0*deg",
        pos="0*cm 0*cm 0*cm",
        style="1",
        sensitivity="bubble",
        hit_type="bubble",
        identifiers="detId manual 2")
    print_det(configuration, c3f8cell)
    
def build_PhotonDump(configuration):
    # Build beam dump
    PhotonDump = MyDetector(
        name="PhotonDump",
        mother="root",
        description="Bubble Photon Dump",
        color="eeeeff",
        type="Box",
        dimensions="5.08*cm 5.08*cm 20.32*cm",
        material="G4_Al",
        rotation="0*deg 0*deg 0*deg",
        pos="0*cm 0*cm 100*cm",
        style="1")
    print_det(configuration, PhotonDump)
