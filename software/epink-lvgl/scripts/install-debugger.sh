#!/bin/bash

WORKDIR=$(pwd)
echo ${WORKDIR}

cd .. && source tools/envsetup.sh && cd ${WORKDIR}

echo ${SOFTWARE_PATH}

cd ${SOFTWARE_PATH}

git clone https://github.com/raspberrypi/openocd.git --recursive --branch rp2040 --depth=1

cd openocd

./bootstrap

./configure --enable-cmsis-dap

cd ${WORKDIR}

make -j12