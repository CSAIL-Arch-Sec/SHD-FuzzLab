/*
 * Pretty Secure System
 * Joseph Ravichandran
 * UIUC Senior Thesis Spring 2021
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

#ifndef DEFINES_H
#define DEFINES_H

// Various CSR addresses
#define     CSR_MHARTID     0xf14
#define     CSR_MSTATUS     0x300
#define     CSR_MSTATUSH    0x310
#define     CSR_MIE         0x304
#define     CSR_MTVEC       0x305
#define     CSR_MSCRATCH    0x340
#define     CSR_MEPC        0x341
#define     CSR_MCAUSE      0x342
#define     CSR_MTVAL       0x343
#define     CSR_MIP         0x344
#define     CSR_MPP         0x399
#define     CSR_MPIE        0x398
#define     CSR_MIPI_ISSUER 0x397

// Various exception causes (in mcause)
/* Disallowed CSR read or write */
#define     EXCEPTION_CAUSE_ILLEGAL_ACCESS  0x00000001

/* Invalid (illegal) or unsupported instruction */
#define     EXCEPTION_CAUSE_INVALID_INST    0x00000002

/* System calls from various privilege levels */
#define     EXCEPTION_CAUSE_ECALL_U         0x00000008
#define     EXCEPTION_CAUSE_ECALL_S         0x00000009
#define     EXCEPTION_CAUSE_ECALL_M         0x0000000b

/* External (off-chip) Device Interrupt */
#define     EXCEPTION_CAUSE_EXTERNAL        0x8000000b

/* Inter-Processor Interrupt */
#define     EXCEPTION_CAUSE_IPI             0x8000000c

/* Low privilege U mode */
#define     PSP_PRIV_USER       0

/* High privilege M mode */
#define     PSP_PRIV_MACHINE    3

// MMIO device regions
#define     TEXT_MEM        0x40000000
#define     VIDEO_MEM       0x80000000

// Multicore parameters
#define     MAIN_CORE_ID    0

#endif // DEFINES_H
