#! /usr/bin/env python
import serial
ser = serial.Serial('/dev/ttyACM0', 9600)

ser.write('1')

system("checkTemp.py")