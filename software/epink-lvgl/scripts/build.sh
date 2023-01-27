#!/bin/bash

# source the enviroments
WORKDIR=$(pwd)
echo "working dir is ${WORKDIR}"

BUILDDIR=${WORKDIR}/dir_build

BIN="xenia_clock.elf"

function do_banner() {
cat << "EOF" >> /dev/tty
__  __          _              ____ _            _
\ \/ /___ _ __ (_) __ _       / ___| | ___   ___| | __
 \  // _ \ '_ \| |/ _` |     | |   | |/ _ \ / __| |/ /
 /  \  __/ | | | | (_| |     | |___| | (_) | (__|   <
/_/\_\___|_| |_|_|\__,_|      \____|_|\___/ \___|_|\_\

EOF

}

function do_usage() {
cat << "EOF" >> /dev/tty

./build.sh [-h|-c|-p]

    If no parameter is provided, will do a normal build process

    -h      print this usage

    -c      do a make clean job

    -p      do a chip flash program job

EOF
}

function do_configure() {
    echo "do configuring ..."
    cd .. && source tools/envsetup.sh && cd ${WORKDIR}
}

function do_compile() {
    echo "do compiling ..."
    # if [ ! -d "${WORKDIR}/build" ]; then
    #     mkdir build
    # fi
    mkdir -p ${BUILDDIR} && cd ${BUILDDIR}
    cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=Release -GNinja ..
    time ninja

    # symol link compile_commands.json on WORKDIR

    ln -sf ${BUILDDIR}/compile_commands.json ${WORKDIR}

    cd -
}

function do_install() {
    echo "do installing ..."
    #cp ${BUILDDIR}/${BIN} .
    ln -sf ${BUILDDIR}/${BIN} ${WORKDIR}
    echo -e "                     =--- size info ---=\n"
    arm-none-eabi-size -G -d ${BIN}
}

function do_flash() {
    ${WORKDIR}/../tools/dapp ./${BIN}
}

function do_clean() {
    mkdir -p ${BUILDDIR} && cd ${BUILDDIR}
    ninja clean
    cd -
}

case $1 in

    "-h")
        echo "Printing Usage ..."
        do_banner
        do_usage
        exit 0
        ;;

    "-p")
        echo "will do a flash job"
        do_banner
        do_flash
        exit 0
        ;;

    "-c")
        echo "do a clean job"
        do_banner
        do_clean
        exit 0
        ;;

esac

do_banner
do_configure
do_compile
do_install

exit 0
