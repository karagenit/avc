#!/usr/bin/env python3

import sys
import serial

if (len(sys.argv) != 5):
    exit()

# TODO: port may change
serialPort = serial.Serial("/dev/ttyUSB0", 115200);

serialPort.write(bytearray([127 + int(sys.argv[1])]))
serialPort.write(bytearray([127 + int(sys.argv[2])]))
serialPort.write(bytearray([127 + int(sys.argv[3])]))
serialPort.write(bytearray([127 + int(sys.argv[4])]))

print(serialPort.readline())

serialPort.close
