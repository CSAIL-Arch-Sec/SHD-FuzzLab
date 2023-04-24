#!/bin/bash
set -e

source debug.sh

if [[ -z "$1" ]]
then
    echo "Need to specify which part to run!"
    echo "Usage: run.sh [part] (optional: --debug)"
    exit -1
fi

# Which kernel image to simulate?
: ${KERNEL_MEMFILE:="$1/kernel.mem"}
: ${KERNEL_ELFFILE:="$1/kernel.elf"}

if [[ ! -f $KERNEL_MEMFILE ]]; then
    echo "No kernel image found: $KERNEL_MEMFILE"
    echo "Did you remember to make?"
    exit -1
fi

if [[ ! -f $KERNEL_ELFFILE ]]; then
    echo "Warning: No debug symbols found for $KERNEL_MEMFILE"
    echo "(Could not find $KERNEL_ELFFILE)"
else
    # Only copy the debug symbols if we could find them
    cp $KERNEL_ELFFILE sim/obj_dir/kernel.elf
fi

# What to initialize the CSRs to?
# (This is where the secret flag is loaded into the PSP CSRs)
: ${CSR_MEMFILE:="csr_file.mem"}

if [[ ! -f $CSR_MEMFILE ]]; then
    echo "No CSR initialization file found: $CSR_MEMFILE"
    exit -1
fi

cp $KERNEL_MEMFILE sim/obj_dir/kernel.mem
cp $CSR_MEMFILE sim/obj_dir/csr_file.mem

cd sim/obj_dir

if [[ -z "$2" ]]; then
./Vpsp $2
else
if [[ -z $SHD_DEBUG_PORT ]]; then
    echo "Error: You need to set the debug port in debug.sh!"
    exit -1
fi
./Vpsp $2 $SHD_DEBUG_PORT
fi