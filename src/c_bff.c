/*
 * Copyright 2020 Pedro Rodrigues
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

#include <fcntl.h>

#include "common.h"
#include "errors.h"
#include "prog.h"

#define MAX_CELLS 30000


static Boolean __is_valid_operator(char c) {
    switch (c) {
        case '<' :
        case '>' :
        case '+' :
        case '-' :
        case '[' :
        case ']' :
        case ',' :
        case '.' : return 1;
        default : return 0;
    }
}


/*
 * Loads only valid Brainfuck operators from file into
 * an array of chars and returns a pointer to it.
 * @file_name
 */
char *load_code(char *file_name) {
    char buf[BUFSIZ];
    int fd, n, code_size = 0;

    if ((fd = open(file_name, O_RDONLY)) == -1) {
        errExit(file_name);
    }

    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        for (int i = 0; i < n; i++) {
            if (__is_valid_operator(buf[i])) {
                code_size++;
            }
        }
    }

    int pos = 0;
    char *code = (char*)malloc(code_size * sizeof(char));

    lseek(fd, 0, SEEK_SET);

    while ((n = read(fd, buf, BUFSIZ)) > 0) {
        for (int i = 0; i < n; i++) {
            if (__is_valid_operator(buf[i]))
                code[pos++] = buf[i];
        }
    }

    close(fd);

    return code;
}


// -----------------------------------------------------------


/*
 * Entry point
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        usageErr("c-bff <file.bf>\n");
    }

    char *code = load_code(argv[1]);

    Program *p = create_program(code, MAX_CELLS);
    execute_program(p);

    free_program(p);
}
