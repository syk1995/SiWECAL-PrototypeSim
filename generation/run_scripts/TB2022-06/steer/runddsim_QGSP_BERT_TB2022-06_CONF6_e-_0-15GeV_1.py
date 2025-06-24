from DDSim.DD4hepSimulation import  DD4hepSimulation
#from SystemOfUnits import mm, GeV, MeV
from g4units import GeV, mm, MeV

SIM = DD4hepSimulation()

SIM.runType = "run"
# Number of events defined in macro file

SIM.skipNEvents = 0
SIM.outputFile = "/data_ilc/flc/ritzmann/simulations/TB2022-06/CONF6/lcio/ECAL_QGSP_BERT_conf6_e-_0-15GeV_1.slcio"

SIM.compactFile = "/home/llr/ilc/ritzmann/work/SiWECAL-Sim/generation/geometry//TB2022-06/ECAL_CONF6.xml"
SIM.dumpSteeringFile = "/grid_mnt/vol_home/llr/ilc/ritzmann/work/SiWECAL-Sim/generation/run_scripts/TB2022-06/steer/dumpSteering.xml"

SIM.field.eps_min = 1*mm
SIM.part.minimalKineticEnergy = 0.3*MeV
SIM.physicsList = "QGSP_BERT"
SIM.enableDetailedShowerMode=True