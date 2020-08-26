/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/26 21:08:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			free_arg_parts(char **arg_parts)
{
	int			i;

	i = -1;
	while (arg_parts[++i])
		free(arg_parts[i]);
	free(arg_parts);
}

void			add_operation(t_list **operations, t_operation o)
{
	if (*operations == NULL)
	{
		*operations = ft_lstnew((const void *)&o, sizeof(t_operation));
	}
	else
	{
		ft_lstaddend(operations, \
			ft_lstnew((const void *)&o, sizeof(t_operation)));
	}
}

static void		init(t_so *so, int *options, int *i)
{
	*options = 0;
	*i = 1;
	so->options.color = false;
	so->options.details = false;
	so->options.display_stacks = false;
	so->options.fast = false;
	so->options.input = 0;
}

static int		parse_options_1(char **av, int i, t_so *so)
{
	if (ft_strlen(av[i]) == 2 && av[i][1] == 'v')
		so->options.display_stacks = true;
	else if (ft_strlen(av[i]) == 2 && av[i][1] == 'f')
		so->options.fast = true;
	else if (ft_strlen(av[i]) == 2 && av[i][1] == 'c')
		so->options.color = true;
	else if (ft_strlen(av[i]) == 2 && av[i][1] == 'd')
		so->options.details = true;
	else
		return (0);
	return (1);
}

int				parse_options(int ac, char **av, t_so *so)
{
	int			i;
	int			options;

	init(so, &options, &i);
	while (i < ac && av[i][0] == '-')
	{
		if (ft_strlen(av[i]) == 2 && av[i][1] == 'r')
		{
			i++;
			options++;
			if (i >= ac)
				return (-1);
			so->options.input = open(av[i], O_RDONLY);
			if (so->options.input == -1)
				return (-1);
		}
		else if (parse_options_1(av, i, so) == 0)
			return (options);
		i++;
		options++;
	}
	return (options);
}
