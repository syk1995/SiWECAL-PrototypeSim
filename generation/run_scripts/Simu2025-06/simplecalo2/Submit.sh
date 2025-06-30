pwd=$PWD
Particle=e-
CONF=CONF0
ScriptPath=/home/llr/ilc/shi/code/SiWECAL-Prototype/generation/run_scripts/Simu2025-06
OutDIR=/data_ilc/flc/shi/SiWECAL-Prototype/Simu2025-06/${CONF}/${Particle}/MC
compactFile=${ScriptPath}/simplecalo2/compact/${CONF}.xml
env=${ScriptPath}/env.sh
SubmitPath=$PWD/Submit
rm -r ${SubmitPath}
mkdir -p ${SubmitPath}
EventNumber=5000
Energy=(0.05 0.1 0.15 0.2 0.25 0.5 0.75 1.0 2.0 5.0 10.0 20.0 30.0 40.0 50.0 60.0)
#Energy=(20.0)

for E in "${Energy[@]}"
do
    echo "Submitting jobs for energy: $E GeV"
    mkdir -p ${SubmitPath}/${E}GeV
    old_py=${ScriptPath}/simplecalo2/sc2SteeringFile.py
    new_py=${SubmitPath}/${E}GeV/sc2SteeringFile.py
    submit=${SubmitPath}/${E}GeV/run.sh
    outputFile=${OutDIR}/${E}GeV.root

    cp ${old_py} ${new_py}

    sed -i "s|SIM.compactFile *= *.*|SIM.compactFile = \"${compactFile}\"|" ${new_py}
    sed -i "s|SIM.outputFile *= *.*|SIM.outputFile = \"${outputFile}\"|" ${new_py}
    sed -i "s|SIM.numberOfEvents *= *.*|SIM.numberOfEvents = ${EventNumber}|" ${new_py}
    sed -i "s|SIM.gun.energy *= *.*|SIM.gun.energy = ${E}*GeV|" ${new_py}

    cat <<EOF > ${submit}
#!/bin/bash
hostname
. ${env}
ddsim --steeringFile ${new_py}
EOF
    chmod +x ${submit}
    cd ${SubmitPath}/${E}GeV
    t3submit -singleout ${submit} 
done
cd ${pwd}