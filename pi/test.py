#!/usr/bin/env python3

import serial

# TODO: port may change
serialPort = serial.Serial("/dev/ttyUSB0", 115200);

while True:
    print("Enter motor values:")
    serialPort.write(bytearray([int(input("Motor A: "))]))
    serialPort.write(bytearray([int(input("Motor B: "))]))
    serialPort.write(bytearray([int(input("Motor C: "))]))
    serialPort.write(bytearray([int(input("Motor D: "))]))

serialPort.close
