#!/usr/bin/env python3
from pwn import *

io=remote('127.0.0.1', 31338)

# Your exploit here!

io.interactive()
