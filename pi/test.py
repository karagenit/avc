#!/usr/bin/env python3

import serial

# TODO: port may change
serialPort = serial.Serial("/dev/ttyACM0", 115200);

while True:
    print("Enter motor values:")
    value = chr(input("A: "))
    serialPort.write(value)
    value = chr(input("B: "))
    serialPort.write(value)
    value = chr(input("C: "))
    serialPort.write(value)
    value = chr(input("D: "))
    serialPort.write(value)

serialPort.close
