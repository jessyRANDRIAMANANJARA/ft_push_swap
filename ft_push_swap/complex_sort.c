/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:57:59 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/13 19:58:11 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void assign_final_index(t_stack_node *stack)
{
    t_stack_node *curr;
    t_stack_node *cmp;

    curr = stack;
    while (curr)
    {
        cmp = stack;
        curr->final_index = 0;
        while (cmp)
        {
            if (cmp->value < curr->value)
                curr->final_index++;
            cmp = cmp->next;
        }
        curr = curr->next;
    }
}

static int get_max_bits(t_stack_node *stack)
{
    t_stack_node *head;
    int max;
    int max_bits;

    head = stack;
    max = 0;
    while (head)
    {
        if (head->final_index > max)
            max = head->final_index;
        head = head->next;
    }
    max_bits = 0;
    while ((max >> max_bits) != 0)
        max_bits++;
    return (max_bits);
}

void radix_sort(t_stack_node **stack_a, t_stack_node **stack_b)
{
    int i;
    int j;
    int size;
    int max_bits;

    if (*stack_a == NULL)
        return;
    assign_final_index(*stack_a);
    size = stack_len(*stack_a);
    max_bits = get_max_bits(*stack_a);
    i = 0;
    while (i < max_bits)
    {
        j = 0;
        while (j++ < size)
        {
            if (((*stack_a)->final_index >> i) & 1)
                ra(stack_a, false);
            else
                pb(stack_b, stack_a, false);
        }
        while (*stack_b)
            pa(stack_a, stack_b, false);
        i++;
    }
}
