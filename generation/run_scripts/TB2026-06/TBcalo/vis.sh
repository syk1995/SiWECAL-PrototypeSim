source /cvmfs/sw.hsf.org/key4hep/setup.sh
source ../env.sh
ddsim --compactFile compact/CONF3.xml --runType qt --macroFile vis.mac --part.userParticleHandler=''
