#!/bin/bash 

RESET_PIN=P9.14 
RELAY_PIN=P9.12

# set relay and reset as 'inactive'
config-pin ${RESET_PIN} hi
config-pin ${RELAY_PIN} hi
