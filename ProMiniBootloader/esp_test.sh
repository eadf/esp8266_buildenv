#!/bin/bash

export SDK_BASE=/Users/ead/Develop/workspace-esp/esp-open-sdk/sdk
export PATH=${SDK_BASE}/../xtensa-lx106-elf/bin:${PATH}
export ESPPORT=/dev/tty.SLAB_USBtoUART

make -f clean && \
make -f SDK_BASE=${SDK_BASE} && \
~/bin/esp_bootmode.sh && \
make -f SDK_BASE=${SDK_BASE} ESPPORT=${ESPPORT} flash && \
~/bin/esp_normalmode.sh && \
# we can't use "make test" to start the console, because we want to enter "normalmode" first
screen ${ESPPORT} 115200
