/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 08:36:05 by hrandri2          #+#    #+#             */
/*   Updated: 2026/04/02 23:46:45 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static void	adaptive_flag(int disorder_percent, t_stack_node **a,
				t_stack_node **b, t_count *count)
{
	if (disorder_percent < 20)
		push_swap(a, b, count);
	else if (disorder_percent >= 20 && disorder_percent < 50)
		medium_sort(a, b, count);
	else
		radix_sort(a, b, count);
}

static void	apply_sort_flag(char *arg, t_stack_node **a, t_stack_node **b,
				int disorder_percent, t_count *count)
{
	if (!arg || ft_strcmp(arg, "--adaptive") == 0)
	{
		adaptive_flag(disorder_percent, a, b, count);
		return ;
	}
	if (ft_strcmp(arg, "--simple") == 0)
		push_swap(a, b, count);
	else if (ft_strcmp(arg, "--medium") == 0)
		medium_sort(a, b, count);
	else if (ft_strcmp(arg, "--complex") == 0)
		radix_sort(a, b, count);
	else if (ft_strcmp(arg, "--bench") != 0)
	{
		write(2, "Error\n", 6);
		exit(1);
	}
	else
		adaptive_flag(disorder_percent, a, b, count);
}

static bool	has_bench_flag(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "--bench") == 0)
			return (true);
		i++;
	}
	return (false);
}

static char	*get_sort_flag(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "--", 2) == 0
			&& ft_strcmp(argv[i], "--bench") != 0)
			return (argv[i]);
		i++;
	}
	return (NULL);
}

static char	*repeat_flag(char **arg)
{
	int		i;
	int		j;
	int		count;
	int		k;
	int		count_strg;
	char	*flag[] = {"--simple", "--medium", "--complex", "--adaptive"};;

	count = 0;
	count_strg = 0;
	i = 0;
	while (arg[i])
	{
		j = i + 1;
		k = 0;
		while (k < 4)
		{
			if (ft_strcmp(flag[k], arg[i]) == 0)
			{
				count_strg++;
				if (count_strg > 1)
					return (arg[i]);
			}
			k++;
		}
		while (arg[j])
		{
			if (ft_strcmp(arg[i], arg[j]) == 0)
				return (arg[i]);
			if (ft_strcmp(arg[i], "--") == 0)
			{
				count++;
				if (count > 2 || !(arg[i][2]))
					return (arg[i]);
			}
			j++;
		}
		i++;
	}
	return (NULL);
}

static bool	check_flags(int argc, char **argv, t_args *args)
{
	int	start;

	if (repeat_flag(argv))
	{
		ft_printf("Error\n");
		return (true);
	}
	args->flag = get_sort_flag(argc, argv);
	args->bench = has_bench_flag(argc, argv);
	args->values = NULL;
	args->free_values = false;
	if (argc < 2)
		return (true);
	start = 1;
	while (start < argc && ft_strncmp(argv[start], "--", 2) == 0)
		start++;
	if (start >= argc)
		return (true);
	if (start == argc - 1)
	{
		args->values = ft_split(argv[start], ' ');
		args->free_values = true;
		return (false);
	}
	args->values = argv + start;
	return (false);
}

static double	run_sort(t_sort_data *data)
{
	double	disorder;
	int		disorder_percent;

	disorder = compute_disorder(*data->a);
	disorder_percent = (int)(disorder * 100);
	if (stack_sorted(*data->a))
		return (disorder);
	if (stack_len(*data->a) == 2)
		sa(data->a, data->count);
	else if (stack_len(*data->a) == 3)
		tiny_sort(data->a, data->count);
	else
		apply_sort_flag(data->flag, data->a, data->b,
			disorder_percent, data->count);
	return (disorder);
}

static void	cleanup(t_stack_node **a, char **values, bool free_values)
{
	int	i;

	free_stack(a);
	if (free_values && values)
	{
		i = 0;
		while (values[i])
			free(values[i++]);
		free(values);
	}
}

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;
	t_args			args;
	t_count			count;
	t_sort_data		data;
	double			disorder;

	if (argc < 2)
		return (1);
	if (check_flags(argc, argv, &args))
		return (0);
	a = NULL;
	b = NULL;
	count = (t_count){0};
	stack_init(&a, args.values, args.free_values);
	data = (t_sort_data){&a, &b, args.flag, &count};
	disorder = run_sort(&data);
	if (args.bench)
		bench_mode(disorder, args.flag, &count);
	cleanup(&a, args.values, args.free_values);
	return (0);
}
