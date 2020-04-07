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

#include <assert.h>
#include <stdio.h>

#include "../src/stack.h"

void test_grow_stack() {
    Stack *s = create_stack();

    for (int i = 0; i < 5; i++) {
        stack_push(s, i+1);
    }

    for (int i = 0; i < 5; i++) {
        stack_push(s, i+1);
    }

    assert(s->capacity == 10);
    assert(s->len == 10);
    assert(stack_peek(s) == 5);

    for (int i = 0; i < 5; i++) {
        assert(stack_pop(s) == 5 - i);
    }

    delete_stack(s);
}

void test_shrink_stack() {
    Stack *s = create_stack();

    for (int i = 0; i < 8; i++) {
        stack_push(s, 1);
    }

    for (int i = 0; i < 6; i++) {
        stack_pop(s);
    }

    assert(s->capacity == 10);

    stack_pop(s);
    stack_pop(s);

    assert(s->len == 0);
    assert(s->capacity == 2);

    delete_stack(s);
}

int main(void) {
    test_grow_stack();
    test_shrink_stack();

    return 0;
}
