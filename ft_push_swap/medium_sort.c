/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:00:53 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/13 19:08:24 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

// Helper function to find the node with the smallest value in stack a
static t_stack_node	*find_min_node(t_stack_node *a)
{
	t_stack_node	*min_node;
	int				min_value;

	if (!a)
		return (NULL);
	min_node = a;
	min_value = a->value;
	a = a->next;
	while (a)
	{
		if (a->value < min_value)
		{
			min_value = a->value;
			min_node = a;
		}
		a = a->next;
	}
	return (min_node);
}

static void	rotate_to_top(t_stack_node **a, t_stack_node *node)
{
	int	len;
	int	pos;

	len = stack_len(*a);
	pos = 0;
	t_stack_node *current = *a;
	while (current != node)
	{
		pos++;
		current = current->next;
	}
	if (pos <= len / 2)
	{
		while (*a != node)
			ra(a, false);
	}
	else
	{
		while (*a != node)
			rra(a, false);
	}
}

void	medium_sort(t_stack_node **a, t_stack_node **b)
{
	int	len;
	int	i;

	len = stack_len(*a);
	i = 0;
	while (i < len - 3)
	{
		t_stack_node *min_node = find_min_node(*a);
		rotate_to_top(a, min_node);
		pb(b, a, false);
		i++;
	}
	tiny_sort(a);
	while (*b)
		pa(a, b, false);
}
