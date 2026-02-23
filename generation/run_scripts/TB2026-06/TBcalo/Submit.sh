#!/bin/bash

pwd=$PWD
Particle=gamma
GEO=CONF4
CONF=Validate
ScriptPath=/home/llr/ilc/shi/code/SiWECAL-Prototype/generation/run_scripts/Simu2025-06
OutDIR=/data_ilc/flc/shi/SiWECAL-Prototype/Simu2025-06/${GEO}/${Particle}/${CONF}/MC
compactFile=${ScriptPath}/simplecalo2/compact/${GEO}.xml
env=${ScriptPath}/env.sh
SubmitPath=$PWD/Submit_${CONF}

# 清理旧目录
rm -rf ${SubmitPath}
mkdir -p ${SubmitPath}
mkdir -p ${OutDIR}

# 能量点定义
Energy_train=(0.5 1.5 2.5 3.5 4.5 5.5 6.5 7.5 8.5 9.5 10.5 15 25 35 45 55 65)
#Energy_val=(0.05 0.1 0.15 0.2 0.25 0.5 0.75 1.0 2.0 5.0 10.0 20.0 30.0 40.0 50.0 60.0)
Energy_val=(0.05 0.1 0.15 0.2 0.25 0.5 0.75 1.0 2.0 5.0 10.0)
# 选择使用哪一组能量点
# 默认使用训练集，可快速切换为验证集只需修改这一行
#Energy=("${Energy_train[@]}")
Energy=("${Energy_val[@]}")   # <-- 快速切换到验证集

NumJobs=10
EventsPerEnergy=5000

# 生成作业
for i in $(seq 1 ${NumJobs}); do
    JobDir=${SubmitPath}/Job${i}
    mkdir -p ${JobDir}
    JobScript=${JobDir}/run.sh

    echo "#!/bin/bash" > ${JobScript}
    echo ". ${env}" >> ${JobScript}

    # 循环每个能量点生成独立 steering 文件
    for E in "${Energy[@]}"; do
        SteeringPy=${JobDir}/sc2SteeringFile_${E}GeV.py
        cp ${ScriptPath}/simplecalo2/sc2SteeringFile.py ${SteeringPy}

        outFile=${OutDIR}/${E}GeV_${i}.root

        # 修改 steering 文件参数
        sed -i "s|SIM.compactFile *= *.*|SIM.compactFile = \"${compactFile}\"|" ${SteeringPy}
        sed -i "s|SIM.outputFile *= *.*|SIM.outputFile = \"${outFile}\"|" ${SteeringPy}
        sed -i "s|SIM.numberOfEvents *= *.*|SIM.numberOfEvents = ${EventsPerEnergy}|" ${SteeringPy}
        sed -i "s|SIM.gun.energy *= *.*|SIM.gun.energy = ${E}*GeV|" ${SteeringPy}
        sed -i "s|SIM.gun.particle *= *.*|SIM.gun.particle = \"${Particle}\"|" ${SteeringPy}

        # 添加执行命令到作业脚本
        echo "ddsim --steeringFile ${SteeringPy}" >> ${JobScript}
    done

    chmod +x ${JobScript}

    # 提交作业
    cd ${JobDir}
    t3submit -singleout ${JobScript}
done

cd ${pwd}
echo "Submitted ${NumJobs} jobs, each generating separate files for all selected energy points."
