#!/bin/bash

sudo openocd -f interface/jlink.cfg -c "transport select swd" -c "adapter speed 10000" -f target/rp2040.cfg  -c "init; program ${1}; reset; shutdown;"
