#!/bin/bash
source debug.sh
cd sim
riscv64-unknown-elf-gdb --ex "set arch riscv:rv32" --ex "set confirm off" --ex "file obj_dir/kernel.elf" --ex "target remote localhost:$SHD_DEBUG_PORT"
