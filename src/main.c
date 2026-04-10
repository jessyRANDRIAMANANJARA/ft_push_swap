#include "../include/push_swap.h"

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static int is_space(char c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
        || c == '\r');
}

void error_and_exit(void)
{
    write(2, "Error\n", 6);
    exit(1);
}

static int append_value(int **values, int *count, int *capacity, int value)
{
    int *new_values;

    if (*count >= *capacity)
    {
        *capacity *= 2;
        new_values = malloc(sizeof(int) * (*capacity));
        if (!new_values)
            return (0);
        memcpy(new_values, *values, sizeof(int) * (*count));
        free(*values);
        *values = new_values;
    }
    (*values)[*count] = value;
    (*count)++;
    return (1);
}

static int parse_token(const char *token, size_t len, int *value)
{
    size_t i;
    int sign;
    long result;
    long digit;

    i = 0;
    sign = 1;
    result = 0;
    if (len == 0)
        return (0);
    if (token[i] == '+' || token[i] == '-')
    {
        if (token[i] == '-')
            sign = -1;
        i++;
    }
    if (i >= len)
        return (0);
    while (i < len)
    {
        if (token[i] < '0' || token[i] > '9')
            return (0);
        digit = token[i] - '0';
        if ((sign == 1 && result > (INT_MAX - digit) / 10)
            || (sign == -1 && result > ((-(long)INT_MIN) - digit) / 10))
            return (0);
        result = result * 10 + digit;
        i++;
    }
    *value = (int)(result * sign);
    return (1);
}

static int has_duplicates(const int *values, int count)
{
    int i;
    int j;

    i = 0;
    while (i < count)
    {
        j = i + 1;
        while (j < count)
        {
            if (values[i] == values[j])
                return (1);
            j++;
        }
        i++;
    }
    return (0);
}

int parse_values(int argc, char **argv, int **out_values, int *out_count)
{
    int *values;
    int count;
    int capacity;
    int i;
    char *arg;
    int value;
    size_t len;

    values = malloc(sizeof(int) * 16);
    if (!values)
        return (0);
    count = 0;
    capacity = 16;
    i = 1;
    while (i < argc)
    {
        arg = argv[i];
        while (*arg)
        {
            while (is_space(*arg))
                arg++;
            len = 0;
            while (arg[len] && !is_space(arg[len]))
                len++;
            if (len == 0)
                break ;
            if (!parse_token(arg, len, &value)
                || !append_value(&values, &count, &capacity, value))
                return (free(values), 0);
            arg += len;
        }
        i++;
    }
    if (count == 0 || has_duplicates(values, count))
        return (free(values), 0);
    *out_values = values;
    *out_count = count;
    return (1);
}

static int cmp_int(const void *a, const void *b)
{
    const int *ia;
    const int *ib;

    ia = (const int *)a;
    ib = (const int *)b;
    if (*ia < *ib)
        return (-1);
    if (*ia > *ib)
        return (1);
    return (0);
}

static int binary_search(const int *arr, int size, int value)
{
    int left;
    int right;
    int mid;

    left = 0;
    right = size - 1;
    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] == value)
            return (mid);
        if (arr[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return (-1);
}

int to_indexes(const int *values, int count, int **out_indexes)
{
    int *sorted;
    int *indexes;
    int i;

    sorted = malloc(sizeof(int) * count);
    indexes = malloc(sizeof(int) * count);
    if (!sorted || !indexes)
        return (free(sorted), free(indexes), 0);
    memcpy(sorted, values, sizeof(int) * count);
    qsort(sorted, count, sizeof(int), cmp_int);
    i = 0;
    while (i < count)
    {
        indexes[i] = binary_search(sorted, count, values[i]);
        i++;
    }
    free(sorted);
    *out_indexes = indexes;
    return (1);
}

int is_sorted(const int *values, int count)
{
    int i;

    i = 0;
    while (i + 1 < count)
    {
        if (values[i] > values[i + 1])
            return (0);
        i++;
    }
    return (1);
}

static void swap_top(t_stack *stack)
{
    int tmp;

    if (stack->size < 2)
        return ;
    tmp = stack->data[0];
    stack->data[0] = stack->data[1];
    stack->data[1] = tmp;
}

static void push_stack(t_stack *src, t_stack *dst)
{
    int value;

    if (src->size == 0)
        return ;
    value = src->data[0];
    if (dst->size > 0)
        memmove(dst->data + 1, dst->data, sizeof(int) * dst->size);
    dst->data[0] = value;
    dst->size++;
    src->size--;
    if (src->size > 0)
        memmove(src->data, src->data + 1, sizeof(int) * src->size);
}

static void rotate_stack(t_stack *stack)
{
    int first;

    if (stack->size < 2)
        return ;
    first = stack->data[0];
    memmove(stack->data, stack->data + 1, sizeof(int) * (stack->size - 1));
    stack->data[stack->size - 1] = first;
}

static void reverse_rotate_stack(t_stack *stack)
{
    int last;

    if (stack->size < 2)
        return ;
    last = stack->data[stack->size - 1];
    memmove(stack->data + 1, stack->data, sizeof(int) * (stack->size - 1));
    stack->data[0] = last;
}

void sa(t_stack *a)
{
    swap_top(a);
    write(1, "sa\n", 3);
}

void pa(t_stack *a, t_stack *b)
{
    push_stack(b, a);
    write(1, "pa\n", 3);
}

void pb(t_stack *a, t_stack *b)
{
    push_stack(a, b);
    write(1, "pb\n", 3);
}

void ra(t_stack *a)
{
    rotate_stack(a);
    write(1, "ra\n", 3);
}

void rra(t_stack *a)
{
    reverse_rotate_stack(a);
    write(1, "rra\n", 4);
}

static void sort_three(t_stack *a)
{
    int first;
    int second;
    int third;

    first = a->data[0];
    second = a->data[1];
    third = a->data[2];
    if (first > second && second < third && first < third)
        sa(a);
    else if (first > second && second > third)
    {
        sa(a);
        rra(a);
    }
    else if (first > second && second < third && first > third)
        ra(a);
    else if (first < second && second > third && first < third)
    {
        sa(a);
        ra(a);
    }
    else if (first < second && second > third && first > third)
        rra(a);
}

static int min_pos(const t_stack *a)
{
    int i;
    int min_i;

    i = 1;
    min_i = 0;
    while (i < a->size)
    {
        if (a->data[i] < a->data[min_i])
            min_i = i;
        i++;
    }
    return (min_i);
}

void sort_small(t_stack *a, t_stack *b)
{
    int pos;

    while (a->size > 3)
    {
        pos = min_pos(a);
        if (pos <= a->size / 2)
            while (pos-- > 0)
                ra(a);
        else
            while (pos++ < a->size)
                rra(a);
        pb(a, b);
    }
    if (a->size == 2 && a->data[0] > a->data[1])
        sa(a);
    if (a->size == 3)
        sort_three(a);
    while (b->size > 0)
        pa(a, b);
}

void radix_sort(t_stack *a, t_stack *b)
{
    int bits;
    int i;
    int j;
    int size;

    size = a->size;
    bits = 0;
    while (((size - 1) >> bits) != 0)
        bits++;
    i = 0;
    while (i < bits)
    {
        j = 0;
        while (j++ < size)
        {
            if (((a->data[0] >> i) & 1) == 1)
                ra(a);
            else
                pb(a, b);
        }
        while (b->size > 0)
            pa(a, b);
        i++;
    }
}

int main(int argc, char **argv)
{
    int *values;
    int *indexes;
    int count;
    t_stack a;
    t_stack b;

    if (argc < 2)
        return (0);
    if (!parse_values(argc, argv, &values, &count))
        error_and_exit();
    if (!to_indexes(values, count, &indexes))
        return (free(values), 1);
    free(values);
    a.data = indexes;
    a.size = count;
    b.data = malloc(sizeof(int) * count);
    if (!b.data)
        return (free(indexes), 1);
    b.size = 0;
    if (!is_sorted(a.data, a.size))
    {
        if (a.size <= 5)
            sort_small(&a, &b);
        else
            radix_sort(&a, &b);
    }
    return (free(a.data), free(b.data), 0);
}
