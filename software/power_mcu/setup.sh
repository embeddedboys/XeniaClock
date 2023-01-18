#!/bin/bash

#O#################################O#
#     Setup script for PowerMCU     #
#                                   #
#O#################################O#


do_setup() {
    echo "Installing tools to ~/.local/bin ..."
    
    # programmer for STC series mcu
    echo "1. Installing stc8gprog ..."
    cp tools/stc8prog ~/.local/bin
    
    # Other tools
    
    echo "Remember check this target path in you \$PATH"
}

do_setup