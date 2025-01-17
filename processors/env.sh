Processor_PATH=/grid_mnt/vol_home/llr/ilc/shi/code/SiWECAL-Sim/processors
source /home/llr/ilc/shi/key4hep/env.sh
#source /cvmfs/ilc.desy.de/sw/x86_64_gcc82_centos7/v02-02-03/init_ilcsoft.sh
export MARLIN_DLL=${Processor_PATH}/lib/libDigitization.so:$MARLIN_DLL
