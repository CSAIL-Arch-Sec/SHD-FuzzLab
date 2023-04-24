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

#include "utils.h"
#include "shd.h"
#include "serial.h"
#include "defines.h"

#define BUF_SIZE ((768))

/*
 * shd_main()
 * Entrypoint for all MIT secure hardware design lab code.
 * Once we have reached this point, software-independent bringup
 * is fully complete and the CPU is ready to run the lab code.
 */
void shd_main(void) {
    printf("+------------------+\n");
    printf("| MIT SHD Fuzz Lab |\n");
    printf("|      Part 4      |\n");
    printf("+------------------+\n");

    char inputbuf[BUF_SIZE];
    uint32_t fname_len, lname_len;

    printf("inputbuf is at 0x%X\n", inputbuf);

    printf("How long is your first name: ");
    serial_read(inputbuf, sizeof(inputbuf));
    fname_len = atoi(inputbuf);

    printf("How long is your last name: ");
    serial_read(inputbuf, sizeof(inputbuf));
    lname_len = atoi(inputbuf);

    if (fname_len + lname_len > sizeof(inputbuf)) {
        printf("Error: Your name is too large!\n");
        return;
    }

    printf("Ok, tell me your first name: ");
    size_t firstname_bytes_read=serial_read(inputbuf, fname_len);
    printf("And your last name: ");
    serial_read(inputbuf + firstname_bytes_read, lname_len);

    printf("Your username is %s\n", inputbuf);
}
