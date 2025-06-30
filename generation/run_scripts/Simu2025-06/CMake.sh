#source /home/llr/ilc/shi/key4hep/env.sh
source env.sh
rm -r build
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=../install -Wno-dev
make install -j8
k4_local_repo .
cd ..
