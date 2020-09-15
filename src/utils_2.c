/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 15:56:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			nb_at_index_mod(t_stack *stack, int index)
{
	int		n;

	if (index < 1)
		n = number_at_index(*stack, index + stack->size);
	else if (index > stack->size)
		n = number_at_index(*stack, index - stack->size);
	else
		n = number_at_index(*stack, index);
	return (n);
}

int			out_of_order(t_so *so)
{
	int		count;
	int		i;
	int		a;
	int		b;
	int		c;

	count = 0;
	i = 0;
	while (++i < so->a_stack->max_size)
	{
		a = nb_at_index_mod(so->a_stack, i - 1);
		b = nb_at_index_mod(so->a_stack, i);
		c = nb_at_index_mod(so->a_stack, i + 1);
		if ((c != so->ordered_numbers[0] && b > c) \
			|| (a != so->ordered_numbers[so->a_stack->max_size - 1] && a > b))
			count++;
	}
	return (count);
}

int			get_element_index(t_stack *stack, int to_find)
{
	int		index;
	int		to_compare;
	int		i;

	index = 1;
	i = stack->size;
	while (--i >= 0)
	{
		to_compare = stack->data[i];
		if (to_find == to_compare)
			return (index);
		index++;
	}
	return (-1);
}

void		inverse_order(t_so *so)
{
	int		len;
	int		i;

	len = so->a_stack->max_size;
	i = len;
	while (--i >= 2)
	{
		operation(so, PB);
		if (so->b_stack->size > 1)
			operation(so, RB);
	}
	operation(so, SA);
	while (so->b_stack->size > 0)
		operation(so, PA);
}

t_bool		check_order(t_so *so)
{
	int		len;
	int		i;
	int		a;
	int		b;

	len = so->a_stack->max_size;
	i = 0;
	while (++i <= len)
	{
		a = number_at_index(*so->a_stack, i);
		b = number_at_index(*so->a_stack, i < len ? i + 1 : 1);
		if ((b != so->ordered_numbers[0] || a != so->ordered_numbers[len - 1]) \
			&& a > b)
			return (false);
	}
	return (true);
}
