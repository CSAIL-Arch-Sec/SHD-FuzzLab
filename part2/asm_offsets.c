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

#include "exception.h"
#include <stddef.h>

/*
 * PROBLEM:
 * We would like to be able to refer to elements of a C struct from assembly.
 * Specifically, where each offset within the saved_regs_t struct each register goes.
 *
 * Assembly cannot access C structs or use `offsetof` so we need to do a preprocessor step.
 *
 * SOLUTION:
 * We first create a C file that emits an object with a bunch of ASCII strings in it
 * using the .ascii feature of inline assembly.
 *
 * Each of these strings is a key value pair, where the key is the name of a struct member,
 * and the value is where to find it relative to the struct (eg. its offsetof).
 *
 * Then, we parse this file using riscv64-unknown-elf-objdump, and then we can dump
 * the resulting file into a new header with a bunch of assembly macros that assembly can read.
 *
 * This approach is used by the Linux kernel in its kbuild system.
 * Refer to include/linux/kbuild.h in the Linux kernel
 */

/*
 * EMIT_KEY_VALUE_PAIR(key,val)
 * Emits a definition for an assembly header file of the following format:
 *
 * .set KEY, VALUE # VALUE_MEANING
 *
 * KEY: The symbolic name of the thing to define (what you want it to be called in assembly)
 * VALUE: The value of the offset of the struct. This will be THE VALUE OF some C expression (eg. offsetof(whatever, whatever))
 * VALUE_MEANING: This is the actual C stringified meaning of value inserted as a comment for clarity.
 *
 * For example, if the name is "REGISTER_X1", and we wanted its value to be offsetof(saved_regs_t, x1) (which is 0), then:
 * KEY is the string "REGISTER_X1"
 * VALUE is 0
 * VALUE_MEANING is the string "offsetof(saved_regs_t, x1)"
 *
 * And the result would be:
 * .set REGISTER_X1, 0 # offsetof(saved_regs_t, x1)
 *
 * The first assembly line is used to emit the ".set blah blah" thing, and
 * the second line is used to emit the new line.
 * You might be wondering why not just add a "\n" to the first .asciz?
 * Well for some reason I get the warning: "Warning: unterminated string; newline inserted"
 * and this is the easiest way to just make that go away.
 */
#define EMIT_KEY_VALUE_PAIR(key,val) \
    asm volatile( \
        "\n.asciz \".set " #key ",%0 # " #val "\"" \
        "\n.word 0x10" \
    : : "i"(val))

/*
 * EMIT_OFFSET(name,structure,member)
 * This is a higher-level function that is used to wrap around EMIT_KEY_VALUE_PAIR.
 *
 * name: The name of the thing as it should be read in assembly.
 * structure: The C struct we want to emit the offset of.
 * member: The member within that structure.
 */
#define EMIT_OFFSET(name,structure,member) \
    EMIT_KEY_VALUE_PAIR(name, offsetof(structure,member))

/*
 * asm_offsets(void)
 * This is not a valid C function!
 *
 * The body contents of this function are a string of key value pairs
 * that are later used to generate an assembly header file.
 *
 * This is all a massive hack to get around the fact that assembly
 * doesn't understand C structures.
 */
__attribute__((naked)) void asm_offsets(void) {
    EMIT_OFFSET(SAVED_REGS_X1, saved_regs_t, x1);
    EMIT_OFFSET(SAVED_REGS_X2, saved_regs_t, x2);
    EMIT_OFFSET(SAVED_REGS_X3, saved_regs_t, x3);
    EMIT_OFFSET(SAVED_REGS_X4, saved_regs_t, x4);
    EMIT_OFFSET(SAVED_REGS_X5, saved_regs_t, x5);
    EMIT_OFFSET(SAVED_REGS_X6, saved_regs_t, x6);
    EMIT_OFFSET(SAVED_REGS_X7, saved_regs_t, x7);
    EMIT_OFFSET(SAVED_REGS_X8, saved_regs_t, x8);
    EMIT_OFFSET(SAVED_REGS_X9, saved_regs_t, x9);
    EMIT_OFFSET(SAVED_REGS_X10, saved_regs_t, x10);
    EMIT_OFFSET(SAVED_REGS_X11, saved_regs_t, x11);
    EMIT_OFFSET(SAVED_REGS_X12, saved_regs_t, x12);
    EMIT_OFFSET(SAVED_REGS_X13, saved_regs_t, x13);
    EMIT_OFFSET(SAVED_REGS_X14, saved_regs_t, x14);
    EMIT_OFFSET(SAVED_REGS_X15, saved_regs_t, x15);
    EMIT_OFFSET(SAVED_REGS_X16, saved_regs_t, x16);
    EMIT_OFFSET(SAVED_REGS_X17, saved_regs_t, x17);
    EMIT_OFFSET(SAVED_REGS_X18, saved_regs_t, x18);
    EMIT_OFFSET(SAVED_REGS_X19, saved_regs_t, x19);
    EMIT_OFFSET(SAVED_REGS_X20, saved_regs_t, x20);
    EMIT_OFFSET(SAVED_REGS_X21, saved_regs_t, x21);
    EMIT_OFFSET(SAVED_REGS_X22, saved_regs_t, x22);
    EMIT_OFFSET(SAVED_REGS_X23, saved_regs_t, x23);
    EMIT_OFFSET(SAVED_REGS_X24, saved_regs_t, x24);
    EMIT_OFFSET(SAVED_REGS_X25, saved_regs_t, x25);
    EMIT_OFFSET(SAVED_REGS_X26, saved_regs_t, x26);
    EMIT_OFFSET(SAVED_REGS_X27, saved_regs_t, x27);
    EMIT_OFFSET(SAVED_REGS_X28, saved_regs_t, x28);
    EMIT_OFFSET(SAVED_REGS_X29, saved_regs_t, x29);
    EMIT_OFFSET(SAVED_REGS_X30, saved_regs_t, x30);
    EMIT_OFFSET(SAVED_REGS_X31, saved_regs_t, x31);
    EMIT_OFFSET(SAVED_REGS_EPC, saved_regs_t, mepc);

    EMIT_KEY_VALUE_PAIR(SAVED_REGS_SIZE, sizeof(saved_regs_t));
}
