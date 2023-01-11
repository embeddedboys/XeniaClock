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
    ls
    cmake .. -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -GNinja
    ninja

    cd -
}

function do_install() {
    echo "do installing ..."
    cp build/${BIN} .
}

function do_flash() {
    ${WORKDIR}/../tools/dapp ./${BIN}
}

do_configure
do_compile
do_install

case $1 in

    "-p")
        echo "do a flash ops"
        do_flash
        ;;

esac