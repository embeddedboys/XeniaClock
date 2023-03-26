#!/bin/bash

INTERFACE=jlink.cfg
TARGET=rp2040.cfg
ADAPTER_SPEED=100000

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

sudo openocd -f interface/${INTERFACE}     \
             -c "transport select swd"  \
             -f target/${TARGET}      \
             -c "adapter speed ${ADAPTER_SPEED}"   \
             -c "init; program ${1};"   \
             -c "reset; shutdown;"
