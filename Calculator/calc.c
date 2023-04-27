#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "calc.h"

num *push_num(num *head, double value) {
    num *new_num = malloc(sizeof(num));
    new_num->next = head;
    new_num->data = value;
    return new_num;
}

operator *push_operator(operator *head, char value, int weight) {
    operator *new_operator = malloc(sizeof(operator));
    new_operator->next = head;
    new_operator->data = value;
    new_operator->weight = weight;
    return new_operator;
}

num *pop_num(num *head) {
    if (head->next) {
        num *tmp = head->next;
        free(head);
        return tmp;
    }
    return head;
}

operator *pop_operator(operator *head) {
    if (head->next) {
        operator *tmp = head->next;
        free(head);
        return tmp;
    }
    return head;
}

double get_top_num(num *head) {
    return head->data;
}

char get_top_oper(operator *head) {
    return head->data;
}

double Math(num *head1, operator *head2) {
    int c = 0;
    while (head1->next->next) {
        double a = get_top_num(head1);
        head1 = pop_num(head1);
        char symb = get_top_oper(head2);
        head2 = pop_operator(head2);
        double b = get_top_num(head1);
        head1 = pop_num(head1);
        if (symb == '+') {
            head1 = push_num(head1, a + b);
        }
        if (symb == '-' && head2->data != symb) {
            head1 = push_num(head1, b - a);
        }
        if (symb == '-' && head2->data == symb) {
            head1 = push_num(head1, a + b);
        }
        if (symb == '*') {
            head1 = push_num(head1, a * b);
        }
        if (symb == '/') {
            if (a != 0) { head1 = push_num(head1, b / a); }
            else return -1000000000000000;
        }

    }
    if (!head1->next->next) {
        double a = get_top_num(head1);
        head1 = pop_num(head1);
        char symb = get_top_oper(head2);
        head2 = pop_operator(head2);
        double b = get_top_num(head1);
        head1 = pop_num(head1);
        if (symb == '+') {
            head1 = push_num(head1, a + b);
        }
        if (symb == '-') {
            head1 = push_num(head1, b - a);
        }
        if (symb == '*') {
            head1 = push_num(head1, a * b);
        }
        if (symb == '/') {
            if (a != 0) { head1 = push_num(head1, b / a); }
            else return -1000000000000000;
        }
        head1->next = NULL;
        return head1->data;
    }
}


double calculate(char *to_calc, num *head1, operator *head2) {
    char value;
    double final;
    int i = 0;
    int j = 0;
    int k = 0;
    int n = 0;
    int hard = 0;
    int very_hard = 0;
    int weight;
    char *res = malloc(sizeof(char) * 12);
    for (i; to_calc[i] != '\0'; i++) {
        value = to_calc[i];
        if (!isdigit(value) && i == 0) {
            return -1000000000000001;
        }
        if (isdigit(value) > 0) {
            if (j >= 12) {
                return -1000000000000002;
            } else {
                *(res + j) = value;
                j++;
            }
        } else if (value == '+' || value == '-' || value == '*' || value == '/') {
            final = atoi(res);
            if (value == '+' || value == '-') {
                weight = 1;
            }
            if (value == '*' || value == '/') {
                weight = 2;
            }

            if (head2->weight > weight &&
                head1->next) { //если приоритет текущей операции меньше, чем приоритет операции, лежащей на стеке
                int count = 0;
                while (head2->weight > weight && head1->next) {
                    if (count == 0) { // условие, что в цикл зашли первый раз
                        double a = get_top_num(head1);
                        head1 = pop_num(head1);
                        char sym = get_top_oper(head2);
                        head2 = pop_operator(head2);
                        if (sym == '*') { final = final * a; }
                        if (sym == '/') {
                            if (final != 0) { final = a / final; }
                            else { return -1000000000000000; }
                        }
                        if (k == 0) {
                            head1->data = final;
                            k++;
                        } else {
                            if (hard == 0 && very_hard == 0) { head1 = push_num(head1, final); }

                            else {
                                head1->data = final;
                            }
                        }
                        memset(res, ' ', j);
                        j = 0;
                        count++;
                    } else { // если уже заходили в цикл, но на стеке все еще лежит операция с бОльшим приоритетом
                        double a = get_top_num(head1);
                        head1 = pop_num(head1);
                        char sym = get_top_oper(head2);
                        double b = get_top_num(head1);
                        if (!head2->next) { // если на стеке осталась единственная операция с бОльшим весом
                            if (sym == '*') { final = b * a; }
                            if (sym == '/') {
                                if (a != 0) { final = b / a; }
                                else { return -1000000000000000; }
                            }
                            count = 0;
                            hard++;
                            very_hard++;
                            break;
                        }
                        if (sym == '*') { final = b * a; }
                        if (sym == '/') {
                            if (a != 0) { final = b / a; }
                            else { return -1000000000000000; }
                        }
                        head1 = pop_num(head1);
                        head2 = pop_operator(head2);
                        memset(res, ' ', j);
                        j = 0;
                    }
                }
            } else if (head2->weight > weight && !head1->next) {
                double a = get_top_num(head1);
                char sym = get_top_oper(head2);
                if (sym == '*') { final = final * a; }
                if (sym == '/') {
                    if (final != 0) { final = a / final; }
                    else { return -1000000000000000; }
                }
                hard++;
            } else if (head2->data == '/' && value == '/' && !head1->next) {
                double a = get_top_num(head1);
                if (final != 0) { final = a / final; }
                else { return -1000000000000000; }
                very_hard++;
            } else if (head2->data == '/' && value == '/' && head1->next) {
                double a = get_top_num(head1);
                head1 = pop_num(head1);
                if (final != 0) { final = a / final; }
                else { return -1000000000000000; }
                head2 = pop_operator(head2);

            } else if (head2->next && head2->weight == weight && head2->weight == head2->next->weight &&
                       get_top_oper(head2) != head2->next->data) {
                double a = get_top_num(head1);
                head1 = pop_num(head1);
                char sym = get_top_oper(head2);
                head2 = pop_operator(head2);
                if (sym == '+') { final = a - final; }
                if (sym == '-') { final = a - final; }
                if (sym == '/') {
                    if (final != 0) { final = a / final; }
                    else { return -1000000000000000; }
                }
                if (sym == '*') { final = final * a; }
            }

            if (k == 0) {
                head1->data = final;
                k++;
            } else {
                if (hard == 0 && very_hard == 0) { head1 = push_num(head1, final); }

                else {
                    head1->data = final;
                }
            }
            memset(res, ' ', j);
            j = 0;

            if (n == 0) {
                head2->data = value;
                head2->weight = weight;
                n++;
            } else {
                if (hard == 0 && very_hard == 0) { head2 = push_operator(head2, value, weight); }
                else {
                    head2->data = value;
                    head2->weight = weight;
                    hard = 0;
                    very_hard = 0;
                }
            }
            continue;
        }
    }

    final = atoi(res);
    if (head2->data == '+' && head2->next && head2->next->data == '-') {
        double a = get_top_num(head1);
        head1 = pop_num(head1);
        char sym = get_top_oper(head2);
        head2 = pop_operator(head2);

        final = a - final;
    }
    head1 = push_num(head1, final);
    return Math(head1, head2);
}
