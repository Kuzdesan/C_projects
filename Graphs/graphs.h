#define INF 10000000000

typedef struct Node {
    int top_num;
    long label;
    int status;
    struct Side *sides_from;
    struct Side *sides_to;
} node;

typedef struct Side {
    node *top_to;
    int weight;
    struct Side *next;
} side;

typedef struct List {
    node *top;
    struct List *next;
} list;

typedef struct Way {
    struct List *tops;
    long wey_length;
} way;

list *read_graph(list *List_all, char *name);

void print_graph(list *List_all);

void print_graph_help(list *List_all);

node *search(list *head, int find);

side *init_side(node *to, int weight);

list *add_head(list *head, int num);

node *add_tail_from(node *head, node *tail, int weight);

node *add_tail_to(node *head, node *tail, int weight);

node *init_node(int num);

int make_labels(list *List_all, node *from, node *to, int num);

way *final_find_way(list *List_all, int from, int to, way *final_way);

list *add_head_without_malloc(list *List_all, node *head);

side *find_minimum(side *sides);

void fill_label(list *List_all, long num);

void change_label(list *List_all, int num);

void back_run(list *List_all, node *to, node *from, way *final_way);

void print_way(way *Way_all, int num_from, int num_to);

void clear_status(list *List_all);

node *find_min(list *List_all, node *top);

