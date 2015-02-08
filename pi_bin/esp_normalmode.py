#!/usr/bin/env python 

import RPi.GPIO as GPIO
from time import sleep

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(7, GPIO.OUT) # GPIO7 = bypass, active low 
GPIO.setup(8, GPIO.OUT) # GPIO8 = reset, active low

GPIO.output(7, GPIO.HIGH)
GPIO.output(8, GPIO.HIGH)
