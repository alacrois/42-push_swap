/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/05 20:17:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_bool		is_ordered(t_list *stack)
{
	int		a;
	int		b;

	if (stack == NULL)
		return (true);
	a = *(int *)(stack->content);
	stack = stack->next;
	while (stack != NULL)
	{
		b = *(int *)(stack->content);
		if (a > b)
			return (false);
		stack = stack->next;
		a = b;
	}
	return (true);
}

t_bool		stack_is_ordered(t_stack stack)
{
	int		a;
	int		b;
	int		index;

	if (stack.size == 0)
		return (true);
	index = -1;
	while (++index < stack.size - 1)
	{
		a = stack.data[index];
		b = stack.data[index + 1];
		if (a < b)
			return (false);
	}
	return (true);
}

t_bool		stack_has_duplicates(t_stack a_stack)
{
	int		i1;
	int		i2;

	i1 = -1;
	while (++i1 < a_stack.size)
	{
		i2 = -1;
		while (++i2 < a_stack.size)
		{
			if (a_stack.data[i1] == a_stack.data[i2] && i1 != i2)
				return (true);
		}
	}
	return (false);
}
