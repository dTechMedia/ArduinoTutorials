#! /usr/bin/python3

import serial

arduino = serial.Serial('/dev/ttyACM0', 9600, timeout=0)

while 1:
  cmdString = input ('Input Command: ')
  
  if not isinstance(cmdString, str):
     cmdString = str(cmdString)
  
  if cmdString != "exit":
     print("Running Command String '" + cmdString + "'")
     arduino.write(cmdString.encode())
  