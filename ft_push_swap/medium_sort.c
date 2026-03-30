/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/10 22:00:53 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/22 07:28:36 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	assign_index(t_stack_node *stack)
{
	t_stack_node	*curr;
	t_stack_node	*cmp;

	curr = stack;
	while (curr)
	{
		curr->final_index = 0;
		cmp = stack;
		while (cmp)
		{
			if (cmp->value < curr->value)
				curr->final_index++;
			cmp = cmp->next;
		}
		curr = curr->next;
	}
}

static void	sort_three(t_stack_node **a, t_count *c)
{
	int	f;
	int	s;
	int	t;

	f = (*a)->final_index;
	s = (*a)->next->final_index;
	t = (*a)->next->next->final_index;
	if (f > s && s < t && f < t)
		sa(a, c);
	else if (f > s && s > t)
	{
		sa(a, c);
		rra(a, c);
	}
	else if (f > s && f > t && s < t)
		ra(a, c);
	else if (f < s && s > t && f < t)
	{
		sa(a, c);
		ra(a, c);
	}
	else if (f < s && f > t)
		rra(a, c);
}

static int	find_min_in_a(t_stack_node *a)
{
	t_stack_node	*cur;
	int				min;
	int				pos;
	int				ret;

	cur = a;
	min = 2147483647;
	pos = 0;
	ret = 0;
	while (cur)
	{
		if (cur->final_index < min)
		{
			min = cur->final_index;
			ret = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (ret);
}

static int	find_max_in_b(t_stack_node *b)
{
	t_stack_node	*cur;
	int				max;
	int				pos;
	int				ret;

	cur = b;
	max = -1;
	pos = 0;
	ret = 0;
	while (cur)
	{
		if (cur->final_index > max)
		{
			max = cur->final_index;
			ret = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (ret);
}

static int	find_place_in_b(t_stack_node *b, int idx)
{
	t_stack_node	*cur;
	int				pos;
	// int				len;
	int				max_idx;
	int				max_pos;
	int				closest;
	int				closest_pos;

	if (!b)
		return (0);
	cur = b;
	pos = 0;
	// len = stack_len(b);
	max_idx = -1;
	max_pos = 0;
	closest = -1;
	closest_pos = 0;
	while (cur)
	{
		if (cur->final_index > max_idx)
		{
			max_idx = cur->final_index;
			max_pos = pos;
		}
		if (cur->final_index < idx && cur->final_index > closest)
		{
			closest = cur->final_index;
			closest_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	if (closest == -1)
		return (max_pos);
	return (closest_pos);
}

static void	calc_cost(int pos_a, int pos_b, int len_a, int len_b, int *r)
{
	if (pos_a <= len_a / 2)
	{
		r[0] = pos_a;
		r[2] = 0;
	}
	else
	{
		r[0] = len_a - pos_a;
		r[2] = 1;
	}
	if (pos_b <= len_b / 2)
	{
		r[1] = pos_b;
		r[3] = 0;
	}
	else
	{
		r[1] = len_b - pos_b;
		r[3] = 1;
	}
}

static int	total_cost(int *r)
{
	if (r[2] == r[3])
	{
		if (r[0] > r[1])
			return (r[0]);
		return (r[1]);
	}
	return (r[0] + r[1]);
}

static void	find_best(t_stack_node *a, t_stack_node *b, int *best)
{
	t_stack_node	*cur;
	int				pos_a;
	int				pos_b;
	int				r[4];
	int				len[2];

	cur = a;
	pos_a = 0;
	len[0] = stack_len(a);
	len[1] = stack_len(b);
	best[4] = 2147483647;
	while (cur)
	{
		pos_b = find_place_in_b(b, cur->final_index);
		calc_cost(pos_a, pos_b, len[0], len[1], r);
		if (total_cost(r) < best[4])
		{
			best[0] = r[0];
			best[1] = r[1];
			best[2] = r[2];
			best[3] = r[3];
			best[4] = total_cost(r);
		}
		pos_a++;
		cur = cur->next;
	}
}

static void	do_move(t_stack_node **a, t_stack_node **b, int *best, t_count *c)
{
	while (best[2] == 0 && best[3] == 0 && best[0] > 0 && best[1] > 0)
	{
		rr(a, b, c);
		best[0]--;
		best[1]--;
	}
	while (best[2] == 1 && best[3] == 1 && best[0] > 0 && best[1] > 0)
	{
		rrr(a, b, c);
		best[0]--;
		best[1]--;
	}
	while (best[0]-- > 0)
	{
		if (best[2] == 0)
			ra(a, c);
		else
			rra(a, c);
	}
	while (best[1]-- > 0)
	{
		if (best[3] == 0)
			rb(b, c);
		else
			rrb(b, c);
	}
	pb(b, a, c);
}

static void	push_to_b(t_stack_node **a, t_stack_node **b, t_count *c)
{
	int	best[5];

	pb(b, a, c);
	while (stack_len(*a) > 3)
	{
		find_best(*a, *b, best);
		do_move(a, b, best, c);
	}
}

static void	push_to_a(t_stack_node **a, t_stack_node **b, t_count *c)
{
	int	pos;
	int	len;

	while (*b)
	{
		pos = find_max_in_b(*b);
		len = stack_len(*b);
		if (pos <= len / 2)
		{
			while (pos-- > 0)
				rb(b, c);
		}
		else
		{
			while (pos++ < len)
				rrb(b, c);
		}
		pa(a, b, c);
	}
}

static void	final_rot(t_stack_node **a, t_count *c)
{
	int	pos;
	int	len;

	pos = find_min_in_a(*a);
	len = stack_len(*a);
	if (pos <= len / 2)
	{
		while (pos-- > 0)
			ra(a, c);
	}
	else
	{
		while (pos++ < len)
			rra(a, c);
	}
}

void	medium_sort(t_stack_node **a, t_stack_node **b, t_count *c)
{
	int	len;

	if (!a || !*a)
		return ;
	len = stack_len(*a);
	assign_index(*a);
	if (len == 2)
	{
		if ((*a)->final_index > (*a)->next->final_index)
			sa(a, c);
		return ;
	}
	if (len == 3)
	{
		sort_three(a, c);
		return ;
	}
	push_to_b(a, b, c);
	sort_three(a, c);
	push_to_a(a, b, c);
	final_rot(a, c);
}