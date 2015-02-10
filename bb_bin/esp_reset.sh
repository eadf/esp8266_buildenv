#!/bin/bash 

RESET_PIN=P9.14

config-pin ${RESET_PIN} hi
# perform the esp8266 reset
config-pin ${RESET_PIN} lo
sleep 0.1
config-pin ${RESET_PIN} high

