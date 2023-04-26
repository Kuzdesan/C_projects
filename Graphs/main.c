#include <stdio.h>
#include <stdlib.h>
#include "graphs.h"


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("You should give the file");
        return 0;
    }
    list *List_all = NULL;
    List_all = read_graph(List_all, argv[1]);
    print_graph(List_all);
    way *final_way = malloc(sizeof(way));
    final_way = final_find_way(List_all, 1, 6, final_way);
}

