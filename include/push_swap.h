#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stddef.h>

typedef struct s_stack
{
    int *data;
    int size;
} t_stack;

int parse_values(int argc, char **argv, int **out_values, int *out_count);
int to_indexes(const int *values, int count, int **out_indexes);
int is_sorted(const int *values, int count);
void sa(t_stack *a);
void pa(t_stack *a, t_stack *b);
void pb(t_stack *a, t_stack *b);
void ra(t_stack *a);
void rra(t_stack *a);
void sort_small(t_stack *a, t_stack *b);
void radix_sort(t_stack *a, t_stack *b);
void error_and_exit(void);

#endif
