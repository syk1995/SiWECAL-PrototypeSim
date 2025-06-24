pwd=$PWD
Simu_DIR=/grid_mnt/vol_home/llr/ilc/shi/code/SiWECAL-Prototype/generation/run_scripts/Simu2025-06
source /cvmfs/sw.hsf.org/key4hep/setup.sh -r 2025-05-29
source /home/llr/ilc/shi/key4hep/env.sh
echo "root version"
which root
cd $Simu_DIR/build
target_path="/cvmfs/sw.hsf.org/key4hep/releases/2025-05-29/x86_64-almalinux9-gcc14.2.0-opt/dd4hep/1.32-x2e5mf/lib"
if [[ ":$LD_LIBRARY_PATH:" != *":$target_path:"* ]]; then
    export LD_LIBRARY_PATH="$target_path:$LD_LIBRARY_PATH"
    echo "Added $target_path to LD_LIBRARY_PATH"
else
    echo "Path already in LD_LIBRARY_PATH"
fi
echo "k4 local repo"
k4_local_repo .
cd $pwd
