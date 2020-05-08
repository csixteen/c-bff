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

#include "c_bff.h"
#include "prog.h"
#include "stack.h"

Program *create_program(char *code) {
    Program *p = (Program*)malloc(sizeof(struct prog));

    p->ip = 0;
    p->cursor = 0;
    p->code = code;
    p->cells = (char*)malloc(MAX_CELLS * sizeof(char));
    p->stack = create_stack();

    return p;
}

void free_program(Program *p) {
    free(p->code);
    free(p->cells);

    free(p);
}

/*
 * Captures a single character from STDIN without waiting for
 * Enter to be pressed.
 * https://stackoverflow.com/questions/421860/capture-characters-from-standard-input-without-waiting-for-enter-to-be-pressed
 */
static char __read_char() {
    char buf = 0;

    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");

    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    if (read(0, &buf, 1) < 0)
        perror ("read()");

    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror ("tcsetattr ~ICANON");

    return (buf);
}

static void __execute_next_instruction(Program *p) {
    int offset = 1;

    switch (p->code[p->ip]) {
        case '>':
            p->cursor++;
            break;
        case '<':
            p->cursor--;
            break;
        case '+':
            p->cells[p->cursor]++;
            break;
        case '-':
            p->cells[p->cursor]--;
            break;
        case ',':
            p->cells[p->cursor] = __read_char();
            break;
        case '.':
            printf("%c", p->cells[p->cursor]);
            break;
        case '[':
            if (p->cells[p->cursor] > 0) {
                stack_push(p->stack, p->ip);
            }
            else {
                if (p->cells[p->cursor] > 0) {
                    stack_push(p->stack, p->ip);
                }
                else {
                    int i = p->ip + 1;
                    int skipped = 0;

                    while (i < strlen(p->code)) {
                        switch (p->code[i]) {
                            case '[':
                                skipped += 1;
                                break;
                            case ']':
                                if (skipped == 0) { i++; break; }
                                else { skipped -= 1; }
                                break;
                        }

                        i++;
                    }

                    offset = i - p->ip;
                }
            }
            break;
        case ']':
            if (p->cells[p->cursor] == 0) {
                stack_pop(p->stack);
            }
            else {
                int top = stack_peek(p->stack);
                offset = top - p->ip + 1;
            }
            break;
    }

    p->ip += offset;
}

/*
 * Executes the program while the Instruction Pointer
 * hasn't reached the end of the code.
 */
void execute_program(Program *p) {
    while (p->ip < strlen(p->code))
        __execute_next_instruction(p);
}
