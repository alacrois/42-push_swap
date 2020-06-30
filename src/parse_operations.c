/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/06/30 16:59:46 by marvin           ###   ########.fr       */
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
		// if (ft_strequ((const char *)line, "secret password"))
		// 	return ;
		// printf("line = %s\n", line);
		free(line);
	}
	return (operations);
}