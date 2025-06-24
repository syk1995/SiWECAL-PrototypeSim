source /home/llr/ilc/shi/key4hep/env.sh
Scrpit_DIR=/home/llr/ilc/shi/code/SiWECAL-Sim/generation/run_scripts/TB2025-03/Sr90
cd $Scrpit_DIR
ILD_MODEL=/home/llr/ilc/shi/code/SiWECAL-Sim/generation/geometry/TB2025-03/ECAL_CONF0
OUTPUT_DIR=/data_ilc/flc/shi/TB_2025_3/Comission/Sr90/MC
# Defaults
#PARTICLE_TYPE=pi+
PARTICLE_TYPE=Sr90
PARTICLE_ENERGY=100
PARTICLE_MULTIPLICITY=1
N_EVENTS=50
PROD_NAME=${OUTPUT_DIR}/${PARTICLE_TYPE}

run_simulation () {
    if [ "$1" != "" ]; then
        N_EVENTS=$1
    fi
    mkdir -p $PROD_NAME
    outputFile=$PROD_NAME/$PARTICLE_TYPE.edm4hep.root
    # --compactFile $lcgeo_DIR/ILD/compact/$ILD_MODEL/$ILD_MODEL.xml \
    ddsim \
        --steeringFile ddsim_steer.py \
        --compactFile $ILD_MODEL.xml \
        --enableG4GPS \
        --runType run \
        --macroFile Sr90.mac \
        --numberOfEvents=$N_EVENTS \
        --outputFile ${outputFile} \
        --random.seed 1
        2>&1 | tee $PROD_NAME/sim_${PARTICLE_TYPE}.log
        echo $N_EVENTS "produced in" "$outputFile"
    #             --enableDetailedShowerMode  is to have detaille MC tracks in     
}

run_simulation
