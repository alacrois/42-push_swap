/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/04 02:30:31 by marvin           ###   ########.fr       */
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