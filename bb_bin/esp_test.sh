#!/bin/bash

SDK_BASE=/opt/local/esp-open-sdk/sdk
export PATH=${SDK_BASE}/../xtensa-lx106-elf/bin:${PATH}
ESPPORT=/dev/ttyO0
MAKEFILE=Makefile.linux

make -f ${MAKEFILE} clean && \
make -f ${MAKEFILE} SDK_BASE=${SDK_BASE} && \
sudo ~/bin/esp_bootmode.sh && \
make -f ${MAKEFILE} SDK_BASE=${SDK_BASE} ESPPORT=${ESPPORT} flash && \
~/bin/esp_normalmode.sh && \
# we can't use "make test" to start the console, because we want to enter "normalmode" first
screen ${ESPPORT} 115200
