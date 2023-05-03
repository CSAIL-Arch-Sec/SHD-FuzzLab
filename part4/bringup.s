/*
 * Pretty Secure System
 * Joseph Ravichandran
 * UIUC Senior Thesis Spring 2021
 * MIT Secure Hardware Design Spring 2023
 *
 * MIT License
 * Copyright (c) 2021-2023 Joseph Ravichandran
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

.include "defines_asm.h"

/* Export the symbol start as a global symbol, and place this code in the ".text.start" section.
 * We created the .text.start section as a special section that gets placed at the very beginning of memory
 * in the linker script. See linker.ld for more! */
.global start
.section .text.start

/* This is the global entrypoint- the very first thing that gets run
 * when our program begins executing on the CPU!
 *
 * See linker.ld (the linker script) to see how we set this to be the beginning */
start:
    # Setup exception handler
    # Whenever an exception occurs, we will jump here
    la x1, exception_handler_entry
    csrw CSR_MTVEC, x1

    # Setup stack pointer to default kernel stack for this core
    # Note that PSP is a multicore system, so all cores need to
    # choose different parts of the anonymous bringup stack to use.

    # sp <- _kernel_anonymous_stack - (0x100 * mhartid)
    # hart id is the "core id"
    # This way all the cores have different stacks during early bringup
    csrr x1, CSR_MHARTID
    slli x1, x1, 8
    la sp, _kernel_anonymous_stack
    sub sp, sp, x1

    # mepc: What symbol to jump to when we mret (boot_main)
    la x1, boot_main
    csrw CSR_MEPC, x1

    # mpp (saved privilege level): What privilege level to run with after mret (PSP_PRIV_MACHINE)
    li x1, PSP_PRIV_USER
    csrrw x1, CSR_MPP, x1

    # mpie (saved interrupt enable): Should interrupts be enabled after mret? (No)
    li x1, 0
    csrrw x1, CSR_MPIE, x1

    # Put any non-boot cores to sleep early
    csrr x1, CSR_MHARTID
    bne x1, x0, wfi_forever

    # Where the first method goes if it ever returns:
    la ra, shutdown

    # We're all set to go!
    # This will perform the following:
    # pc <- mepc
    # mie <- mpie
    # privilege level <- mpp
    mret

# A busy loop for the core to rest in
.global wfi_forever
wfi_forever:
    wfi
    j wfi_forever

.global shutdown
shutdown:
    # 0xFFFF002B is a custom-1 instruction that immediately shuts off the core.
    # This is handled by a custom signal set in the control word that the writeback stage
    # forwards out of the SoC and into the testbench telling the simulator to shut down.
    # A lof of simulators use a MMIO write to trigger shutdown (eg. write to a special address),
    # but we do it with a custom instruction instead to save on complexity (as the PSP memory
    # hierarchy is quite complicated with multiple interconnects and MMIO devices).
    .word 0xFFFF002B
    j wfi_forever
