#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"

way* final_find_way(list *List_all, int from, int to, way *final_way) {
    printf("\n\n>>>>>\tFINDING THE SHORTEST WAY %d->%d\t<<<<<\n", from, to);
    if (from == to){
        printf("\tSorry, I can't work when the beginning equals the end(((\n");
        printf("------------------------------------------------------");
        return NULL;
    }
    fill_label(List_all, INF);
    change_label(List_all, from);
    node *from_top = search(List_all, from);
    if (from_top == NULL){
        printf("\tNo such top: %d!!!\n", from);
        printf("------------------------------------------------------");
        return NULL;
    }
    if (from_top->sides_from == NULL) {
        printf("\tThere now edges from top %d!!!\n", from);
        printf("------------------------------------------------------");
        return NULL;
    }
    node *to_top = search(List_all, to);
    if (to_top == NULL){
        printf("\tNo such top: %d!!!\n", to);
        printf("------------------------------------------------------");
        return NULL;
    }
    if (to_top->sides_to == NULL) {
        printf("\tTop %d is unreachable!!!\n", to);
        printf("------------------------------------------------------");
        return NULL;
    }
    int success = make_labels(List_all, from_top, to_top, from);
    if (success == 0) {
        printf("\tTop %d is unreachable from top %d\n", to, from);
        printf("------------------------------------------------------");
        return NULL;
    } else {
        list *new_list = malloc(sizeof(list));
        new_list->top = to_top;
        new_list->next = NULL;
        final_way->tops = new_list;
        final_way->wey_length = to_top->label;
        back_run(List_all, to_top, from_top, final_way);
        print_way(final_way, from, to);
        fill_label(List_all, 0);
        clear_status(List_all);
        return final_way;
    }
}

//расстановка меток вершин
int make_labels(list *List_all, node *from, node *to, int num) {
    side *tmp = from->sides_from;
    while (tmp) {
        if (tmp->top_to->status == 0) {
            long dist = from->label + tmp->weight;
            if (dist < tmp->top_to->label) {
                tmp->top_to->label = dist;
            }
        }
        tmp = tmp->next;
    }
    from->status = 1;
    node *minimum = NULL;
    if (from->sides_from) { //проверка, потому что иначе сломается в find_min
        minimum = find_min(List_all, from);
    } else {
        minimum = from;
    }
    if (minimum->sides_from == NULL && minimum != to) { //при таком раскладе вершина недостижима
        return 0;
    }
    if (minimum != to) {
        make_labels(List_all, minimum, to, num);
    } else return 1;
}


// после того, как расставили все метки, пробегаемся от вершины to до вершины from, чтобв определить искомый путь
void back_run(list *List_all, node *to, node *from, way *final_way) {
    side *tmp = to->sides_to;
    while (tmp) {
        long count = to->label - tmp->weight;
        if (count == tmp->top_to->label) {
            final_way->tops = add_head_without_malloc(final_way->tops, tmp->top_to);
            break;
        }
        tmp = tmp->next;
    }
    if (tmp->top_to != from) { back_run(List_all, tmp->top_to, from, final_way); }
    else return;
}

void clear_status(list *List_all) {
    list *point = List_all;
    while (point) {
        point->top->status == 0;
        point = point->next;
    }
}

void fill_label(list *List_all, long num) {
    list *point = List_all;
    while (point) {
        point->top->label = num;
        point = point->next;
    }
}

void change_label(list *List_all, int num) { //изменение метки по номеру вершины
    list *point = List_all;
    while (point) {
        if (point->top->top_num == num) {
            point->top->label = 0;
        }
        point = point->next;
    }
}

node *find_min(list *List_all, node *top) { // поиск минимума
    node *current_min = NULL;
    long minimum = INF;
    list *point = List_all;
    while (point) {
        if (point->top->status != 1 && point->top->label < minimum) {
            current_min = point->top;
            minimum = point->top->label;
        }
        point = point->next;
    }
    return current_min;
}

list *add_head_without_malloc(list *List_all, node *head) { //не маллочится нода
    if (!List_all) {
        List_all = malloc(sizeof(list));
        List_all->next = NULL;
        List_all->top = head;
        return List_all;
    } else {
        list *tmp = malloc(sizeof(list));
        tmp->next = List_all;
        tmp->top = head;
        return tmp;
    }
}

node *init_node(int num) {
    node *new_node = malloc(sizeof(node));
    new_node->top_num = num;
    new_node->sides_from = NULL;
    return new_node;
}

node *add_tail_from(node *head, node *tail, int weight) { //добавление ребра, выходящего из вершины
    side *tmp = head->sides_from;
    if (tmp == NULL) {
        head->sides_from = malloc(sizeof(side));
        head->sides_from->top_to = tail;
        head->sides_from->weight = weight;
    } else {
        while (tmp->next) {
            tmp = tmp->next;
        }
        side *new_side = malloc(sizeof(side));
        new_side->top_to = tail;
        new_side->weight = weight;
        tmp->next = new_side;
    }
    return head;
}

node *add_tail_to(node *head, node *tail, int weight) { // добавление ребра, входящего в вершину
    side *tmp = head->sides_to;
    if (tmp == NULL) {
        head->sides_to = malloc(sizeof(side));
        head->sides_to->top_to = tail;
        head->sides_to->weight = weight;
    } else {
        while (tmp->next) {
            tmp = tmp->next;
        }
        side *new_side = malloc(sizeof(side));
        new_side->top_to = tail;
        new_side->weight = weight;
        tmp->next = new_side;
    }
    return head;
}

list *add_head(list *head, int num) {
    if (!head) {
        head = malloc(sizeof(list));
        head->next = NULL;
        node *el = init_node(num);
        head->top = el;
        return head;
    } else {
        list *tmp = malloc(sizeof(list));
        tmp->next = head;
        node *el = init_node(num);
        tmp->top = el;
        return tmp;
    }
}

side *init_side(node *to, int weight) {
    side *new_side = malloc(sizeof(side));
    new_side->top_to = to;
    new_side->weight = weight;
    new_side->next = NULL;
    return new_side;
}

node *search(list *head, int find) {
    list *tmp = head;
    while (tmp) {
        if (tmp->top->top_num == find) {
            return tmp->top;
        }
        tmp = tmp->next;
    }
    return NULL; //no such element
}


void print_graph(list *List_all) {
    printf("\n\n>>>>>\tYOUR GRAPH\t<<<<<\n\n");
    list *point = List_all;
    int num_of_sides = 0;
    while (point) {
        node *str = point->top;
        side *tmp = str->sides_from;
        while (tmp) {
            num_of_sides++;
            printf("%d->%d\t||\t weight: %d\n", str->top_num, tmp->top_to->top_num,
                   tmp->weight);
            tmp = tmp->next;
        }
        point = point->next;
    }
    printf("\nTotal number of sides is : %d\n", num_of_sides);
    printf("------------------------------------------------------");
}


list *read_graph(list *List_all, char *name) {
    FILE *input;
    int from, to, weight = 0;
    if ((input = fopen(name, "r")) == NULL) exit(2);
    while (fscanf(input, "%d%d%d", &from, &to, &weight) != EOF) {
        if (!List_all) {
            List_all = add_head(List_all, to);
            List_all = add_head(List_all, from);
            List_all->top->sides_from = init_side(List_all->next->top, weight);
            List_all->next->top->sides_to = init_side(List_all->top, weight);
        } else {
            list *tmp = List_all;
            node *from_new = search(tmp, from);
            node *to_new = search(tmp, to);
            if (from_new != NULL) {     //если нода from уже есть в списке
                if (to_new != NULL) {   //если нода to уже тоже есть в списке
                    from_new = add_tail_from(from_new, to_new,
                                             weight);     //добавлем ребро->to_new, которое исходит из вершины from_new
                    to_new = add_tail_to(to_new, from_new,
                                         weight);         // добавлем ребро->from_to, которое входит в вершину to_new

                } else { //если ноды to нет в списке
                    List_all = add_head(List_all, to);
                    from_new = add_tail_from(from_new, List_all->top,
                                             weight);  //добавлем ребро->to, которое исходит из вершины from_new
                    List_all->top = add_tail_to(List_all->top, from_new,
                                                weight);   // добавлем ребро->from_to, которое входит в вершину to
                }
            } else { //если ноды from нет в списке
                List_all = add_head(List_all, from);
                if (to_new != NULL) { //если нода to уже есть в списке
                    List_all->top->sides_from = init_side(to_new, weight);
                    to_new = add_tail_to(to_new, List_all->top, weight);
                } else { //если ноды to нет в списке
                    node *prev_head = List_all->top;
                    List_all = add_head(List_all, to);
                    prev_head = add_tail_from(prev_head, List_all->top, weight);
                    List_all->top = add_tail_to(List_all->top, prev_head, weight);
                }
            }
        }
    }
    fclose(input);
    return List_all;
}

void print_way(way *Way_all, int num_from, int num_to) {
    list *tmp = Way_all->tops;
    printf("\n\tThe shortest way from %d to %d:", num_from, num_to);
    printf("\t");
    while (tmp) {
        node *top = tmp->top;
        if (tmp->next) { printf("%d -> ", top->top_num); }
        else printf("%d", top->top_num);
        tmp = tmp->next;
    }
    printf("\n\n\tTotal length is: %ld\n\n", Way_all->wey_length);
    printf("------------------------------------------------------");
}


