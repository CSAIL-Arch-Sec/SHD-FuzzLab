#!/usr/bin/env python3
# Given an input file output its bytes as hex chars, 4 bytes to a line
import sys

if len(sys.argv) != 2:
    print("usage: hexdump.py [file to dump]")
    exit(-1)

with open (sys.argv[1], "rb") as file_f:
    file_size = 0
    data = file_f.read(4)
    while data:
        file_size += 4
        print(data[::-1].hex())
        data = file_f.read(4)

    # Initialize uninitialized memory
    for i in range((0x10000 - file_size) // 4):
        print("00000000")
