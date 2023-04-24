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

// Utilities for pwnyOS- refactored to work with the PSP kernel
#include "utils.h"
#include "types.h"
#include "serial.h"
#include <stdarg.h>

int strlen (char *str) {
    int i = 0;
    while (*str) {
        i++;
        str++;
    }
    return i;
}

void strcpy (char *dst, char *src) {
    while (*src) {
        *dst = *src;
        src++;
        dst++;
    }
}

size_t strncpy(char *to, const char *from, size_t max_bytes) {
    if (max_bytes == 0) return 0;
    
    size_t i = 0;
    while (i < max_bytes - 1) {
        to[i] = from[i];
        if (from[i] == '\0') return i;
        i++;
    }
    // Insert null terminator:
    to[max_bytes-1] = '\0';
    return i;
}


bool strncmp (const char *str1, const char *str2, size_t max_bytes) {
    size_t i = 0;
    while (i < max_bytes) {
        if (str1[i] != str2[i]) return false;
        if (str1[i] == '\0') return true;
        i++;
    }

    // If a string is longer than max_bytes we need to say they're unequal,
    // even if they've been equal thus far.
    // This is since we can't look past max_bytes, and they may be unequal after.
    // If this is return true, then comparing the files "s" and "src/" will return true
    // (since files are compared by what the user typed, not the length of the overall name)
    return false;
}

/*
 * atoi
 * Convert string to unsigned integer.
 */
#define ASCII_NUMS_BEGIN 0x30
#define ASCII_NUMS_END 0x39
unsigned int atoi(char *str) {
    unsigned int result=0;
    char *cursor = str;

    while (*cursor) {
        if (*cursor < ASCII_NUMS_BEGIN || *cursor > ASCII_NUMS_END) {
            cursor++;
            continue;
        }
        result = result * 10 + (*cursor - ASCII_NUMS_BEGIN);
        cursor++;
    }

    return result;
}

/*
 * serial_read
 * Read up to buf_len bytes into buf through the serial port.
 *
 * If a newline is encountered, stores a NULL terminator into the buffer and quits.
 */
size_t serial_read(char *buf, size_t buf_len) {
    size_t bytes_read = 0;
    while (bytes_read < buf_len) {
        buf[bytes_read] = serial_getc();

        if (buf[bytes_read] == '\n') {
            buf[bytes_read] = '\x00';
            return bytes_read;
        }
        bytes_read+=1;
    }
    buf[bytes_read-1] = '\x00';
    return bytes_read-1;
}

/*
 * printf
 *
 * Prints a formatted string to the serial device.
 */
void printf(char *format, ...) {
    char *idx;

    bool is_special_code = false;
    bool should_print_preleading_zeroes = false;
    bool printed_anything = false;

    uint8_t arg_char_counter = 0;

    va_list ap;
    va_start(ap, format);

    for (idx = format; *idx != NULL; idx++) {
        if (is_special_code) {
            if (*idx != 'c' && *idx != 'C') { arg_char_counter = 0; }
            if (*idx == 'x' || *idx == 'X') {
                // Treat *arg as a hex number
                uint32_t arg_val = va_arg(ap, uint32_t);
                bool has_seen_nonzero = false;
                uint32_t counter = 8; // Max length
                while (counter > 0) {
                    int cur_digit = ((arg_val & 0xF0000000) >> 28);
                    if (cur_digit != 0) has_seen_nonzero = true;

                    if ((!(cur_digit == 0 && !has_seen_nonzero)) || should_print_preleading_zeroes) {
                        if (cur_digit < 0x0A) {
                            // Numeric
                            serial_putc(cur_digit + 0x30);
                        }
                        else {
                            // Alpha
                            serial_putc(cur_digit + 0x41 - 0x0A);
                        }
                        printed_anything = true;
                    }

                    arg_val = arg_val << 4;
                    counter--;
                }

                if (!printed_anything) {
                    // Thing to print was 0 and we didn't enable preleading zeroes
                    // So just print a 0 and move on
                    serial_putc('0');
                }

                // Move to next argument:
                is_special_code = false;
                should_print_preleading_zeroes = false;
                printed_anything = false;
                continue;
            }
            else if (*idx == '0') {
                // This means preprint the leading zeroes
                should_print_preleading_zeroes = true;

                // Not done with this argument yet so continue:
                continue;
            }
            else if (*idx == 's' || *idx == 'S') {
                // Print string
                char *cursor = va_arg(ap, char*);
                while (*cursor) {
                    serial_putc(*cursor);
                    cursor++;
                }

                should_print_preleading_zeroes = false;
                is_special_code = false;
                continue;
            }
            else if (*idx == 'c' || *idx == 'C') {
                // Print char
                char cur_val = va_arg(ap, int);
                serial_putc(cur_val);

                is_special_code = false;
                continue;
            }
            else {
                // Couldn't handle this argument type,
                // Move to next argument:
                is_special_code = false;
                va_arg(ap, uint32_t);
                continue;
            }
        }

        if (*idx == '%') {
            is_special_code = true;
            continue;
        }

        serial_putc(*idx);
    }

    va_end(ap);
}

uint32_t my_core_id() {
    uint32_t core_id;
    asm volatile (
        "csrr %[core_id_r], mhartid\n"
        : [core_id_r]"=r"(core_id)
    );

    return core_id;
}
