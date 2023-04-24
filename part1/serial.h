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

#ifndef SERIAL_H
#define SERIAL_H

// These are assembly stubs that interact with the CSRs needed
// to support serial IO. They are defined in serial_csr.s!
extern void csr_serial_write_io(char c);
extern char csr_serial_read_io();
extern void csr_serial_write_flags(char c);
extern char csr_serial_read_flags();

#define SOFTSERIAL_FLAGS_CLEAR 0
#define SOFTSERIAL_FLAGS_WAITING 1

/*
 * serial_putc
 * Write a single character to the serial port.
 */
void serial_putc(char c);

/*
 * serial_getc
 * Read a single character from the serial port.
 */
char serial_getc(void);

/*
 * serial_puts
 * Write a string to the serial port.
 */
void serial_puts(char *str);

#endif // SERIAL_H
