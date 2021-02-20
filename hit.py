# Builds the bubble__hit_(configuration).txt file
# Usage ./hit.py config.dat

from gemc_api_hit import *

def define_hit(configuration):
    # 
    hit = MyHit(
        name="bubble",
        description="bubble hit definitions",
        identifiers="detId",
        signalThreshold="0.1*KeV",
        timeWindow="0*ns",
        prodThreshold="1*mm",
        maxStep="1*cm",
        delay="50*ns",
        riseTime="5*ns",
        fallTime="8*ns",
        mvToMeV=100,
        pedestal=-20)
    print_hit(configuration, hit)
    
# timeWindow: 0 means “every track”. Anything other than 0 will integrate over time window to define a hit
# prodThreshold: this is minimum distance that secondaries have to travel in order to be created
# maxStep: max step of particles    