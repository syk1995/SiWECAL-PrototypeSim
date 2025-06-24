#!/usr/bin/env python3
from DDSim.DD4hepSimulation import  DD4hepSimulation
#from SystemOfUnits import mm, GeV, MeV
from g4units import GeV, mm, MeV

SIM = DD4hepSimulation()

SIM.runType = "run"
# Number of events defined in macro file

SIM.skipNEvents = 0
SIM.outputFile = "/data_ilc/flc/shi/simulations/TB2022-03/CONF0/lcio/ECAL_QGSP_BERT_conf0_e-_3.0GeV_1.edm4hep.root"

#SIM.compactFile = "/home/llr/ilc/shi/code/SiWECAL-Sim/generation/geometry//TB2022-03/ECAL_CONF0.xml"
SIM.compactFile="/cvmfs/sw.hsf.org/key4hep/releases/2024-10-03/x86_64-almalinux9-gcc14.2.0-opt/k4geo/0.21-d5gbnd/share/k4geo/ILD/compact/ILD_l5_v02/ILD_l5_o1_v02.xml"
SIM.dumpSteeringFile = "/grid_mnt/vol_home/llr/ilc/shi/code/SiWECAL-Sim/generation/run_scripts/TB2022-03/steer/dumpSteering.xml"

SIM.field.eps_min = 1*mm
SIM.part.minimalKineticEnergy = 0.3*MeV
SIM.physicsList = "QGSP_BERT"
SIM.enableDetailedShowerMode=True
