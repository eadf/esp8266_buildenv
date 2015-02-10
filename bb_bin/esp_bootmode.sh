#!/bin/bash 

RESET_PIN=P9.14 
RELAY_PIN=P9.12

config-pin ${RESET_PIN} hi
config-pin ${RELAY_PIN} lo

# give the relay 0.5 sec to switch over
sleep 0.5 

# perform the esp8266 reset
config-pin ${RESET_PIN} lo
sleep 0.1
config-pin ${RESET_PIN} high

# relay should now be in "active state" disconnecting eventual hardware from the esp
