/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/06/30 20:38:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void		add_operation(t_list **operations, t_operation o)
{
	if (*operations == NULL)
	{
		*operations = ft_lstnew((const void *)&o, sizeof(t_operation));
	}
	else
	{
		ft_lstaddend(operations, ft_lstnew((const void *)&o, sizeof(t_operation)));
	}
	
}

int			parse_operation(char *line, t_list **operations)
{
	if (ft_strequ(line, "sa"))
		add_operation(operations, SA);
	else if (ft_strequ(line, "sb"))
		add_operation(operations, SB);
	else if (ft_strequ(line, "ss"))
		add_operation(operations, SS);
	else
		return 0;
	return 1;
}

t_list		*parse_operations()
{
	char	*line;
	t_list	*operations;

	operations = NULL;
	while (ft_gnl(0, &line))
	{
		if (parse_operation(line, &operations) == 0)
		{
			free(line);
			return (operations);
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
	*n = ft_atoi((const char *)s);
	return (1);
}

t_list		*parse_stack(int ac, char **av)
{
	t_list	*stack;
	int		i;
	int		tmp;

	stack = NULL;
	i = 0;
	while (++i < ac)
	{
		if (parse_number(av[i], &tmp) == 0)
		{
			free_list(&stack);
			return (NULL);
		}
		ft_lstaddend(&stack, ft_lstnew((const void *)&tmp, sizeof(int)));
	}
	return (stack);
}