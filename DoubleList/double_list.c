#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "double_list.h"



node *get_point(pointers *point, long index) {
    int k = 0;
    node *tmp = point->head;
    while (tmp->next) {
        if (k == index) {
            return tmp;
        } else {
            k++;
            tmp = tmp->next;
        }
    }
    return NULL;
}

long search(pointers *point, long value, long index) {
    long size = point->size;
    if ((size % 2 != 0) && size > 1) {
        node *tmp = get_point(point, size / 2);
        node *tail_tmp = point->tail;
        node *head_tmp = point->head;
        if (tmp->data < value) {
            pointers *new_point = malloc(sizeof(point));
            index = index + (size / 2) + 1;
            new_point->head = tmp->next;
            new_point->tail = tail_tmp;
            new_point->size = size / 2;
            return search(new_point, value, index);
        }
        if (tmp->data > value) {
            pointers *new_point = malloc(sizeof(point));
            new_point->head = head_tmp;
            node *str = tmp->back;
            new_point->tail = str;
            new_point->size = size / 2;
            return search(new_point, value, index);
        }
        if (tmp->data == value) {
            index = index + size / 2;
            return index;
        }
    } else if ((size % 2 == 0) && size > 1) {
        node *ptr = get_point(point, size / 2);
        if (value > ptr->data) {
            pointers *new_point = malloc(sizeof(point));
            index += (size / 2);
            new_point->head = ptr;
            new_point->tail = point->tail;
            new_point->size = size / 2;
            return search(new_point, value, index);
        }
        if (value < ptr->data) {
            pointers *new_point = malloc(sizeof(node));
            new_point->head = point->head;
            new_point->tail = ptr->back;
            new_point->size = size / 2;
            return search(new_point, value, index);
        }
        if (value == ptr->data) {
            index += size / 2;
            return index;
        }
    } else if (size == 1 && point->head->data == value) {
        return index;
    } else {
        return -1;
    }
}


int get_value_by_index(pointers *point, int index, int *res) {
    int k = 0;
    int n = 1;
    long size = point->size;
    node *tmp = point->head;
    node *ptr = point->tail;
    clock_t start = clock();
    if (index >= 0 && index <= (size / 2)) {
        while (tmp) {
            if (k == index) {
                *res = tmp->data;
                clock_t stop = clock();
                printf("Time of checking value: %f\n", ((stop - start)) * 1000.0 / CLOCKS_PER_SEC);
                return 1;
            } else {
                k++;
                tmp = tmp->next;
            }
        }
    } else if ((index > (size / 2)) && (index < size)) {
        while (ptr) {
            if ((size - n) == index) {
                *res = ptr->data;
                clock_t stop = clock();
                printf("Time of checking value: %f\n", ((stop - start)) * 1000.0 / CLOCKS_PER_SEC);
                return 1;
            } else {
                n++;
                ptr = ptr->back;
            }
        }
    } else {
        clock_t stop = clock();
        printf("Time of checking value: %f\n", ((stop - start)) * 1000.0 / CLOCKS_PER_SEC);
        return 0;
    }
}


int get_size(pointers *point) {
    return point->size;
}

pointers *add_back_sort(pointers *point, node *head2) {
    point->tail->next = head2;
    head2->back = point->tail;
    point->tail = head2;
    return point;
}

pointers *delete(pointers *point, node *current_head) {
    if (current_head->next && current_head->back) {
        current_head->back->next = current_head->next;
        current_head->next->back = current_head->back;
        return point;
    } else if (current_head->next) {
        current_head->next->back = NULL;
        point->head = current_head->next;
        current_head->next = NULL;
        return point;
    } else if (current_head->back) {
        current_head->back->next = NULL;
        point->tail = current_head->back;
        current_head->back = NULL;
        return point;
    } else {
        point->head = NULL;
        point->tail = NULL;
        return point;
    }

}

pointers *sort(pointers *point) {
    pointers *new_pointer = malloc(sizeof(point));
    long new_size = point->size;
    int ptr = 0;
    clock_t start = clock();
    while (point->head) {
        int current_min = point->head->data;
        node *current = point->head;
        node *current_head = point->head;
        while (current) {
            if (current->data < current_min) {
                current_min = current->data;
                current_head = current;
                current = current->next;
            } else current = current->next;
        }
        ptr++;
        point = delete(point, current_head);
        current_head->next = NULL;
        if (ptr == 1) {
            new_pointer->head = current_head;
            new_pointer->tail = current_head;
        } else {
            new_pointer = add_back_sort(new_pointer, current_head);
        }

    }
    clock_t stop = clock();
    printf("Time of sort by address: %f\n", ((stop - start)) * 1000.0 / CLOCKS_PER_SEC);
    new_pointer->size = new_size;
    return new_pointer;
}

pointers *add_head(pointers *point, int value) {
    node *new_head = malloc(sizeof(node));

    point->head->back = new_head;
    new_head->next = point->head;
    new_head->data = value;
    new_head->back = NULL;
    point->head = point->head->back;
    point->size = point->size + 1;
    return point;
}


pointers *add_back(pointers *point, int value) {
    node *new_tail = malloc(sizeof(node));
    new_tail->next = NULL;
    new_tail->data = value;
    point->tail->next = new_tail;
    new_tail->back = point->tail;
    point->tail = new_tail;
    point->size = point->size + 1;
    return point;
}


pointers *del_head(pointers *point) {
    if (point->head->next != NULL) {
        node *tmp = point->head->next;
        point->head->next->back = NULL;
        point->head->next = NULL;
        free(point->head);
        point->head = tmp;
    }
    point->size = point->size - 1;
    return point;
}

pointers *del_tail(pointers *point) {
    if (point->tail->back != NULL) {
        node *tmp = point->tail->back;
        point->tail->back->next = NULL;
        point->tail->back = NULL;
        free(point->tail);
        point->tail = tmp;
    }
    point->size = point->size - 1;
    return point;
}

pointers *fill_list(pointers *point, int to_add) {
    int k = 0;
    while (k < to_add) {
        point = add_head(point, rand() % 1000);
        k++;
    }
    return point;
}


void print(node *head) {
    int i = 0;
    do {
        printf("+++++++++++++++++\n");
        printf("+%d. int data =  [%d]+\n", i, head->data);
        printf("+++++++++++++++++\n");
        printf("\n");
        head = head->next;
        i++;
    } while (head != NULL);
}


int get_int(const char *msg) {
    int res = 0;
    int ret_val = 0;
    while (!ret_val) {
        printf("%s: ", msg);
        ret_val = scanf("%d", &res);
        if (!ret_val) {
            printf("[ERROR] Waiting for integer\n");
            scanf("%*[^\n]");
            printf("%s: ", msg);
        }
    }

    scanf("%*c");
    return res;
}

void Menu() {
    printf("Chose option\n");
    printf("0. Exit\n");
    printf("1. Add Head\n");
    printf("2. Del Head\n");
    printf("3. Add Back\n");
    printf("4. Del Back\n");
    printf("5. Get size of list \n");
    printf("6. Sort list \n");
    printf("7. Fill list by random \n");
    printf("8. Get value \n");
    printf("9. Get index of value \n");
    printf("10. Print List \n");
}

pointers *dialog(int x, pointers *point) {
    int val, tmp;
    int res;
    switch (x) {
        case 1: {
            val = get_int("Enter data value: ");
            return add_head(point, val);
        }
        case 2:
            return del_head(point);
        case 3: {
            val = get_int("Enter data value: ");
            return add_back(point, val);
        }
        case 4:
            return del_tail(point);
        case 5: {
            printf("The size of list: %d\n", get_size(point));
            return point;
        }
        case 6:
            return sort(point);
        case 7:
            return fill_list(point, get_int("Number of elements to add: "));
        case 8: {
            tmp = get_value_by_index(point, get_int("Your index: "), &res);
            if (tmp == 1) {
                printf("The value is: %d\n", res);
            } else {
                printf("Incorrect index\n");
            }
            return point;
        }

        case 9: {
            const int N = 0;
            val = get_int("Enter your value: ");
            long res = search(point, val, N);
            if (res != -1) {
                printf("the index of value %d is: %ld\n", val, res);
            } else {
                printf("value %d doesn't contain in list\n", val);
            }
            return point;
        }

        case 10: {
            print(point->head);
            return point;
        }
    }
}
