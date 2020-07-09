/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/09 16:44:39 by marvin           ###   ########.fr       */
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

t_bool		push_next_target(t_so so, int target, int *nt_value, int *nt_isolation)
{
	int		a_top;
	int		b_top;
	int		b_top2;
	float	i_min;

	a_top = so.a_stack->data[so.a_stack->size - 1];
	b_top = so.b_stack->size > 0 ? so.b_stack->data[so.b_stack->size - 1] : -2147483648;
	b_top2 = so.b_stack->size > 1 ? so.b_stack->data[so.b_stack->size - 2] : -2147483648;
	if (target < b_top || target < b_top2 || a_top < b_top || a_top < b_top2)
		return (false);
	i_min = (int)((so.average_isolation + so.max_isolation) / 2);
	// i_min = (int)((so.average_isolation + so.max_isolation) / 2);
	if ((a_top == nt_value[0] && nt_isolation[0] >= i_min) || \
		(a_top == nt_value[1] && nt_isolation[1] >= i_min))
		return (true);
	return (false);
}

static int	check_for_next_target(t_so so, int order_index)
{
	int		target;
	int		next_targets_value[2];
	int		next_targets_isolation[2];

	target = so.ordered_numbers[order_index];
	next_targets_value[0] = order_index + 1 < so.a_stack->max_size ? \
						so.ordered_numbers[order_index + 1] : so.ordered_numbers[0];
	next_targets_value[1] = order_index + 2 < so.a_stack->max_size ? \
						so.ordered_numbers[order_index + 2] : so.ordered_numbers[0];
	next_targets_isolation[0] = order_index + 1 < so.a_stack->max_size ? \
						so.numbers_isolation[order_index + 1] : 0;
	next_targets_isolation[1] = order_index + 2 < so.a_stack->max_size ? \
						so.numbers_isolation[order_index + 2] : 0;
						/*
	if (((so.b_stack->size > 0 && so.a_stack->data[so.a_stack->size - 1] > so.b_stack->data[so.b_stack->size - 1]) && \
		(so.b_stack->size > 1 && so.a_stack->data[so.a_stack->size - 1] > so.b_stack->data[so.b_stack->size - 2])) && \
		((so.a_stack->data[so.a_stack->size - 1] == next_targets_value[0] && \
		(float)next_targets_isolation[0] > so.average_isolation) || \
		(so.a_stack->data[so.a_stack->size - 1] == next_targets_value[1] && \
		(float)next_targets_isolation[1] > so.average_isolation))) */
	if (push_next_target(so, target, next_targets_value, next_targets_isolation) == true)
	{
		// display_infos(*so.a_stack, *so.b_stack, *so.operations);
	/*
		printf("nt put on b was %i when last on b was %i and %i before\n", so.a_stack->data[so.a_stack->size - 1], \
					so.b_stack->data[so.b_stack->size - 1], so.b_stack->size >= 2 ? so.b_stack->data[so.b_stack->size - 2] : 666);
*/
		check_swap_b(&so);
		execute_and_save_operation(so.a_stack, so.b_stack, \
			so.operations, PB);
		check_swap_b(&so);
		return (1);
	}
/*
	if (order_index + 1 < so.a_stack->max_size)
	{
		next_target = so.ordered_numbers[order_index + 1];
		if (so.a_stack->data[so.a_stack->size - 1] == next_target)
		{
			execute_and_save_operation(so.a_stack, so.b_stack, \
				so.operations, PB);
			return (1);
		}
	} */
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
	{
		execute_and_save_operation(so->a_stack, so->b_stack, \
									so->operations, SB);
		// printf("Swapped B : %i & %i\n", a, b);
	}
}
