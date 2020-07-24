/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 13:16:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		rotate_minimum_on_top(t_so *so)
{
	int			len;
	int			min;
	int			index;
	t_operation	rotate_op;

	len = so->a_stack->max_size;
	min = so->ordered_numbers[0];
	index = get_element_index(so->a_stack, min);
	rotate_op = index - 1 <= len / 2 ? RA : RRA;
	while (number_at_index(*so->a_stack, 1) != min)
		execute_and_save_operation(so->a_stack, so->b_stack, \
									so->operations, rotate_op);
}

static void		swap_min_max(t_so *so)
{
	int			len;
	int			min_index;

	len = so->a_stack->max_size;
	if (out_of_order(so) >= 1 && len > 3)
	{
		min_index = get_element_index(so->a_stack, so->ordered_numbers[0]);
		if (nb_at_index_mod(so->a_stack, min_index + 1) \
			== so->ordered_numbers[len - 1])
		{
			rotate_minimum_on_top(so);
			execute_and_save_operation(so->a_stack, NULL, so->operations, SA);
		}
	}
}

void			sort_small(t_so *so)
{
	int			len;
	t_stack		*a;

	a = so->a_stack;
	len = so->a_stack->max_size;
	swap_min_max(so);
	while (check_order(so) == false)
	{
		if (nb_at_index_mod(a, 1) > nb_at_index_mod(a, 2) \
			&& (nb_at_index_mod(a, 1) != so->ordered_numbers[len - 1] \
			|| nb_at_index_mod(a, 2) != so->ordered_numbers[0]))
		{
			optimise_last_rotations(so->operations, len);
			execute_and_save_operation(a, NULL, so->operations, SA);
		}
		if (check_order(so) == false)
			execute_and_save_operation(a, NULL, so->operations, RA);
	}
	rotate_minimum_on_top(so);
	optimise_last_rotations(so->operations, len);
}
