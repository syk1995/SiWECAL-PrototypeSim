#!/bin/bash

pwd=$PWD
Particle=gamma
GEO=CONF4
CONF=Train
ScriptPath=/home/llr/ilc/shi/code/SiWECAL-Prototype/generation/run_scripts/Simu2025-06
OutDIR=/data_ilc/flc/shi/SiWECAL-Prototype/Simu2025-06/${GEO}/${Particle}/${CONF}/MC/Uniform
compactFile=${ScriptPath}/simplecalo2/compact/${GEO}.xml
env=${ScriptPath}/env.sh
SubmitPath=$PWD/Submit_${CONF}_Uniform
#Energy=(0 70)
Energy=(0 15)

rm -rf ${SubmitPath}
mkdir -p ${SubmitPath}
mkdir -p ${OutDIR}

NumJobs=50
EventsPerEnergy=2000

for i in $(seq 1 ${NumJobs}); do
    JobDir=${SubmitPath}/Job${i}
    mkdir -p ${JobDir}
    JobScript=${JobDir}/run.sh
    echo "#!/bin/bash" > ${JobScript}
    echo ". ${env}" >> ${JobScript}
    SteeringPy=${JobDir}/sc2SteeringFile_uniform_${i}.py
    cp ${ScriptPath}/simplecalo2/UniformSteeringFile.py ${SteeringPy}
    outFile=${OutDIR}/${Energy[0]}_${Energy[1]}GeV_${i}.root

    sed -i "s|SIM.compactFile *= *.*|SIM.compactFile = \"${compactFile}\"|" ${SteeringPy}
    sed -i "s|SIM.outputFile *= *.*|SIM.outputFile = \"${outFile}\"|" ${SteeringPy}
    sed -i "s|SIM.numberOfEvents *= *.*|SIM.numberOfEvents = ${EventsPerEnergy}|" ${SteeringPy}
    sed -i "s|SIM.gun.particle *= *.*|SIM.gun.particle = \"${Particle}\"|" ${SteeringPy}
    sed -i "s|SIM.gun.momentumMin *= *.*|SIM.gun.momentumMin = \"${Energy[0]}*GeV\"|" ${SteeringPy}
    sed -i "s|SIM.gun.momentumMax *= *.*|SIM.gun.momentumMax = \"${Energy[1]}*GeV\"|" ${SteeringPy}
    echo "ddsim --steeringFile ${SteeringPy}" >> ${JobScript}

    chmod +x ${JobScript}
    cd ${JobDir}
    t3submit -singleout ${JobScript}
done


cd ${pwd}
echo "Submitted ${NumJobs} jobs, each generating separate files for all selected energy points."
