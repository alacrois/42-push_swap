/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/05 19:47:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

#define DEBUG_SORT false

int			get_median(int *array, int size, float target)
{
	return (array[(int)((float)size * target)]);
}

int			pre_sort_core(t_so *so, t_bool sort_in_a_stack, int median)
{
	int		element_on_top;

	if (sort_in_a_stack == true)
		element_on_top = so->a_stack->data[so->a_stack->size - 1];
	else
		element_on_top = so->b_stack->data[so->b_stack->size - 1];
	if ((sort_in_a_stack == true && element_on_top < median) ||
		(sort_in_a_stack == false && element_on_top >= median))
	{
		if (sort_in_a_stack == true)
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
		else
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
		return (1);
	}
	else
	{
		if (sort_in_a_stack == true)
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RA);
		else
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RB);
		return (0);
	}
}

void			push_back_stack(t_so *so, t_bool sort_in_a_stack, int moves)
{
	while (moves > 0)
	{
		if (sort_in_a_stack == true && so->b_stack->size > 0)
		{
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
		}
		else if (sort_in_a_stack == false && so->a_stack->size > 0)
		{
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
		}
		moves--;
	}
}

void			rotate_back(t_so *so, t_bool sort_in_a_stack, int moves)
{
	while (moves > 0)
	{
		if (sort_in_a_stack == true)
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RRA);
		else
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RRB);
		moves--;
	}
}

void			pre_sort_stack(t_so *so, t_bool sort_in_a_stack, int fraction, \
								float median_ratio)
{
	int		median;
	int		i;
	// int		element_on_top;
	int		test_number;
	int 	push_moves;
	int 	rotate_moves;
	// float	new_median_ratio;

	// median = get_median(so->ordered_numbers, so->a_stack->max_size, (float)1 / (float)fraction);
	// median = get_median(so->ordered_numbers, so->a_stack->max_size, fraction);
	median = get_median(so->ordered_numbers, so->a_stack->max_size, median_ratio);
	// test_number = 2 * (int)((float)so->a_stack->max_size * fraction);
	test_number = 2 * (int)((float)so->a_stack->max_size / fraction);
	if (DEBUG_SORT == true)
	{

		printf("Median = %i && fraction = %i && median_ratio = %f   ", \
			median, fraction, median_ratio);
		if (sort_in_a_stack == true)
			printf(" A stack\n\n");
		else
			printf(" B stack\n\n");
	}
	// test_number = size;
	i = -1;
	push_moves = 0;
	rotate_moves = 0;
	while (++i <= test_number)
	{
		if (pre_sort_core(so, sort_in_a_stack, median) == 1)
			push_moves++;
		else
			rotate_moves++;
	}
	if (DEBUG_SORT == true)
	{
		printf("========== SORT DEBUG 1 ==========\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}


	if (fraction <= 4)
	{
		// pre_sort_stack(so, true, 0.75, true, (int)(so->a_stack->max_size / 2) + 1);
		// pre_sort_stack(so, false, 0.25, true, (int)(so->a_stack->max_size / 2) + 1);
		if (median_ratio == 0.5)
		{
			pre_sort_stack(so, true, fraction * 2, median_ratio + (float)1 / (float)(fraction * 2));
			pre_sort_stack(so, false, fraction * 2, median_ratio - (float)1 / (float)(fraction * 2));
		}
		else
		{
			pre_sort_stack(so, median_ratio > 0.5 ? true : false, fraction * 2, median_ratio + (float)1 / (float)(fraction * 2));
			pre_sort_stack(so, median_ratio > 0.5 ? true : false, fraction * 2, median_ratio - (float)1 / (float)(fraction * 2));
			// pre_sort_stack(so, sort_in_a_stack == true ? true : false, fraction * 2, median_ratio + (float)1 / (float)(fraction * 2));
			// pre_sort_stack(so, sort_in_a_stack == false ? true : false, fraction * 2, median_ratio - (float)1 / (float)(fraction * 2));

			// pre_sort_stack(so, true, fraction * 2, median_ratio + (float)1 / (float)(fraction * 2));
			// pre_sort_stack(so, false, fraction * 2, median_ratio - (float)1 / (float)(fraction * 2));
		}
		// pre_sort_stack(so, true, 0.875, true, (int)(so->a_stack->max_size / 2) + 1);
		// pre_sort_stack(so, true, 0.750, true, (int)(so->a_stack->max_size / 2) + 1);
		// pre_sort_stack(so, true, 0.625, true, (int)(so->a_stack->max_size / 2) + 1);
		// pre_sort_stack(so, false, 0.375, true, (int)(so->a_stack->max_size / 2) + 1);
		// pre_sort_stack(so, false, 0.250, true, (int)(so->a_stack->max_size / 2) + 1);
		// pre_sort_stack(so, false, 0.125, true, (int)(so->a_stack->max_size / 2) + 1);
	}

	// if (sort_in_a_stack == false)
	// {

		// rotate_back(so, sort_in_a_stack, rotate_moves);

		// if (DEBUG_SORT == true)
		// 	printf("\nPushing back %i times ...\n\n", push_moves);
		// push_back_stack(so, sort_in_a_stack, push_moves);
	// }
	// else
	// {
	// 	if (DEBUG_SORT == true)
	// 		printf("\nPushing back %i times ...\n\n", push_moves);
	// 	push_back_stack(so, sort_in_a_stack, push_moves);
	// 	rotate_back(so, sort_in_a_stack, rotate_moves);
	// }
	
	if (DEBUG_SORT == true)
		printf("\nPushing back %i times ...\n\n", push_moves);
	push_back_stack(so, sort_in_a_stack, push_moves);



	if (DEBUG_SORT == true)
	{
		printf("========== SORT DEBUG 2 ==========\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
}

t_bool			check_order(t_so *so)
{
	int			len;
	int			i;
	int			a;
	int			b;

	len = so->a_stack->max_size;
	i = 0;
	while (++i < len)
	{
		a = number_at_index(*so->a_stack, i);
		b = number_at_index(*so->a_stack, i + 1);
		// printf("b = %i, min = %i, a = %i\n", b, so->ordered_numbers[0], a);
		if ((b != so->ordered_numbers[0] || a != so->ordered_numbers[len - 1]) && a > b)
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
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, rotate_op);
}

void			pre_sort_stack_test(t_so *so)
{
	int			len;

	if (DEBUG_SORT == true)
	{
		printf("========== SORT TEST BEFORE ==========\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	len = so->a_stack->max_size;
	while (check_order(so) == false)
	{
		if (number_at_index(*so->a_stack, 1) > number_at_index(*so->a_stack, 2) \
			&& number_at_index(*so->a_stack, 1) != so->ordered_numbers[len - 1])
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, SA);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RA);
	}
	if (DEBUG_SORT == true)
	{
		printf("========== SORT TEST AFTER ==========\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	rotate_minimum_on_top(so);
}

void			pre_sort_stack_2(t_so *so, int div, float median_ratio)
{
	int		i;
	int		median;
	int		test_number;
	int 	push_moves;
	int 	rotate_moves;

	median = get_median(so->ordered_numbers, so->a_stack->max_size, median_ratio);
	// test_number = 2 * (int)((float)so->a_stack->max_size * fraction);
	test_number = 2 * (int)((float)so->a_stack->max_size / div);
	if (DEBUG_SORT == true)
	{
		printf("Median = %i && div = %i && median_ratio = %f   ", \
			median, div, median_ratio);
	}
	i = -1;
	push_moves = 0;
	rotate_moves = 0;
	test_number = so->a_stack->size;
	while (++i <= test_number)
	{
		if (pre_sort_core(so, true, median) == 1)
			push_moves++;
		else
			rotate_moves++;
	}
	if (DEBUG_SORT == true)
	{
		printf("========== SORT DEBUG 1 ==========\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	// push_back_stack(so, true, push_moves);
	// rotate_back(so, true, rotate_moves);
	// if (div < 8)
	// {

	// }
	// if (DEBUG_SORT == true)
	// {
	// 	printf("========== SORT DEBUG 2 ==========\n");
	// 	display_infos(*so->a_stack, *so->b_stack, *so->operations);
	// }
}