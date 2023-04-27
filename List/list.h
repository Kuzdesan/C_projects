
#define first_data 1


typedef struct Node {
    int data;
    struct Node *next;
} node;

node *add_head(node *head, int value);

node *add_back(node *head, int value);

node *add_element(node *head, int N, int value);

node *del_head(node *head);

node *del_back(node *head);

node *del_element(node *head, int value);

int get(node *head, int index, int *);

int size(node *head);

int get_first_index(node *head, int value, int *write_to);

node *set(node *head, int index, int value);

node *fill_list(node *head, int to_add);

node *add_back_sort(node *head, node *head2);

node *del_by_index(node *head, node *previos_to_del, node *next);

node *sort(node *head);

node *del_head_sort(node *head);

node *dialog();

void print(node *head);

int get_int(const char *msg);

void Menu();


