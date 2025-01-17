#!bin/bash
DATA_PATH=/grid_mnt/data__DATA/data.polcalice/data/flc/shi
DATA_NAME=ECAL_QGSP_BERT_conf1_e-_3GeV_30
template=../steering/templates/Shaping_TB2022-03.xml
output_filename=../steering/run/ECAL_QGSP_BERT_conf1_e-_3GeV_30.xml
LCIOInputFiles=$DATA_PATH/SandBox/$DATA_NAME.slcio
LCIOOutputFile=$DATA_PATH/SandBox/$DATA_NAME.slcio

./prepare_Shaping.py --template $template --output_filename $output_filename --LCIOInputFiles /data_ilc/flc/jimenez/simulations/TB2022-03/CONF1/lcio/ECAL_QGSP_BERT_conf1_e-_3GeV_30.slcio --LCIOOutputFile $LCIOOutputFile --MaxRecordNumber 1000
##      --LCIOOutputFile /data_ilc/flc/jimenez/simulations/TB2022-03/CONF1/lcio/ECAL_QGSP_BERT_conf1_e-_3GeV_30_shaped.slcio