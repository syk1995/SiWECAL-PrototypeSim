#!/bin/bash
#source /grid_mnt/vol_home/llr/ilc/shi/code/SiWECAL-Sim/generation/run_scripts/env.sh
cat /etc/system-release
g++ -v
#python3 --version
echo $PATH
#cp -r /grid_mnt/vol_home/llr/ilc/shi/code/SiWECAL-Sim/generation/run_scripts/TB2022-03/steer//runddsim_QGSP_BERT_TB2022-03_CONF0_e-_3.0GeV_1.{py,sh} .
#This is run in /grid_mnt/vol_home/llr/ilc/shi/code/SiWECAL-Sim/generation/run_scripts
ddsim --enableG4GPS --macroFile /data_ilc/flc/shi/simulations/TB2022-03/CONF0/lcio//e-_3.0GeV_1.mac --steeringFile /grid_mnt/vol_home/llr/ilc/shi/code/SiWECAL-Sim/generation/run_scripts/TB2022-03/steer/runddsim_QGSP_BERT_TB2022-03_CONF0_e-_3.0GeV_1.py
