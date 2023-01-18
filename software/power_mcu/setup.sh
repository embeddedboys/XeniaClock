#!/bin/bash

#O#################################O#
#     Setup script for PowerMCU     #
#                                   #
#O#################################O#

WORKDIR=$(pwd)
echo "=== working dir is ${WORKDIR} ==="

BIN_DIR=~/.local/bin

do_setup() {
    mkdir -p ${BIN_DIR}
    cd ${WORKDIR}/tools

    echo "=== Installing tools to ~/.local/bin ..."

    # programmer for STC series mcu
    echo "=== 1. Installing stc8gprog ..."
    if [ ! -d "stc8prog" ]; then
        git clone -q https://github.com/IOsetting/stc8prog.git stc8prog
    fi
    cd stc8prog && make clean && make && chmod +x stc8prog  && cp stc8prog ${BIN_DIR} && ls ${BIN_DIR}/stc8prog

    # Other tools
    echo "=== 2. Installing another tools ..."

    echo "=== Install work done."

    echo "=== Remember check this target path in you \$PATH"

    # check if ${BIN_DIR} in $PATH
    if [ ! $(which stc8prog) ]; then
        echo "=== Appending ${BIN_DIR} to your \$PATH"
        export PATH=$PATH:${BIN_DIR}
    else
        echo "=== ${BIN_DIR} already exists in your \$PATH"
    fi

    cd ${WORKDIR}
}

do_setup
