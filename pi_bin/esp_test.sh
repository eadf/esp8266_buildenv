#!/bin/bash

SDK_BASE=/opt/local/esp-open-sdk/sdk
ESPPORT=/dev/ttyAMA0
MAKEFILE=Makefile.linux

make -f ${MAKEFILE} clean && \
make -f ${MAKEFILE} SDK_BASE=${SDK_BASE} && \
sudo ~/bin/esp_bootmode.py && \
make -f ${MAKEFILE} SDK_BASE=${SDK_BASE} ESPPORT=${ESPPORT} flash && \
sudo ~/bin/esp_normalmode.py && \
# we can't use "make test" to start the console, because we want to enter "normalmode" first
screen ${ESPPORT} 115200
