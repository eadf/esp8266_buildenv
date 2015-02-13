#!/usr/bin/env python2.7

# usage: send_and_receive_arduino <DEVICE> <BAUDRATE> <TEXT>
# where <DEVICE> is typically some /dev/ttyfoobar
# and where <BAUDRATE> is the baudrate
# and where <TEXT> is a text, e.g. "Hello"
import sys
import serial
import time
try:
  ser = serial.Serial() #xonxoff=0, rtscts=0)
  ser.port=sys.argv[1]
  ser.baudrate=sys.argv[2]
  ser.open()
  time.sleep(0.5)
  ser.write(sys.argv[3] + "\r\n")
  time.sleep(0.5)
  for i in range(3, len(sys.argv)):
    ser.write(sys.argv[i] + "\r\n")
    time.sleep(0.25)

  time.sleep(0.25)
  ser.close()
except Exception as e:
  print(e)
  sys.exit(1)
#while 1:
#   print ser.readline()
