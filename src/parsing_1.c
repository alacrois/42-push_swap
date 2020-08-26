/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/26 18:51:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		add_operation(t_list **operations, t_operation o)
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

static int	parse_operation(char *line, t_list **operations)
{
	if (ft_strequ(line, "sa"))
		add_operation(operations, SA);
	else if (ft_strequ(line, "sb"))
		add_operation(operations, SB);
	else if (ft_strequ(line, "ss"))
		add_operation(operations, SS);
	else if (ft_strequ(line, "pa"))
		add_operation(operations, PA);
	else if (ft_strequ(line, "pb"))
		add_operation(operations, PB);
	else if (ft_strequ(line, "ra"))
		add_operation(operations, RA);
	else if (ft_strequ(line, "rb"))
		add_operation(operations, RB);
	else if (ft_strequ(line, "rr"))
		add_operation(operations, RR);
	else if (ft_strequ(line, "rra"))
		add_operation(operations, RRA);
	else if (ft_strequ(line, "rrb"))
		add_operation(operations, RRB);
	else if (ft_strequ(line, "rrr"))
		add_operation(operations, RRR);
	else
		return (0);
	return (1);
}

t_list		*parse_operations(int fd)
{
	char	*line;
	t_list	*operations;

	operations = NULL;
	while (ft_gnl(fd, &line))
	{
		if (parse_operation(line, &operations) == 0)
		{
			free(line);
			exit_error();
			return (NULL);
		}
		free(line);
	}
	return (operations);
}

static int	parse_number(char *s, int *n)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if ((s[i] < '0' || s[i] > '9') && s[i] != '-')
			return (0);
	}
	if (is_int(s) == false || (ft_strlen(s) == 1 && s[0] == '-'))
		return (0);
	*n = ft_atoi((const char *)s);
	return (1);
}

t_stack		parse_stack(int ac, char **av, int options)
{
	t_stack	stack;
	int		i;
	int		i2;
	int		tmp;
	char	**arg_p;

	stack = new_stack(ac - 1 - options);
	i = options;
	while (++i < ac)
	{
		arg_p = ft_strsplit(av[i], ' ');
		i2 = -1;
		while (arg_p[++i2])
		{
			if (ft_strlen(arg_p[i2]) == 0 || parse_number(arg_p[i2], &tmp) == 0)
			{
				free_stack(stack);
				free_arg_parts(arg_p);
				return (stack);
			}
			stack.data[stack.size - i + options] = tmp;
		}
		free_arg_parts(arg_p);
	}
	return (stack);
}
