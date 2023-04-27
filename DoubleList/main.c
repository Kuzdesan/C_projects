#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "double_list.h"

int main() {
    node *head = malloc(sizeof(node));
    head->next = NULL;
    head->data = 11;
    head->back = NULL;
    pointers *point = malloc(sizeof(pointers));
    point->head = head;
    point->tail = head;
    point->size++;

    point->size = 1;
    int choise = -1;
    fflush(stdout);
    while (choise != 0) {
        Menu();
        choise = get_int("Your choice");
        if (choise < 0 || choise > 10) {
            printf("[WARNING] Wrong option\n");
            continue;
        }
        printf("\n");
        point = (dialog(choise, point));

    }
}

