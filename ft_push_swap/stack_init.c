/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:38:48 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/02 23:16:51 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static long	ft_atol(const char *str)
{
	long	num;
	int		isneg;
	int		i;

	num = 0;
	isneg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		isneg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * isneg);
}

void	stack_init(t_stack_node **a, char **argv, bool flag_argc_2)
{
	long	nbr;
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], "--simple") == 0
			|| ft_strcmp(argv[i], "--medium") == 0
			|| ft_strcmp(argv[i], "--complex") == 0
			|| ft_strcmp(argv[i], "--adaptive") == 0
			|| ft_strcmp(argv[i], "--bench") == 0)
		{
			count++;
			if (count > 2)
				error_free(a, argv, flag_argc_2);
			i++;
			if (argv[i])
			{
				if (ft_strcmp(argv[i], "--simple") == 0
					|| ft_strcmp(argv[i], "--medium") == 0
					|| ft_strcmp(argv[i], "--complex") == 0
					|| ft_strcmp(argv[i], "--adaptive") == 0
					|| ft_strcmp(argv[i], "--bench") == 0)
				{
					count++;
					i++;
				}
			}
		}
		if (!argv[i])
			return ;
		if (error_syntax(argv[i]))
			error_free(a, argv, flag_argc_2);
		nbr = ft_atol(argv[i]);
		if ((nbr > INT_MAX || nbr < INT_MIN) || error_repetition(*a, (int)nbr))
			error_free(a, argv, flag_argc_2);
		append_node(a, (int)nbr);
		i++;
	}
}
