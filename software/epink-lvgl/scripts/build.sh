#!/bin/bash

# source the enviroments
WORKDIR=$(pwd)
echo "working dir is ${WORKDIR}"

BUILDDIR=${WORKDIR}/dir_build

BIN="xenia_clock.elf"
UF2="xenia_clock.uf2"

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
    cd .. && source tools/envsetup.sh && cd ${WORKDIR}

    echo_debug "do configuring ..."
    if [ ! -f .config ]; then
        echo_debug "making a default config"
        ARCH=${ARCH} make xeniaclock_defconfig
    else
        echo_debug "user config exists"
    fi
}

function do_compile() {
    echo_debug "do compiling ..."
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
    echo_debug "do installing ..."
    #cp ${BUILDDIR}/${BIN} .
    ln -sf ${BUILDDIR}/${BIN} ${WORKDIR}
    echo -e "                     =--- size info ---=\n"
    arm-none-eabi-size -d ${BIN}
}

function do_flash() {
    echo_debug "do flashning ..."
    time ${WORKDIR}/../tools/dapp ${WORKDIR}/${BIN}
}

function do_flash_uf2() {
    echo_debug "do uf2 flashning ..."
    sudo cp ${BUILDDIR}/${UF2} /media/$USER/RPI-RP2/
}

function do_clean() {
    echo_debug "do cleaning ..."
    mkdir -p ${BUILDDIR} && cd ${BUILDDIR}
    ninja clean
    cd -
}

case $1 in

    "-h")
        echo_debug "Printing Usage ..."
        do_banner
        do_usage
        exit 0
        ;;

    "-p")
        echo_debug "will do a flash job"
        do_banner
        do_flash
        exit 0
        ;;

    "-u")
	echo_debug "will do a uf2 flash job"
	do_banner
	do_flash_uf2
	exit 0
	;;

    "-c")
        echo_debug "do a clean job"
        do_banner
        do_clean
        exit 0
        ;;

    "menuconfig")
        do_configure
        echo_debug "show the menu"
        ARCH=${ARCH} make menuconfig
        ARCH=${ARCH} make
        exit 0
        ;;

esac

do_banner
do_configure
do_compile
do_install

exit 0
