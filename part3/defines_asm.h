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

/* Various CPU hardware constants (privilege levels, CSRs, etc.) */

.set CSR_MHARTID      ,  0xf14
.set CSR_SERIAL_FLAGS ,  0x200
.set CSR_SERIAL_IO_IN ,  0x201
.set CSR_SERIAL_IO_OUT,  0x202
.set CSR_MSTATUS      ,  0x300
.set CSR_MSTATUSH     ,  0x310
.set CSR_MIE          ,  0x304
.set CSR_MTVEC        ,  0x305
.set CSR_MSCRATCH     ,  0x340
.set CSR_MEPC         ,  0x341
.set CSR_MCAUSE       ,  0x342
.set CSR_MTVAL        ,  0x343
.set CSR_MIP          ,  0x344
.set CSR_MPP          ,  0x399
.set CSR_MPIE         ,  0x398

.set PSP_PRIV_USER      ,   0
.set PSP_PRIV_MACHINE   ,   3
