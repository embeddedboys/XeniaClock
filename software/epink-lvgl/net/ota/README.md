OTA
====

Detail
-------

This function is used to  download upgrade package
from server, the server probably is github or gitlab etc.

Then use the flash tools in pico-sdk reburn sectors on flash
and invoke a reboot ops get into the new program.

This function also used to upgrade program in sub
MCU(on power supply board), when the update package is download
finished, invoke mcu self upgrade logic.
