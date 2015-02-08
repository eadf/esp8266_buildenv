#!/usr/bin/env python 

import RPi.GPIO as GPIO
from time import sleep

GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(8, GPIO.OUT) # 8 is reset

GPIO.output(8, GPIO.HIGH)
sleep(0.5)
GPIO.output(8, GPIO.LOW)
sleep(0.5)
GPIO.output(8, GPIO.HIGH)
