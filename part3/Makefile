# Pretty Secure System
# Joseph Ravichandran
# UIUC Senior Thesis Spring 2021
# MIT Secure Hardware Design Spring 2023
#
# MIT License
# Copyright (c) 2021-2023 Joseph Ravichandran
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

TARGET_MEM:=kernel.mem
TARGET_BIN:=kernel.bin
TARGET_ELF:=kernel.elf

CC := riscv64-unknown-elf-gcc
AS := riscv64-unknown-elf-gcc
LD := riscv64-unknown-elf-gcc
OBJDUMP := riscv64-unknown-elf-objdump
OBJCOPY := riscv64-unknown-elf-objcopy
HEXDUMP := ../utils/hexdump.py
STRINGS := riscv64-unknown-elf-strings
RM := rm

# These files are not compiled into the main binary, but instead
# are used to generate headers at build time (eg. for assembly linkage).
# They should be built before anything else, and not linked against the main binary.
GENERATOR_FILES := ./asm_offsets.c
GENERATOR_RESULTS := $(notdir $(addsuffix .h, $(basename $(GENERATOR_FILES))))

SRC := $(shell find . -name '*.c' -or -name '*.S' -or -name '*.s')
SRC := $(filter-out $(GENERATOR_FILES),$(SRC))
OBJS := bringup.o
OBJS += $(notdir $(filter-out ./bringup.o,$(addsuffix .o, $(basename $(SRC)))))
DEPS := $(OBJS:.o=.d)

print-%  : ; @echo $* = $($*)

CFLAGS := -g -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -fno-plt -fno-pic -MMD -O0 -c
CXXFLAGS := $(CFLAGS)
ASFLAGS  := $(CFLAGS)
LDFLAGS1 := -g -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -fno-plt -fno-pic
LDFLAGS2 := -O0 -static-libgcc -lgcc

$(TARGET_MEM): $(TARGET_BIN)
	@python3 $(HEXDUMP) $< > $@
	@echo "  \033[1;32mHEXDUMP\033[0m $@"

$(TARGET_BIN): $(TARGET_ELF)
	@$(OBJCOPY) -O binary $< $@
	@echo "  \033[1;32mOBJCOPY\033[0m $@"

$(TARGET_ELF): $(OBJS) Makefile linker.ld
	@$(LD) $(LDFLAGS1) $(OBJS) -o $@ -T linker.ld $(LDFLAGS2)
	@echo "  \033[1;32mLD\033[0m $@"

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ $<
	@echo "  \033[1;32mCC\033[0m $@"

%.o: %.s $(GENERATOR_RESULTS)
	@$(AS) $(CFLAGS) -o $@ $<
	@echo "  \033[1;32mAS\033[0m $@"

.PHONY: clean
clean:
	@$(RM) -f $(GENERATOR_RESULTS) $(TARGET_ELF) $(TARGET_BIN) $(TARGET_MEM) $(OBJS) $(DEPS) $(FILTER_OBJS)
	@echo "  \033[1;32mRM\033[0m $(GENERATOR_RESULTS) $(TARGET_ELF) $(TARGET_BIN) $(TARGET_MEM) $(OBJS) $(DEPS) $(FILTER_OBJS)"

# Generate ASM headers from C files automagically
$(GENERATOR_RESULTS): $(GENERATOR_FILES)
	@echo "  \033[1;32mGEN_HDR\033[0m $@"
	@$(CC) $(CFLAGS) -o $(addsuffix .o,$(basename $@)) $<
	@$(OBJCOPY) -O binary $(addsuffix .o,$(basename $@)) $(addsuffix .o,$(basename $@))
	@$(STRINGS) $(addsuffix .o,$(basename $@)) > $@
	@$(RM) $(addsuffix .o,$(basename $@))
	@$(RM) -f $(addsuffix .d,$(basename $@))

-include $(DEPS)
