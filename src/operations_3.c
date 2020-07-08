/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/08 03:11:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int			nb_at_index_mod(t_stack *stack, int index, int size)
{
	int	n;

	if (index < 1)
		n = number_at_index(*stack, index + size);
	else if (index > size)
		n = number_at_index(*stack, index - size);
	else
		n = number_at_index(*stack, index);
	return (n);
}

int			out_of_order(t_so *so)
{
	int	count;
	int	i;
	int	a;
	int	b;
	int c;

	count = 0;
	i = 0;
	while (++i < so->a_stack->max_size)
	{
		a = nb_at_index_mod(so->a_stack, i - 1, so->a_stack->size);
		b = nb_at_index_mod(so->a_stack, i, so->a_stack->size);
		c = nb_at_index_mod(so->a_stack, i + 1, so->a_stack->size);
		if ((c != so->ordered_numbers[0] && b > c) \
			|| (a != so->ordered_numbers[so->a_stack->max_size - 1] && a > b))
			count++;
	}
	return (count);
}

static int	check_for_next_target(t_so so, int order_index)
{
	int		next_target;

	if (order_index + 1 < so.a_stack->max_size)
	{
		next_target = so.ordered_numbers[order_index + 1];
		if (so.a_stack->data[so.a_stack->size - 1] == next_target)
		{
			execute_and_save_operation(so.a_stack, so.b_stack, \
				so.operations, PB);
			return (1);
		}
	}
	return (0);
}

void		put_indexed_element_on_top(t_so so, int order_index, int index)
{
	int			len;
	t_stack		*a_stack;
	t_list		**operations;
	int			step;
	t_operation	rotation;

	a_stack = so.a_stack;
	operations = so.operations;
	if (a_stack->size == 0)
		return ;
	len = a_stack->size;
	step = index - 1 <= len / 2 ? -1 : 1;
	rotation = index - 1 <= len / 2 ? RA : RRA;
	while (index > 1 && index <= a_stack->size)
	{
		if (check_for_next_target(so, order_index) == 1)
			index--;
		else
		{
			execute_and_save_operation(a_stack, NULL, operations, rotation);
			index += step;
		}
	}
}

void		check_swap_b(t_so *so)
{
	int		a;
	int		b;

	if (so->b_stack->size < 2)
		return ;
	a = number_at_index(*so->b_stack, 1);
	b = number_at_index(*so->b_stack, 2);
	if (a < b)
		execute_and_save_operation(so->a_stack, so->b_stack, \
									so->operations, SB);
}
