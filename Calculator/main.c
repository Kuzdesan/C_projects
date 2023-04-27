#include <stdio.h>
#include <stdlib.h>
#include "calc.h"


int main(int argc, char *argv[]) {
    num *head1 = malloc(sizeof(num));
    operator *head2 = malloc(sizeof(operator));
    printf("Your expression: %s\n", argv[1]);
    //Example: 9/7*5/6+5+8-2-2-4+2*4/7-1
    double res = calculate(argv[1], head1, head2);
    if (res == -1000000000000000) {
        printf("You can't divide by zero!");
    }
    if (res == -1000000000000001) {
        printf("Wrong expression!");
    }
    if (res == -1000000000000002) {
        printf("Too long number!");
    } else {
        printf("Answer: %f\n", res);
    }

    return 0;
}
