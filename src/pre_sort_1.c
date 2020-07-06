/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_sort_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/07 00:04:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

#define DEBUG_SORT false

t_bool			check_order(t_so *so)
{
	int			len;
	int			i;
	int			a;
	int			b;

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

void			rotate_minimum_on_top(t_so *so)
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

void			sort_small(t_so *so)
{
	int			len;
	t_stack		*a;
	int			min_index;

	a = so->a_stack;
	if (DEBUG_SORT == true)
	{
		ft_putendl("========== SORT TEST BEFORE ==========");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	len = so->a_stack->max_size;
	if (out_of_order(so) >= 1 && len > 3)
	{
		min_index = get_element_index(so->a_stack, so->ordered_numbers[0]);
		if (nb_at_index_mod(so->a_stack, min_index + 1, so->a_stack->size) \
			== so->ordered_numbers[len - 1])
		{
			rotate_minimum_on_top(so);
			execute_and_save_operation(a, NULL, so->operations, SA);
			// printf("Swapped min / max !\n");
		}
	}
	while (check_order(so) == false)
	{
		if (number_at_index(*a, 1) > number_at_index(*a, 2) \
			&& (number_at_index(*a, 1) != so->ordered_numbers[len - 1] \
			|| number_at_index(*a, 2) != so->ordered_numbers[0]))
		// if (number_at_index(*a, 1) > number_at_index(*a, 2)
		// 	&& (number_at_index(*a, 1) != so->ordered_numbers[len - 1]))
		{
			optimise_last_rotations(so->operations, len);
			execute_and_save_operation(a, NULL, so->operations, SA);
		}
		if (check_order(so) == false)
			execute_and_save_operation(a, NULL, so->operations, RA);
	}
	if (DEBUG_SORT == true)
	{
		ft_putendl("========== SORT TEST AFTER ==========");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
		// if (check_order(so) == false)
		// 	printf("Here, check_order(so) == false\n");
		// else
		// 	printf("Here, check_order(so) == true\n");
	}
	rotate_minimum_on_top(so);
	optimise_last_rotations(so->operations, len);
}

void			pre_sort_stack_core(t_so *so, float median_ratio)
{
	int		i;
	int		median;
	int		test_number;
	int		element_on_top;

	median = so->ordered_numbers[(int)((float)so->a_stack->max_size \
										* median_ratio)];
	i = -1;
	test_number = so->a_stack->size;
	while (++i <= test_number)
	{
		element_on_top = so->a_stack->data[so->a_stack->size - 1];
		if (element_on_top < median)
		{
			// Check last rotations (RA ==> RRA ?)
			execute_and_save_operation(so->a_stack, so->b_stack, \
										so->operations, PB);
		}
		else
			execute_and_save_operation(so->a_stack, so->b_stack, \
										so->operations, RA);
	}
}

void			pre_sort_stack(t_so *so)
{
	int		pre_sort_div;
	float	med;
	float	med_step;
	int		s;

	s = so->a_stack->max_size;
	pre_sort_div = s < 1000 ? 8 : 16;
	pre_sort_div = s < 100 ? 4 : pre_sort_div;
	pre_sort_div = s < 50 ? 2 : pre_sort_div;
	// printf("pre_sort_div = %i\n", pre_sort_div);
	med_step = 1 / (float)pre_sort_div;
	med = med_step;
	while (med < 1)
	{
		pre_sort_stack_core(so, med);
		med += med_step;
	}
	all_b_to_a(so->a_stack, so->b_stack, so->operations);
}
