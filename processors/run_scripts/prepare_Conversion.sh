#!bin/bash
DATA_PATH=/grid_mnt/data__DATA/data.polcalice/data/flc/shi
DATA_NAME=bbudsc_3evt_SIM
template=../steering/templates/Conversion.xml
output_filename=../steering/run/Conversion.xml
#LCIOInputFiles=$DATA_PATH/SandBox/$DATA_NAME.slcio
LCIOInputFiles=/data_ilc/flc/jimenez/simulations/TB2022-06/CONF6/lcio/ECAL_QGSP_BERT_conf6_mu-_150GeV_{10..19}.slcio
#ConvAuxFile=/data_ilc/flc/jimenez/simulations/TB2022-06/CONF6/build/ECAL_QGSP_BERT_conf6_mu-_150GeV_5kevt_conversion.root
ConvAuxFile=$DATA_PATH/SandBox/ECAL_QGSP_BERT_conf6_mu-_150GeV_5kevt_conversion.root
OutputBuildFile=$DATA_PATH/SandBox/$DATA_NAME.root

./prepare_Conversion.py --template $template --output_filename $output_filename --LCIOInputFiles $LCIOInputFiles --ConvAuxFile $ConvAuxFile --tb_conf TB2022-06_CONF6 --MIPFitMode 1 --MaxRecordNumber 5000

##      --LCIOInputFiles /data_ilc/flc/jimenez/simulations/TB2022-08/CONF6/lcio/ECAL_QGSP_BERT_conf6_mu-_150GeV_{10..19}.slcio
##      --ConvAuxFile /data_ilc/flc/jimenez/simulations/TB2022-06/CONF6/build/ECAL_QGSP_BERT_conf6_mu-_150GeV_5kevt_conversion.root
##      --tb_conf TB2022-06_CONF6
##      --MipFitMode 1
##      --MaxRecordNumber 5000