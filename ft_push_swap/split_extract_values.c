/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_extract_values.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandri2 <hrandri2@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 00:30:07 by tusandri          #+#    #+#             */
/*   Updated: 2026/04/20 19:18:47 by hrandri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_push_swap.h"

static int	handle_flag_assignment(char *arg, char **flag)
{
	if (!is_valid_flag(arg))
		return (-1);
	if (ft_strcmp(arg, "--bench") != 0)
	{
		if (*flag != NULL)
			return (-1);
		*flag = ft_strdup(arg);
		if (!*flag)
			return (-1);
	}
	return (0);
}

static int	count_and_validate_flags(char **split_args, char **flag)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	*flag = NULL;
	while (split_args[i])
	{
		if (ft_strncmp(split_args[i], "--", 2) == 0)
		{
			if (handle_flag_assignment(split_args[i], flag) == -1)
				return (-1);
		}
		else
			count++;
		i++;
	}
	return (count);
}

static char	**copy_values(char **split_args, int count)
{
	char	**values;
	int		i;
	int		j;

	values = malloc(sizeof(char *) * (count + 1));
	if (!values)
		return (NULL);
	i = 0;
	j = 0;
	while (split_args[i] && j < count)
	{
		if (ft_strncmp(split_args[i], "--", 2) != 0)
		{
			values[j] = ft_strdup(split_args[i]);
			if (!values[j])
			{
				while (--j >= 0)
					free(values[j]);
				return (free(values), NULL);
			}
			j++;
		}
		i++;
	}
	return (values[j] = NULL, values);
}

static bool	has_bench_flag_in_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strcmp(arr[i], "--bench") == 0)
			return (true);
		i++;
	}
	return (false);
}

char	**extract_values(char **split_args, char **flag, bool *bench)
{
	int	count;

	count = count_and_validate_flags(split_args, flag);
	if (count <= 0)
		return (NULL);
	if (has_bench_flag_in_array(split_args))
		*bench = true;
	return (copy_values(split_args, count));
}
