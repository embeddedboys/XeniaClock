#!/bin/bash

# source the enviroments
WORKDIR=$(pwd)
echo "working dir is ${WORKDIR}"

BUILDDIR=${WORKDIR}/build

BIN="xenia_clock.elf"

function do_configure() {
    echo "do configuring ..."
    cd .. && source tools/envsetup.sh && cd ${WORKDIR}
}

function do_compile() {
    echo "do compiling ..."
    # if [ ! -d "${WORKDIR}/build" ]; then
    #     mkdir build
    # fi
    mkdir -p ${WORKDIR}/build && cd build
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Release ..
    time make -j

    cd -
}

function do_install() {
    echo "do installing ..."
    cp build/${BIN} .
}

function do_flash() {
    ${WORKDIR}/../tools/dapp ./${BIN}
}

function do_clean() {
    mkdir -p ${WORKDIR}/build && cd build
    make clean
    cd -
}

do_configure
do_compile
do_install

case $1 in

    "-p")
        echo "do a flash job"
        do_flash
        ;;

    "-c")
        echo "do a clean job"
        do_clean
        ;;

esac