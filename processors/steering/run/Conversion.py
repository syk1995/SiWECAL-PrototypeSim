from Gaudi.Configuration import *

from Configurables import LcioEvent, EventDataSvc, MarlinProcessorWrapper
from k4MarlinWrapper.parseConstants import *
algList = []
evtsvc = EventDataSvc()


CONSTANTS = {
}

parseConstants(CONSTANTS)

read = LcioEvent()
read.OutputLevel = DEBUG
read.Files = ["/grid_mnt/data__DATA/data.polcalice/data/flc/shi/SandBox/bbudsc_3evt_SIM.slcio"]
algList.append(read)

SiWECALConversion = MarlinProcessorWrapper("SiWECALConversion")
SiWECALConversion.OutputLevel = DEBUG
SiWECALConversion.ProcessorType = "ConversionProcessor"
SiWECALConversion.Parameters = {
                                "ConvAuxFile": ["output_conv.root"],
                                "Input_Collections": ["SiEcalCollection"],
                                "MIPFitMode": ["fitmode"],
                                "SiThicknesses": ["si_thicknesses"]
                                }

algList.append(SiWECALConversion)

from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = algList,
                EvtSel = 'NONE',
                EvtMax   = 10,
                ExtSvc = [evtsvc],
                OutputLevel=DEBUG
              )
