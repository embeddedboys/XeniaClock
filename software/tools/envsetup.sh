#!/bin/bash

CWD=`pwd`

# global variables
export NCPU=$(grep -c processor /proc/cpuinfo)
export CWD=$(pwd)
export RED_COLOR='\E[1;31m'
export GREEN_COLOR='\E[1;32m'
export YELOW_COLOR='\E[1;33m'
export BLUE_COLOR='\E[1;34m'
export PINK='\E[1;35m'
export RES='\E[0m'

function echo_debug() {
    echo -e "${BLUE_COLOR} [ $(date +"%H:%M:%S") ]: $1 ${RES}"
}
export -f echo_debug


echo "Setting up environment..."
export ARCH=arm
export PICO_SDK_PATH=$CWD/pico-sdk
export PATH=$PATH:$CWD/tools

cd tools
ln -sf daplink-reset.sh daplink-reset
chmod +x daplink-reset

ln -sf daplink-program.sh daplink-program
chmod +x daplink-program
cd -
