#!/bin/bash

OLD_DIR=$PWD
CPP_DIR=$(dirname "$0")
cd $CPP_DIR

unset MARLIN_DLL
#source ./init_ilcsoft.sh
source /cvmfs/sw.hsf.org/key4hep/setup.sh

mkdir -p build
cd build
#cmake -C $ILCSOFT/ILCSoft.cmake -DCMAKE_BUILD_TYPE=Release ..
cmake ..
make install

cd $OLD_DIR
