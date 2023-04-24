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

#include "serial.h"
#include "utils.h"

void serial_putc(char c) {
    csr_serial_write_io(c);
}

char serial_getc() {
    while (csr_serial_read_flags() == SOFTSERIAL_FLAGS_CLEAR);
    char val = csr_serial_read_io();
    csr_serial_write_flags(SOFTSERIAL_FLAGS_CLEAR);
    return val;
}

void serial_puts(char *str) {
    char *cursor = str;
    while (*cursor) {
        serial_putc(*cursor);
        cursor++;
    }
}
