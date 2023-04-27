typedef struct Node {
    int data;
    struct Node *next;
    struct Node *back;
} node;
typedef struct Pointers {
    long size;
    struct Node *tail;
    struct Node *head;
} pointers;


void print(node *head);

pointers *fill_list(pointers *point, int to_add);

pointers *add_head(pointers *point, int value);

pointers *add_back_sort(pointers *point, node *head2);

pointers *add_back(pointers *point, int value);

pointers *del_head(pointers *point);

pointers *del_tail(pointers *point);

pointers *delete(pointers *point, node *current_head);

pointers *dialog(int x, pointers *point);

node *get_point(pointers *point, long index);

long search(pointers *point, long value, long index);

int get_value_by_index(pointers *point, int index, int *res);

void Menu();

int get_int(const char *msg);

int get_size(pointers *point);

pointers *sort(pointers *point);
