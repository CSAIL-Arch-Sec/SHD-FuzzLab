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

#ifndef UTIL_H
#define UTIL_H

#include "types.h"

// Returns ceil(a/b)
#define ceil_div(a, b) ((((((a)) + ((b)) - 1))/((b))))
#define floor_div(a, b) ((((a))/((b))))

// Various string utility methods
int strlen(char *str);
void strcpy (char *dst, char *src);
size_t strncpy(char *to, const char *from, size_t max_bytes);
size_t memcpy(void *to, void *from, size_t max_bytes);
size_t memset(char *to, char val, size_t max_bytes);
size_t memsetl(void *to, uint32_t val, size_t max_bytes);

// This one just returns true if the strings are the same
// That's all anyone should care about when calling strncmp anyways!
bool strncmp (const char *str1, const char *str2, size_t max_bytes);

// printf- print a formatted string into the serial device
void printf (char *format, ...);

/*
 * serial_read
 * Read up to buf_len bytes into buf through the serial port.
 *
 * If a newline is encountered, stores a NULL terminator into the buffer and quits.
 *
 * Returns the number of bytes read.
 */
size_t serial_read(char *buf, size_t buf_len);

unsigned int atoi(char *str);

// Is a given char printable ASCII?
static inline int is_printable(char c) {
    return (c >= 0x20) && (c <= 0x7e);
}

/*
 * set_interrupts
 * If enabled is 1, turns them on
 * If enabled is 0, disables them
 */
static inline void set_interrupts(uint8_t enabled) {
    asm volatile (
        "csrw mie, %[enabled_r]\n"
        :
        : [enabled_r]"r"(enabled)
    );
}

static inline void enable_interrupts() {
    set_interrupts(1);
}

static inline void disable_interrupts() {
    set_interrupts(0);
}

#define __MY_CORE_ID ((my_core_id()))

/*
 * my_core_id
 * Returns the ID of the hart currently executing this code.
 */
uint32_t my_core_id();

#endif
