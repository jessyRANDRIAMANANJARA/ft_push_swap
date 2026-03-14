/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:05 by hrandri2          #+#    #+#             */
/*   Updated: 2026/03/14 13:15:50 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"


static void is_flag(char **arg, t_stack_node *a, t_stack_node *b)
{
	if (ft_strcmp(*arg, "--simple") == 0)
			push_swap(&a, &b);
	else if (ft_strcmp(*arg, "--medium") == 0)
		medium_sort(&a, &b);
	else if (ft_strcmp(*arg, "--complex") == 0)
		radix_sort(&a, &b);
	else
		return ;
}



// static bool	is_simple_flag(char *arg)
// {
// 	return (arg && ft_strcmp(arg, "--simple") == 0);
// }

// static bool	is_medium_flag(char *arg)
// {
// 	return (arg && ft_strcmp(arg, "--medium") == 0);
// }

// static bool	is_complex_flag(char *arg)
// {
// 	return (arg && ft_strcmp(arg, "--complex") == 0);
// }

/*
	if (!stack_sorted(a))
	{
		if (stack_len(a) == 2)
			sa(&a, false);
		else if (stack_len(a) == 3)
			tiny_sort(&a);
		else if (disorder > 0.2 && disorder < 0.5)
			medium_sort(&a, &b);
		else if (disorder > 0.5)
			radix_sort(&a, &b);
		else
			push_swap(&a, &b);
	}
*/

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	char		**args;
	int		args_count;
	double disorder;

	a = NULL;
	b = NULL;
	args = argv;
	args_count = argc;
	if (args_count > 1)
	{	
		args++;
		args_count--;
	}
	if (1 == args_count || (2 == args_count && !args[1][0]))
		return (1);
	else if (2 == args_count)
		args = ft_split(args[1], ' ');
	stack_init(&a, args + 1, 2 == args_count);
	disorder = compute_disorder(a);

	ft_printf("%.2f\n", disorder);
	if (!stack_sorted(a))
	{
		if (stack_len(a) == 2)
			sa(&a, false);
		else if (stack_len(a) == 3)
			tiny_sort(&a);
		else
			is_flag(args, a, b);
	}

	free_stack(&a);
}
