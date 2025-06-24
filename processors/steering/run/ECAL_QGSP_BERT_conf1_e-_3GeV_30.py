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
read.Files = ["/data_ilc/flc/jimenez/simulations/TB2022-03/CONF1/lcio/ECAL_QGSP_BERT_conf1_e-_3GeV_30.slcio"]
algList.append(read)

MyLCIOOutputProcessor = MarlinProcessorWrapper("MyLCIOOutputProcessor")
MyLCIOOutputProcessor.OutputLevel = DEBUG
MyLCIOOutputProcessor.ProcessorType = "LCIOOutputProcessor"
MyLCIOOutputProcessor.Parameters = {
                                    "LCIOOutputFile": ["/grid_mnt/data__DATA/data.polcalice/data/flc/shi/SandBox/ECAL_QGSP_BERT_conf1_e-_3GeV_30.slcio"],
                                    "LCIOWriteMode": ["WRITE_NEW"]
                                    }

SiWECALShaping = MarlinProcessorWrapper("SiWECALShaping")
SiWECALShaping.OutputLevel = DEBUG
SiWECALShaping.ProcessorType = "ShapingProcessor"
SiWECALShaping.Parameters = {
                             "FixedPosZ": ["7.625", "22.625", "37.55", "52.55", "67.46", "82.46", "97.46", "112.55", "127.55", "142.55", "157.55", "172.46", "187.46", "202.46", "217.46"],
                             "Input_Collections": ["SiEcalCollection"],
                             "MIP2GeVFactors": ["0.0001968", "0.0001968", "0.0001494", "0.0001494", "0.0000938", "0.0000938", "0.0000938", "0.0001494", "0.0001494", "0.0001494", "0.0001494", "0.0000938", "0.0000938", "0.0000938", "0.0000938"],
                             "Output_Collections": ["ShapedSiEcalCollection"],
                             "ShapingProcessor_AuxFilename": ["shaped_aux.root"],
                             "ShapingProcessor_FSNoise": ["0.083333"],
                             "ShapingProcessor_MIPThreshold": ["0.5"],
                             "ShapingProcessor_SSNoise": ["0.05"],
                             "ShapingProcessor_bwF": ["0.5"],
                             "ShapingProcessor_bwI": ["0.5"],
                             "ShapingProcessor_bwS": ["5"],
                             "ShapingProcessor_delay": ["160"],
                             "ShapingProcessor_filterNoise": ["true"],
                             "ShapingProcessor_nbinsF": ["400"],
                             "ShapingProcessor_nbinsI": ["400"],
                             "ShapingProcessor_nbinsS": ["100"],
                             "ShapingProcessor_useHistInput": ["true"],
                             "WriteRootfile": ["true"]
                             }

algList.append(SiWECALShaping)
algList.append(MyLCIOOutputProcessor)

from Configurables import ApplicationMgr
ApplicationMgr( TopAlg = algList,
                EvtSel = 'NONE',
                EvtMax   = 10,
                ExtSvc = [evtsvc],
                OutputLevel=DEBUG
              )


