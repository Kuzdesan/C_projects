
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"


node *fill_list(node *head, int to_add) {
    int k = 0;
    node *tmp = head;
    while (k < to_add) {
        tmp = add_head(tmp, rand() % 1000);
        k++;
    }
    return tmp;
}

node *del_by_index(node *head, node *previos_to_del, node *next) {
    node *tmp = head;
    if (previos_to_del == NULL) {
        return del_head_sort(tmp);
    } else {
        while (head) {
            if (head == previos_to_del) {
                head->next = NULL;
                head->next = next;
                return tmp;
            }
            head = head->next;
        }
    }
}

node *sort(node *head) { //нужная сортировка
    node *new_head = NULL;
    int ptr = 0;
    clock_t start = clock();

    while (head) {
        int current_min = head->data;
        node *current = head;
        node *current_head = head;
        node *current_previos = NULL;

        while (current) {
            if (current->next && current->next->data < current_min) {
                current_previos = current;
                current_head = current->next;
                current_min = current->next->data;
                current = current->next;
            } else current = current->next;
        }
        ptr++;
        if (head->next) {
            head = del_by_index(head, current_previos, current_head->next);
        } else {
            if (ptr == 1) {
                new_head = current_head;
            } else {
                new_head = add_back_sort(new_head, current_head);
            }
            break;
        }
        current_head->next = NULL;
        if (ptr == 1) {
            new_head = current_head;
        } else {
            new_head = add_back_sort(new_head, current_head);
        }

    }
    clock_t stop = clock();
    printf("Time of sort by address: %f\n", ((stop - start)) * 1000.0 / CLOCKS_PER_SEC);
    return new_head;
}

node *sort_by_date(node *head) { //сортировка сменой значений местами
    node *final = head;
    node *to_return = final;
    clock_t start = clock();
    while (final) {
        if (final->next) {
            node *st = final->next;
            while (st) {
                if (st->data < final->data) {
                    int ptr = final->data;
                    final->data = st->data;
                    st->data = ptr;
                }
                st = st->next;
            }
            final = final->next;
        } else {
            clock_t stop = clock();
            printf("Time of sort by date: %f\n", ((stop - start)) * 1000.0 / CLOCKS_PER_SEC);
            return to_return;
        }
    }
}

node *add_head(node *head, int value) {
    node *new_st = malloc(sizeof(node));
    new_st->next = head;
    new_st->data = value;
    return new_st;
}

node *del_head(node *head) {
    if (head->next) {
        node *tmp = head->next;
        free(head);
        return tmp;
    } else return head;
}

node *del_head_sort(node *head) {
    if (head->next) {
        node *tmp = head->next;
        return tmp;
    } else return head;
}

int get_first_index(node *head, int value, int *write_to) {
    int k = 0;
    while (head) {
        if (head->data == value) {
            *write_to = k;
            return 1;
        }
        k++;
        head = head->next;
    }
    return 0;
}

node *set(node *head, int index, int value) {
    node *tmp = head;
    int i = 0;
    while (head) {
        if (i == index) {
            head->data = value;
            return tmp;
        }
        i++;
        head = head->next;
    }
    printf("index %d is out of range %d\n", index, i - 1);
    return tmp;
}

node *add_element(node *head, int N, int value) {
    int k = 1;
    node *tmp = head;
    if (N == 0) return add_head(head, value);
    else {
        while (head) {
            if (N == k && head->next) {
                node *new_struct = malloc(sizeof(node));
                node *ptr = head->next;
                head->next = new_struct;
                new_struct->next = ptr;
                new_struct->data = value;
                return tmp;
            } else if (N == k) {
                node *new_struct = malloc(sizeof(node));
                head->next = new_struct;
                new_struct->data = value;
                new_struct->next = NULL;
                return tmp;
            }
            k++;
            head = head->next;
        }
        printf("index %d is out of range %d\n", N, k - 1);
        return tmp;
    }
}

int size(node *head) {
    int size = 0;
    while (head) {
        size++;
        head = head->next;
    }
    return size;
}

int get(node *head, int index, int *place_to) {
    int k = 0;
    while (head) {
        if (index == k) {
            *place_to = head->data;
            return 1;
        }
        k++;
        head = head->next;
    }
    return 0;
}

node *del_element(node *head, int value) {
    node *tmp = head;
    if (tmp->data == value && tmp->next) {
        tmp = del_head(head);
        head = tmp;
    }
    if (tmp->data == value && tmp->next == 0) return tmp;
    while (head) {
        if (head->next && head->next->data == value) {
            node *ptr = head->next->next;
            free(head->next);
            head->next->next = NULL;
            head->next = ptr;
        }
        if (head->next == NULL && head->data == value) {
            return del_back(tmp);
        }
        if (head->next && head->next->data != value) {
            head = head->next;
        } else if (head->next == NULL && head->data != value) return tmp;
        else {
            while (head->next && head->next->data == value) {
                node *ptr = head->next->next;
                free(head->next);
                head->next->next = NULL;
                head->next = ptr;
            }
            if (head->next) {
                head = head->next;
            } else if (head->next == NULL && head->data == value) {
                return del_back(tmp);
            }
        }
    }
    return tmp;
}

node *add_back_sort(node *head, node *head2) {
    node *tmp = head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    tmp->next = head2;
    return head;
}

node *add_back(node *head, int value) {
    node *tmp = head;
    while (tmp->next) {
        tmp = tmp->next;
    }
    node *new_struct = malloc(sizeof(node));
    new_struct->next = NULL;
    new_struct->data = value;
    tmp->next = new_struct;
    return head;
}

node *del_back(node *head) {
    node *tmp = head;
    while (tmp->next->next) {
        tmp = tmp->next;
    }
    tmp->next = NULL;
    free(tmp->next);
    return head;
}



void print(node *head) {
    do {
        printf("+++++++++++++++++\n");
        printf("+int data =  [%d]+\n", head->data);
        printf("+++++++++++++++++\n");
        printf("\n");
        head = head->next;
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
    printf("5. Add on position \n");
    printf("6. Del by value \n");
    printf("7. Get element by index \n");
    printf("8. Get size of list \n");
    printf("9. Get first index of value \n");
    printf("10. Set value on position \n");
    printf("11. Sort list \n");
    printf("12. Sort list by address \n");
    printf("13. Fill list by random \n");
    printf("14. Print List \n");
}

node *dialog(int x, node *head) {
    int val, position;
    int res;
    int write_to;
    switch (x) {
        case 1:
            val = get_int("Enter data value: ");
            return add_head(head, val);
        case 2:
            return del_head(head);
        case 3:
            val = get_int("Enter data value: ");
            return add_back(head, val);
        case 4:
            return del_back(head);
        case 5:
            val = get_int("Enter data value: ");
            position = get_int("Enter position value: ");
            return add_element(head, position, val);
        case 6:
            val = get_int("Enter data value: ");
            return del_element(head, val);
        case 7:
            position = get_int("Enter position value: ");
            int temp = get(head, position, &res);
            if (temp == 1) {
                printf("the value is: %d\n", res);
            } else printf("index %d is out of range, the value is: %d\n", position, res);
            return head;
        case 8:
            printf("size of list: %d\n", size(head));
            return head;
        case 9:
            val = get_int("Enter data value: ");
            if (get_first_index(head, val, &write_to) == 1) {
                printf("the first index of value %d is %d\n", val, write_to);
            } else {
                printf("Value %d doesn't contains in list\n", val);
            }
            return head;
        case 10:
            val = get_int("Enter data value: ");
            position = get_int("Enter position value: ");
            return set(head, position, val);
        case 11:
            return sort_by_date(head);
        case 12:
            return sort(head);
        case 13:
            return fill_list(head, get_int("Number of elements to add: "));
        case 14:
            print(head);
            return head;
    }
}
