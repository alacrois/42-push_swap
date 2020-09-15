/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/26 21:39:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_stack_size_core(char **arg_p, int *count)
{
	int		i;
	int		tmp;

	i = -1;
	while (arg_p[++i])
	{
		if (ft_strlen(arg_p[i]) == 0 || parse_number(arg_p[i], &tmp) == 0)
		{
			free_arg_parts(arg_p);
			return (-1);
		}
		*count += 1;
	}
	free_arg_parts(arg_p);
	return (0);
}

int			get_stack_size(int ac, char **av, int options)
{
	int		count;
	int		i;
	char	**arg_p;

	i = options;
	count = 0;
	while (++i < ac)
	{
		arg_p = ft_strsplit(av[i], ' ');
		if (get_stack_size_core(arg_p, &count) == -1)
			return (0);
	}
	return (count);
}
