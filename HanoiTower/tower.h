typedef struct stack {
    char *msg;
    int size;
    int current_size;
    int *elements;
    int id;
} Stack;

void print(Stack *st[3]);
void hanoi(int n, Stack *from, Stack *to, Stack *tmp);
Stack *check_max_id(Stack *from, Stack *to, Stack *tmp);
Stack *check_min_id(Stack *from, Stack *to, Stack *tmp);
Stack *init(int max_radius, int fill, int id);
void *move(Stack *from, Stack *to);
void print1(Stack *st, int num);
void *push(Stack *StackArray, int radius);
void pop(Stack *StackArray);

