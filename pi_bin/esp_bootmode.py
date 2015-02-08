#!/usr/bin/env python 

import RPi.GPIO as GPIO
from time import sleep


GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)

GPIO.setup(7, GPIO.OUT) # 7 = bypass relay, LOW==bypass mode
GPIO.setup(8, GPIO.OUT) # 8 = reset

GPIO.output(7, GPIO.LOW)
GPIO.output(8, GPIO.HIGH)
sleep(0.5)
GPIO.output(8, GPIO.LOW)
sleep(0.5)
GPIO.output(8, GPIO.HIGH)
