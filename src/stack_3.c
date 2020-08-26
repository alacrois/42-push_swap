/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/26 18:42:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
			{
				free_stack(a_stack);
				return (true);
			}
		}
	}
	return (false);
}

int			stack_minimum(t_stack *s)
{
	int		min;
	int		i;

	min = nb_at_index_mod(s, 1);
	i = -1;
	while (++i < s->size)
	{
		if (nb_at_index_mod(s, 1 + i) < min)
			min = nb_at_index_mod(s, 1 + i);
	}
	return (min);
}

void		operation(t_so *so, t_operation o)
{
	if (((o == RB || o == RRB) && so->b_stack->size <= 1) || \
		((o == RA || o == RRA) && so->a_stack->size <= 1))
		return ;
	if (o < PA)
		stack_swap(so->a_stack, so->b_stack, o);
	else if (o < RA)
		stack_push(so->a_stack, so->b_stack, o);
	else if (o < RRA)
		stack_rotate(so->a_stack, so->b_stack, o);
	else
		stack_reverse_rotate(so->a_stack, so->b_stack, o);
	add_operation(so->operations, o);
}
