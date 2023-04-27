
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

int main() {
    srand(time(0));
    node *head = malloc(sizeof(node));
    head->data = first_data;
    head->next = NULL;

    int choise = -1;
    while (choise != 0) {
        Menu();
        choise = get_int("Your choice");
        if (choise < 0 || choise > 14) {
            printf("[WARNING] Wrong option\n");
            continue;
        }
        printf("\n");
        head = dialog(choise, head);
    }
}

