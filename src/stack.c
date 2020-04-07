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

#include "errors.h"
#include "stack.h"


/*
 * Stack implementation using a dynamic array. Whenever we push
 * an item to the stack and the stack gets full, we double its
 * capacity. Whenever we pop an item and the number of items is
 * a quarter of the capacity, we shrink the stack to half the
 * current capacity. This way, the stack is always between 25% and
 * 100% full.
 */
Stack *create_stack() {
    Stack *s = (Stack*)malloc(sizeof(struct stack));
    s->capacity = 5;
    s->len = 0;
    s->sp = 0;
    s->s = (int*)malloc(s->capacity * sizeof(int));

    return s;
}


void __resize(Stack *s, size_t capacity) {
    int *new_s = (int*)realloc(s->s, capacity * sizeof(int));

    if (new_s == NULL) {
        errExit("realloc");
    }
    else {
        s->capacity = capacity;
        s->s = new_s;
    }
}


void stack_push(Stack *s, int item) {
    if (s->len == s->capacity) {
        __resize(s, 2 * s->capacity);
    }

    s->s[s->sp++] = item;
    s->len++;
}


int stack_pop(Stack *s) {
    int item = s->s[--s->sp];

    if (s->len > 0 && s->len <= s->capacity/4) {
        __resize(s, s->capacity / 2);
    }

    s->len--;

    return item;
}

int stack_peek(Stack *s) {
    if (s->len > 0) {
        return s->s[s->sp-1];
    }
    else {
        errExit("Possible invalid code.");
    }
}

void delete_stack(Stack *s) {
    free(s->s);
    free(s);
}
