/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:05 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/16 21:31:27 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void adaptive_flag(int disorder_percent, t_stack_node *a, t_stack_node *b)
{
	if (disorder_percent < 20)
		push_swap (&a, &b);
	else if (disorder_percent >= 20 && disorder_percent < 50)
		medium_sort(&a, &b);
	else
		radix_sort(&a, &b);
}
static void is_flag(char **arg, t_stack_node *a, t_stack_node *b, int disorder_percent)
{
	if (ft_strcmp(*arg, "--simple") == 0)
			push_swap(&a, &b);
	else if (ft_strcmp(*arg, "--medium") == 0)
		medium_sort(&a, &b);
	else if (ft_strcmp(*arg, "--complex") == 0)
		radix_sort(&a, &b);
	else if (ft_strcmp(*arg, "--adaptive") == 0)
		adaptive_flag(disorder_percent, a, b);
	else
		return ;
}

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	int		args_count;
	double disorder;

	a = NULL;
	b = NULL;
	args_count = argc;
	if (args_count > 1)
	{	
		argv++;
		args_count--;
	}
	if (1 == argc || (2 == argc && !argv[1][0]))
		return (1);
	else if (2 == argc)
		argv = ft_split(argv[1], ' ');
	stack_init(&a, argv + 1, 2 == argc);
	
	disorder = compute_disorder(a);
	int disorder_percent = disorder * 100;
	ft_printf("%d%%\n", disorder_percent);
	
	if (!stack_sorted(a))
	{
		if (stack_len(a) == 2)
			sa(&a, false);
		else if (stack_len(a) == 3)
			tiny_sort(&a);
		else
			is_flag(argv, a, b, disorder_percent);
	}
	free_stack(&a);
	return (0);
}
