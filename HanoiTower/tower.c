#include <stdio.h>
#include <malloc.h>
#include "tower.h"
void pop(Stack *StackArray) {
    StackArray->current_size--;
}

void push(Stack *StackArray, int radius) {
    if (!StackArray->current_size) {
        StackArray->elements[0] = radius;
        StackArray->current_size++;
        StackArray->msg = "SUCCESS";
    } else if (StackArray->elements[StackArray->current_size - 1] > radius) {
        StackArray->elements[StackArray->current_size++] = radius;
        StackArray->msg = "SUCCESS";
    } else StackArray->msg = "ERROR";
}

void print1(Stack *st, int num) {
    printf("\nTower number %d:", num);
    for (int j = st->current_size; j >= 1; j--) {
        printf("\n-------%d-------\n", st->elements[j - 1]);
    }
    if (st->current_size == 0) {
        printf("\n");
    }
}


void move(Stack *from, Stack *to) {
    push(to, from->elements[from->current_size - 1]);
    printf("\n>>From tower number %d to tower number %d was moved element with radius %d [%s]<<\n", from->id,
           to->id, from->elements[from->current_size - 1], to->msg);
    pop(from);
}

Stack *init(int max_radius, int fill, int id) {
    Stack *st = malloc(sizeof(Stack));
    st->id = id;
    st->elements = malloc(sizeof(int) * max_radius);
    if (fill) {
        for (int i = max_radius; i > 0; i--) {
            push(st, i);
        }
    }
    st->msg = NULL;
    st->size = max_radius;
    return st;
}

Stack *check_min_id(Stack *from, Stack *to, Stack *tmp) {
    int a = from->id;
    int b = to->id;
    int c = tmp->id;
    if (a < b && a < c) {
        return from;
    }
    if (b < a && b < c) {
        return to;
    }
    if (c < a && c < b) {
        return tmp;
    }
}

Stack *check_max_id(Stack *from, Stack *to, Stack *tmp) {
    int a = from->id;
    int b = to->id;
    int c = tmp->id;
    if (a > b && a > c) {
        return from;
    }
    if (b > a && b > c) {
        return to;
    }
    if (c > a && c > b) {
        return tmp;
    }
}


void hanoi(int n, Stack *from, Stack *to, Stack *tmp) {
    if (n == 0) {
        return;
    }
    hanoi(n - 1, from, tmp, to);
    move(from, to);
    Stack *min = check_min_id(from, to, tmp);
    Stack *max = check_max_id(from, to, tmp);
    Stack *average;
    if (from != min && from != max) { average = from; }
    else if (to != min && to != max) { average = to; }
    else { average = tmp; }
    print1(min, min->id);
    print1(average, average->id);
    print1(max, max->id);
    hanoi(n - 1, tmp, to, from);
}

void print(Stack *st[3]) {
    for (int i = 0; i < 3; i++) {
        printf("\nTower number %d:\n", i + 1);
        for (int j = st[i]->current_size; j >= 1; j--) {
            printf("-------%d-------\n", st[i]->elements[j - 1]);
        }
    }
}
