#!/bin/bash

INTERFACE=cmsis-dap.cfg
TARGET=rp2040.cfg
ADAPTER_SPEED=100000

WORKDIR=$(pwd)

if [ `command -v echo_debug > /dev/null` ]; then
    echo_debug "setting up openocd ..."
else
    cd .. && source tools/envsetup.sh
    cd - >> /dev/null
    echo_debug "setting up openocd ..."
fi

# If openocd is not found, we don't need go further.
if [ ${#OPENOCD_DIR} -ne 0 ]; then
    echo_debug "Setting openocd to $OPENOCD_DIR/src/openocd"
    OPENOCD_BIN=$OPENOCD_DIR/src/openocd
else
    # Use system default openocd.
    echo_debug "Will use system default openocd."
    OPENOCD_BIN=openocd
fi

if [ -z "$1" ]; then
    echo_error "Usage: $0 xxx.elf"
    exit
fi

# Call the openocd script to reset the target.
if [ ${#OPENOCD_DIR} -ne 0 ]; then
sudo ${OPENOCD_BIN} -s ${OPENOCD_DIR}/tcl \
    -f ${OPENOCD_DIR}/tcl/interface/${INTERFACE} \
    -f ${OPENOCD_DIR}/tcl/target/${TARGET} -c \
"
    adapter speed ${ADAPTER_SPEED};
    init;
    program {$1};
    reset;
    shutdown;
"
else
sudo ${OPENOCD_BIN} \
    -f interface/${INTERFACE} \
    -f target/${TARGET} -c \
"
    adapter speed ${ADAPTER_SPEED};
    init;
    program {$1};
    reset;
    shutdown;
"
fi

echo "Done."

cd ${WORKDIR} > /dev/null