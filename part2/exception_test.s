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

.section .text
.global exception_test
.global _exception_test_fail

/*
 * This file defines a test case for MIT Secure Hardware Design
 * student exception handlers to ensure they are saving and
 * restoring state properly.
 *
 * If your exception handler passes this test case,
 * you can be confident it is handling state saving correctly!
 */

/*
 * CSR_UNUSED_BY_OS
 * Some unused CSR that isn't one of the defined ones, we expect
 * students not to change it as part of their exception handlers
 * so we can use it for testing them.
 *
 * This is just a random number.
 */
.set CSR_UNUSED_BY_OS, 0x041

/*
 * void exception_test(void)
 * Test to see whether the exception handler is behaving correctly by
 * triggering an invalid instruction exception and testing to ensure
 * all registers are restored correctly afterwords.
 *
 * Never returns!
 */
exception_test:
    # Make space on the stack for our vars:
    addi sp, sp, -16

    la a0, test_str
    jal printf

    # Set all registers (except for stack) to obvious values:
    la x1,  0x11111111
    # Stack pointer should always point to valid memory, so don't set it here!
    csrw CSR_UNUSED_BY_OS, sp # Instead, save the stack pointer
                              # in a random CSR we assume nobody else uses.
    la x3,  0x33333333
    la x4,  0x44444444
    la x5,  0x55555555
    la x6,  0x66666666
    la x7,  0x77777777
    la x8,  0x88888888
    la x9,  0x99999999
    la x10, 0x10101010
    la x11, 0x11111111
    la x12, 0x12121212
    la x13, 0x13131313
    la x14, 0x14141414
    la x15, 0x15151515
    la x16, 0x16161616
    la x17, 0x17171717
    la x18, 0x18181818
    la x19, 0x19191919
    la x20, 0x20202020
    la x21, 0x21212121
    la x22, 0x22222222
    la x23, 0x23232323
    la x24, 0x24242424
    la x25, 0x25252525
    la x26, 0x26262626
    la x27, 0x27272727
    la x28, 0x28282828
    la x29, 0x29292929
    la x30, 0x30303030
    la x31, 0x31313131

    # Push a few test values to the stack to ensure the stack isn't modified either
    sw x1, 0(sp)
    sw x2, 4(sp)
    sw x3, 8(sp)
    sw x4, 12(sp)

    # Trigger invalid instruction exception:
    .word 0xaaaa

    # We expect the exception handler to skip over the faulting instruction,
    # record some data about the fault, and resume execution after.
    # (This is for MIT Secure Hardware Design, other behavior would likely
    # be desired for other use cases)

    # First, check the stack (x2) is unchanged
    # ASSUMPTION: exception handler doesn't change CSR_UNUSED_BY_OS
    # Simultaneously, save x1 to check later
    # x1 <- CSR_UNUSED_BY_OS (contains pre-exception x2)
    # CSR_UNUSED_BY_OS <- x1
    csrrw x1, CSR_UNUSED_BY_OS, x1
    bne x1, x2, _exception_test_fail

    # Check registers x3-x31
    la x1, 0x33333333
    bne x1, x3, _exception_test_fail
    la x1, 0x44444444
    bne x1, x4, _exception_test_fail
    la x1, 0x55555555
    bne x1, x5, _exception_test_fail
    la x1, 0x66666666
    bne x1, x6, _exception_test_fail
    la x1, 0x77777777
    bne x1, x7, _exception_test_fail
    la x1, 0x88888888
    bne x1, x8, _exception_test_fail
    la x1, 0x99999999
    bne x1, x9, _exception_test_fail
    la x1, 0x10101010
    bne x1, x10, _exception_test_fail
    la x1, 0x11111111
    bne x1, x11, _exception_test_fail
    la x1, 0x12121212
    bne x1, x12, _exception_test_fail
    la x1, 0x13131313
    bne x1, x13, _exception_test_fail
    la x1, 0x14141414
    bne x1, x14, _exception_test_fail
    la x1, 0x15151515
    bne x1, x15, _exception_test_fail
    la x1, 0x16161616
    bne x1, x16, _exception_test_fail
    la x1, 0x17171717
    bne x1, x17, _exception_test_fail
    la x1, 0x18181818
    bne x1, x18, _exception_test_fail
    la x1, 0x19191919
    bne x1, x19, _exception_test_fail
    la x1, 0x20202020
    bne x1, x20, _exception_test_fail
    la x1, 0x21212121
    bne x1, x21, _exception_test_fail
    la x1, 0x22222222
    bne x1, x22, _exception_test_fail
    la x1, 0x23232323
    bne x1, x23, _exception_test_fail
    la x1, 0x24242424
    bne x1, x24, _exception_test_fail
    la x1, 0x25252525
    bne x1, x25, _exception_test_fail
    la x1, 0x26262626
    bne x1, x26, _exception_test_fail
    la x1, 0x27272727
    bne x1, x27, _exception_test_fail
    la x1, 0x28282828
    bne x1, x28, _exception_test_fail
    la x1, 0x29292929
    bne x1, x29, _exception_test_fail
    la x1, 0x30303030
    bne x1, x30, _exception_test_fail
    la x1, 0x31313131
    bne x1, x31, _exception_test_fail

    # Now, go back and check x1
    csrr x1, CSR_UNUSED_BY_OS
    la x3, 0x11111111
    bne x1, x3, _exception_test_fail

    # Check the stack variables we saved earlier
    lw x1, 0(sp)
    la x5, 0x11111111
    bne x1, x5, _exception_test_fail

    lw x1, 4(sp) # The value saved here was x2 (sp), load it into x5 to check to not clobber x2
    bne x2, x1, _exception_test_fail

    lw x1, 8(sp)
    la x5, 0x33333333
    bne x1, x5, _exception_test_fail

    lw x1, 12(sp)
    la x5, 0x44444444
    bne x1, x5, _exception_test_fail

    j _exception_test_pass

_exception_test_fail:
    la a0, fail_str
    jal printf
    j wfi_forever # Go to sleep...

_exception_test_pass:
    la a0, pass_str
    jal printf
    j wfi_forever # Go to sleep...

fail_str:
    .asciz "Failed exception test\n"

pass_str:
    .asciz "Passed exception test!\n"

test_str:
    .asciz "Triggering exception...\n"
