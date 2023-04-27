#include <stdio.h>
#include "tower.h"

int main() {
    int max_radius;
    printf("Enter max radius: ");
    scanf("%d", &max_radius);
    Stack *stack1 = init(max_radius, 1, 1);
    Stack *stack2 = init(max_radius, 0, 2);
    Stack *stack3 = init(max_radius, 0, 3);
    Stack *coll[3] = {stack1, stack2, stack3};
    printf("\n~~~~~~~~~YOUR TOWERS~~~~~~~~~\n");
    print(coll);
    printf("\n~~~~~~~~~START MOVING~~~~~~~~~\n");
    hanoi(max_radius, stack1, stack2, stack3);
    printf("\n~~~~~~~~~RESULT~~~~~~~~~\n");
    print(coll);
}
