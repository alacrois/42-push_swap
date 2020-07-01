/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/01 15:09:00 by marvin           ###   ########.fr       */
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

void	display_b_stack(t_list *b_stack)
{
	int	*n;

	if (b_stack != NULL)
	{
		n = (int *)b_stack->content;
		ft_putnbr(*n);
		ft_putchar('\n');
	}
	else
		ft_putchar('\n');
}

void	display_stacks(t_list *a_stack, t_list *b_stack)
{
	int			*n;

	ft_putendl("\nStacks   A		B\n");
	while (a_stack != NULL || b_stack != NULL)
	{
		if (a_stack != NULL)
		{
			n = (int *)a_stack->content;
			ft_putstr("	 ");
			ft_putnbr(*n);
			ft_putstr("		");
		}
		else
			ft_putstr("			");
		display_b_stack(b_stack);
		if (a_stack != NULL)
			a_stack = a_stack->next;
		if (b_stack != NULL)
			b_stack = b_stack->next;
	}
	ft_putchar('\n');
}
