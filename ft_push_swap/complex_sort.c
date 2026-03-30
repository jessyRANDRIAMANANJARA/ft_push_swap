/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 19:57:59 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/23 22:50:41 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	assign_final_index(t_stack_node *stack)
{
	t_stack_node	*curr;
	t_stack_node	*cmp;

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

static int	calc_cost(int pos, int len)
{
	if (pos <= len / 2)
		return (pos);
	return (pos - len);
}

static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

static int	get_total_cost(int ca, int cb)
{
	if ((ca >= 0 && cb >= 0) || (ca < 0 && cb < 0))
	{
		if (ft_abs(ca) > ft_abs(cb))
			return (ft_abs(ca));
		return (ft_abs(cb));
	}
	return (ft_abs(ca) + ft_abs(cb));
}

static int	find_target(t_stack_node *a, int b_idx)
{
	t_stack_node	*cur;
	int				pos;
	int				best_pos;
	int				best_idx;

	cur = a;
	pos = 0;
	best_pos = 0;
	best_idx = -1;
	while (cur)
	{
		if (cur->final_index > b_idx)
		{
			if (best_idx == -1 || cur->final_index < best_idx)
			{
				best_idx = cur->final_index;
				best_pos = pos;
			}
		}
		pos++;
		cur = cur->next;
	}
	if (best_idx != -1)
		return (best_pos);
	cur = a;
	pos = 0;
	while (cur)
	{
		if (best_idx == -1 || cur->final_index < best_idx)
		{
			best_idx = cur->final_index;
			best_pos = pos;
		}
		pos++;
		cur = cur->next;
	}
	return (best_pos);
}

static void	get_cheapest(t_stack_node *a, t_stack_node *b, int *ra, int *rb)
{
	t_stack_node	*cur;
	int				pos;
	int				la;
	int				lb;
	int				best;
	int				ca;
	int				cb;

	cur = b;
	pos = 0;
	la = stack_len(a);
	lb = stack_len(b);
	best = la + lb + 1;
	while (cur)
	{
		cb = calc_cost(pos, lb);
		ca = calc_cost(find_target(a, cur->final_index), la);
		if (get_total_cost(ca, cb) < best)
		{
			best = get_total_cost(ca, cb);
			*ra = ca;
			*rb = cb;
		}
		pos++;
		cur = cur->next;
	}
}

static void	do_double_rot(t_stack_node **a, t_stack_node **b,
				int *ca, int *cb, t_count *c)
{
	while (*ca > 0 && *cb > 0)
	{
		rr(a, b, c);
		(*ca)--;
		(*cb)--;
	}
	while (*ca < 0 && *cb < 0)
	{
		rrr(a, b, c);
		(*ca)++;
		(*cb)++;
	}
}

static void	do_single_rot(t_stack_node **a, t_stack_node **b,
				int ca, int cb, t_count *c)
{
	while (ca > 0)
	{
		ra(a, c);
		ca--;
	}
	while (ca < 0)
	{
		rra(a, c);
		ca++;
	}
	while (cb > 0)
	{
		rb(b, c);
		cb--;
	}
	while (cb < 0)
	{
		rrb(b, c);
		cb++;
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
	else if (f > s && s < t && f > t)
		ra(a, c);
	else if (f < s && s > t && f < t)
	{
		sa(a, c);
		ra(a, c);
	}
	else if (f < s && s > t && f > t)
		rra(a, c);
}

static void	final_rotate(t_stack_node **a, t_count *c)
{
	t_stack_node	*cur;
	int				min_pos;
	int				pos;
	int				len;

	cur = *a;
	min_pos = 0;
	pos = 0;
	while (cur)
	{
		if (cur->final_index == 0)
		{
			min_pos = pos;
			break ;
		}
		pos++;
		cur = cur->next;
	}
	len = stack_len(*a);
	if (min_pos <= len / 2)
		while (min_pos-- > 0)
			ra(a, c);
	else
	{
		min_pos = len - min_pos;
		while (min_pos-- > 0)
			rra(a, c);
	}
}

void	radix_sort(t_stack_node **a, t_stack_node **b, t_count *c)
{
	int	len;
	int	ca;
	int	cb;

	if (!a || !*a)
		return ;
	assign_final_index(*a);
	len = stack_len(*a);
	while (len-- > 3)
		pb(b, a, c);
	sort_three(a, c);
	while (*b)
	{
		get_cheapest(*a, *b, &ca, &cb);
		do_double_rot(a, b, &ca, &cb, c);
		do_single_rot(a, b, ca, cb, c);
		pa(a, b, c);
	}
	final_rotate(a, c);
}