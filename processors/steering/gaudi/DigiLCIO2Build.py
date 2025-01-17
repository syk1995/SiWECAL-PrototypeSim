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
read.Files = ["input.slcio"]
algList.append(read)

DigiLCIO2BuildConversion = MarlinProcessorWrapper("DigiLCIO2BuildConversion")
DigiLCIO2BuildConversion.OutputLevel = DEBUG
DigiLCIO2BuildConversion.ProcessorType = "DigiLCIO2BuildProcessor"
DigiLCIO2BuildConversion.Parameters = {
                                       "Energy_Conf_Name": ["output.root"],
                                       "FixedPosZ": ["6.225", "21.225", "36.15", "51.15", "66.06", "81.06", "96.06", "111.15", "126.15", "141.15", "156.15", "171.06", "186.06", "201.06", "216.06"],
                                       "Input_Collections": ["ShapedSiEcalCollection"],
                                       "WriteRootfile": ["true"],
                                       "hitType": ["CalorimeterHit"]
                                       }

algList.append(DigiLCIO2BuildConversion)

from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = algList,
                EvtSel = 'NONE',
                EvtMax   = 10,
                ExtSvc = [evtsvc],
                OutputLevel=DEBUG
              )
