/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/26 21:44:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

int			parse_number(char *s, int *n)
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

static int	parse_stack_core(char **arg_p, t_stack *s, int *added)
{
	int		i;
	int		tmp;

	i = -1;
	while (arg_p[++i])
	{
		if (ft_strlen(arg_p[i]) == 0 || parse_number(arg_p[i], &tmp) == 0)
		{
			free_stack(*s);
			free_arg_parts(arg_p);
			return (-1);
		}
		s->data[s->size - *added - 1] = tmp;
		*added += 1;
	}
	free_arg_parts(arg_p);
	return (0);
}

t_stack		parse_stack(int ac, char **av, int options)
{
	t_stack	stack;
	int		i;
	char	**arg_p;
	int		added;

	stack = new_stack(get_stack_size(ac, av, options));
	i = options;
	added = 0;
	while (++i < ac)
	{
		arg_p = ft_strsplit(av[i], ' ');
		if (parse_stack_core(arg_p, &stack, &added) == -1)
			return (stack);
	}
	return (stack);
}
