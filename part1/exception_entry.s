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
.include "asm_offsets.h"

.section .text
.global exception_handler_entry

exception_handler_entry:
    # Store original stack pointer in mscratch
    # We will save it later after all the other regs are saved
    csrw CSR_MSCRATCH, sp

    # Make space on the stack for the new saved_regs_t
    addi sp, sp, -(SAVED_REGS_SIZE)

    # Save all registers except for sp (x2):
    # sp now points to the saved_regs_t
    sw x1, SAVED_REGS_X1(sp)
    #sw x2, SAVED_REGS_X2(sp) # <- Don't save the stack pointer here!
    sw x3, SAVED_REGS_X3(sp)
    sw x4, SAVED_REGS_X4(sp)
    sw x5, SAVED_REGS_X5(sp)
    sw x6, SAVED_REGS_X6(sp)
    sw x7, SAVED_REGS_X7(sp)
    sw x8, SAVED_REGS_X8(sp)
    sw x9, SAVED_REGS_X9(sp)
    sw x10, SAVED_REGS_X10(sp)
    sw x11, SAVED_REGS_X11(sp)
    sw x12, SAVED_REGS_X12(sp)
    sw x13, SAVED_REGS_X13(sp)
    sw x14, SAVED_REGS_X14(sp)
    sw x15, SAVED_REGS_X15(sp)
    sw x16, SAVED_REGS_X16(sp)
    sw x17, SAVED_REGS_X17(sp)
    sw x18, SAVED_REGS_X18(sp)
    sw x19, SAVED_REGS_X19(sp)
    sw x20, SAVED_REGS_X20(sp)
    sw x21, SAVED_REGS_X21(sp)
    sw x22, SAVED_REGS_X22(sp)
    sw x23, SAVED_REGS_X23(sp)
    sw x24, SAVED_REGS_X24(sp)
    sw x25, SAVED_REGS_X25(sp)
    sw x26, SAVED_REGS_X26(sp)
    sw x27, SAVED_REGS_X27(sp)
    sw x28, SAVED_REGS_X28(sp)
    sw x29, SAVED_REGS_X29(sp)
    sw x30, SAVED_REGS_X30(sp)
    sw x31, SAVED_REGS_X31(sp)

    # Save mepc and sp (using a0 as a scratch register)
    csrr a0, CSR_MEPC
    sw a0, SAVED_REGS_EPC(sp)
    csrr a0, CSR_MSCRATCH
    sw a0, SAVED_REGS_X2(sp)

    # Call handler(mcause, &regs_struct)
    csrrw a0, CSR_MCAUSE, x0
    mv a1, sp
    jal exception_handler

    # TODO: Remove this when you have implemented the
    # exception handler return logic!
    la a0, exception_not_implemented_str
    jal printf
    j wfi_forever

    # Restore the CPU state by reading every register
    # value back from the saved_regs we created above!

    # 1. Restore mepc from saved_regs
    lw a0, SAVED_REGS_EPC(sp)
    # TODO: Set CSR_MEPC = a0

    # 2. Restore the rest of the registers except for the stack pointer
    lw x1, SAVED_REGS_X1(sp)
    # I am skipping x2 as it points to the stack- save this one for the end!
    lw x3, SAVED_REGS_X3(sp)
    #...
    # TODO: Restore the rest of the registers

    # 3. Restore the stack pointer last
    # You should read it from the saved_regs struct,
    # just like all the other registers- except we do it last
    # TODO

    # 4. Now that all registers are restored, what instruction
    # do we run to return from the exception?
    # TODO

exception_not_implemented_str:
    .string "TODO: You need to write the exception handler return code!\n"
