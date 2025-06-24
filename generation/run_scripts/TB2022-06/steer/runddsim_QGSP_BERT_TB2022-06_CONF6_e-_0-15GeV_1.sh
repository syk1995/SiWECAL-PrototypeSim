source /cvmfs/ilc.desy.de/sw/x86_64_gcc82_centos7/v02-02-03//init_ilcsoft.sh
cp -r /grid_mnt/vol_home/llr/ilc/ritzmann/work/SiWECAL-Sim/generation/run_scripts/TB2022-06/steer//runddsim_QGSP_BERT_TB2022-06_CONF6_e-_0-15GeV_1.{py,sh} .
#This is run in /grid_mnt/vol_home/llr/ilc/ritzmann/work/SiWECAL-Sim/generation/run_scripts
ddsim --enableG4GPS --macroFile /grid_mnt/vol_home/llr/ilc/ritzmann/work/SiWECAL-Sim/generation/run_scripts/TB2022-06/macros/e-_0-15GeV_1.mac --steeringFile /grid_mnt/vol_home/llr/ilc/ritzmann/work/SiWECAL-Sim/generation/run_scripts/TB2022-06/steer/runddsim_QGSP_BERT_TB2022-06_CONF6_e-_0-15GeV_1.py
