typedef struct Stack_num {
    double data;
    struct Stack_num *next;
} num;

typedef struct Stack_operator {
    char data;
    int weight;
    struct Stack_operator *next;
} operator;


double calculate(char *to_calc, num *head1, operator *head2);

num *push_num(num *head, double value);

operator *push_operator(operator *head, char value, int weight);

num *pop_num(num *head);

operator *pop_operator(operator *head);

double get_top_num(num *head);

char get_top_oper(operator *head);

double Math(num *head1, operator *head2);
