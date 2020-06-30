/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/06/30 20:29:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	free_list(t_list **list)
{
	t_list	*elem;
	t_list	*next_elem;

	elem = *list;
	while (elem != NULL)
	{
		next_elem = elem->next;
		if (elem->content != NULL)
			free(elem->content);
		free(elem);
		elem = next_elem;
	}
	if (*list != NULL)
		*list = NULL;
}

void	display_infos(t_list	*operations, t_list *a_stack)
{
	t_operation	*o;
	int			*n;

	if (operations == NULL)
		ft_putendl("No valid operation given !");
	else
	{
		ft_putendl("Operations :");
		while (operations != NULL)
		{
			o = (t_operation *)operations->content;
			printf("%i\n", (int)*o);
			operations = operations->next;
		}
	}

	if (a_stack == NULL)
		ft_putendl("\nStack is empty !");
	else
	{
		ft_putendl("\nStack :");
		while (a_stack != NULL)
		{
			n = (int *)a_stack->content;
			printf("%i\n", *n);
			a_stack = a_stack->next;
		}
	}
	ft_putchar('\n');
}