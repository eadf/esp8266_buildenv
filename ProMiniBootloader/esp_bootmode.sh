#!/bin/sh

python2.7 ~/bin/upload.py /dev/tty.ESPRELAY-DevB 9600 bypass
sleep 0.5
python2.7 ~/bin/upload.py /dev/tty.ESPRELAY-DevB 9600 reset 
