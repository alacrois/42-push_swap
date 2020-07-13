/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/13 03:11:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define DEBUG false
#define LIMIT_DEPTH false
#define MAX_DEPTH 8

static void	put_indexed_on_top(t_so so, int index)
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
		execute_and_save_operation(a_stack, NULL, operations, rotation);
		index += step;
	}
}

void		more_and_less_than_elem(t_so *so, int max_index, int elem, int *ml_diff)
{
	int		i;
	int		tmp;

	i = 0;
	*ml_diff = 0;
	while (++i <= max_index)
	{
		tmp = number_at_index(*so->a_stack, i);
		// printf("Comparing %i and %i (elem)...\n", tmp, elem);
		if (tmp > elem)
			*ml_diff += 1;
		else if (tmp < elem)
			*ml_diff -= 1;
	}
}

float		get_median(t_so *so, int min, int max)
{
	int		min_index;
	int		max_index;
	// int		med_index;
	int		count;
	int		more_less_diff;

	min_index = get_element_index(so->a_stack, min);
	max_index = get_element_index(so->a_stack, max);
	count = max_index - min_index + 1;
	if (DEBUG == true)
		printf("in get_median, min_index = %i, max_index = %i, count = %i, min = %i, max = %i\n", \
			min_index, max_index, count, min, max);
	while (--count >= 0)
	{
		more_and_less_than_elem(so, max_index, number_at_index(*so->a_stack, 1 + count), \
								&more_less_diff);
		if (more_less_diff >= -1 && more_less_diff <= 1)
		{
			if (DEBUG == true)
				printf("get_median returns %i, more_less_diff = %i\n", \
					number_at_index(*so->a_stack, 1 + count), more_less_diff);
			return ((float)number_at_index(*so->a_stack, 1 + count));
		}
	}
	ft_exit("Could not find median !");
	return (0);
}

void		get_more_than_median(t_so *so, int index_max, t_stack *mtm, float median)
{
	int		a;
	// int		b;
	int		i;
	int		i_max;
	// float	median;


	i = -1;
	i_max = index_max / 2;
	// median = get_median(so, min, max);
	while (++i < i_max)
	{
		a = number_at_index(*so->a_stack, 1 + i);
		// b = number_at_index(so->a_stack, index_max - i);
		if ((float)a > median)
		{
			// printf("adding %i to mtm !\n", a);
			add_top(mtm, a);
		}
		// if ((float)b < median)
			// add_top(ltm, b);
	}
}

void		get_less_than_median(t_so *so, int index_max, t_stack *ltm, float median)
{
	// int		a;
	int		b;
	int		i;
	int		i_max;
	// float	median;


	i = -1;
	i_max = index_max / 2;
	// printf("index_max = %i, i_max = %i\n", index_max, i_max);
	// median = get_median(so, min, max);
	while (++i < i_max)
	{
		// a = number_at_index(so->a_stack, 1 + i);
		b = number_at_index(*so->a_stack, index_max - i);
		// if ((float)a > median)
			// add_top(mtm, a);
		if ((float)b < median)
		{
			// printf("adding %i to ltm !\n", b);
			add_top(ltm, b);
		}
	}
}

t_bool		section_in_order(t_so *so, int min_stack_index, int max_stack_index)
{
	int		i;
	int		a;
	int		b;
	int		size;
	// int		out_of_order;
	// int		index_to_swap;

	size = max_stack_index - min_stack_index;
	size = size < 0 ? size + so->a_stack->max_size : size;
	i = -1;
	// out_of_order = 0;
	while (++i < size)
	{
		a = nb_at_index_mod(so->a_stack, min_stack_index + i);
		b = nb_at_index_mod(so->a_stack, min_stack_index + i + 1);
		if (a > b)
		{
			if (DEBUG == true)
				printf("section in order returns false, %i > %i\n", a, b);
			// out_of_order++;
			// index_to_swap = min_stack_index + i;
			return (false);
		}
	}
	// if (out_of_order > 1)
	// {
	// 	if (DEBUG == true)
	// 		printf("section in order returns false with out_of_order = %i\n", out_of_order);
	// 	return (false);
	// }
	// if (out_of_order == 1)
	// {
	// 	put_indexed_on_top(*so, index_to_swap);
	// 	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, SA);
	// 	if (DEBUG == true)
	// 		printf("Swapped in section_in_order !\n");
	// }
	return (true);
}

// void		fill_to_swich(t_so *so, int max_stack_index, t_stack *more, t_stack *less)
// int		fill_to_swich(t_so *so, int max_stack_index, t_to_switch *more, t_to_switch *less)
// int		fill_to_swich(t_so *so, int max_stack_index, float median, int *mid_point_elem)
int		fill_to_swich(t_so *so, int max_stack_index, float median, int *mid_point_relative_index)
{
	// int		i;
	int		a_index;
	int		b_index;
	int		a;
	int		b;
	// float	median;
	int		count;

	a_index = 1;
	b_index = max_stack_index;
	/*
	median = get_median(so, number_at_index(*so->a_stack, 1), \
						number_at_index(*so->a_stack, max_stack_index));
	*/
	// printf("median in 'fill_to_swich' = %f\n", median);
	count = 0;
	while (a_index < b_index)
	{
		a = number_at_index(*so->a_stack, a_index);
		while ((float)a < median && a_index < b_index)
		{
			a_index++;
			a = number_at_index(*so->a_stack, a_index);
		}
		b = number_at_index(*so->a_stack, b_index);
		while ((float)b > median && a_index < b_index)
		{
			b_index--;
			b = number_at_index(*so->a_stack, b_index);
		}
		if (a >= median && b <= median && a_index < b_index)
		{
			// add_top(more, a);
			// add_top(less, b);
			so->quicksort_more[count].elem = a;
			so->quicksort_more[count].relative_index = a_index - 1;
			so->quicksort_less[count].elem = b;
			so->quicksort_less[count].relative_index = b_index - max_stack_index;
			if (DEBUG == true)
				printf("Added %i to more and %i to less\n", a, b);
			a_index++;
			b_index--;
			count++;
		}
	}
	// *mid_point_elem = number_at_index(*so->a_stack, a_index);
	if (DEBUG == true)
	{
		printf("Mid point(a) is %i at index %i\n", number_at_index(*so->a_stack, a_index), a_index);
		printf("Mid point(b) is %i at index %i\n", number_at_index(*so->a_stack, b_index), b_index);
	}
	*mid_point_relative_index = b_index - 1;
	return (count);
}

int			relative_to_real_index(t_so *so, int relative_index)
{
	int		index;
	int		stack_min_index;


	stack_min_index = get_element_index(so->a_stack, so->ordered_numbers[0]);
	index = stack_min_index + relative_index;
	index = index > so->a_stack->max_size ? \
					index - so->a_stack->max_size : index;
	index = index < 1 ? index + so->a_stack->max_size : index;
	return (index);
}

// void		quicksort_core(t_so *so, int min, int max)
void		quicksort_core(t_so *so, int min_relative_index, int max_relative_index, int depth)
// void		quicksort_core(t_so *so, int min_order_index, int max_order_index)
{
	int		i;
	int		min;
	int		max;
	int		switch_max;
	float	median;
	// int		mid_point_index;
	int		switches;
	int		relative_index;
	int		mid_point_index;
	int		mid_point_relative_index;
	int		mid_point_elem;
	// int		size;
	int		next_max;
	int		next_min;
	// int		stack_min_index;
	int		section_min_index;
	int		section_max_index;

	if (LIMIT_DEPTH == true && depth > MAX_DEPTH)
		return ;
	// stack_min_index = get_element_index(so->a_stack, so->ordered_numbers[0]);
	section_min_index = relative_to_real_index(so, min_relative_index);
	section_max_index = relative_to_real_index(so, max_relative_index);
	min = nb_at_index_mod(so->a_stack, section_min_index);
	max = nb_at_index_mod(so->a_stack, section_max_index);
	
	put_indexed_on_top(*so, get_element_index(so->a_stack, min));
	median = get_median(so, min, max);
	switches = fill_to_swich(so, get_element_index(so->a_stack, max), median, &mid_point_relative_index);

	// switch_max = more_than_med.size > less_than_med.size ?
	// 		less_than_med.size : more_than_med.size;
	switch_max = switches;

	if (DEBUG == true)
		printf("Quicksorting between %i and %i\nswitch_max = %i, median = %f\n", \
				min, max, switch_max, median);
	// printf("switch_max = %i, median = %f\n", switch_max, median);
	if (DEBUG == true)
	{
		printf("S1 \n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}

	i = -1;
	while (++i < switch_max)
	{
		// put_indexed_on_top(*so, get_element_index(so->a_stack, more_than_med.data[i]));
		put_indexed_on_top(*so, get_element_index(so->a_stack, so->quicksort_more[i].elem));
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
	}

	if (DEBUG == true)
	{
		printf("S2 \n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	i = -1;
	while (++i < switch_max)
	{
		// put_indexed_on_top(*so, get_element_index(so->a_stack, less_than_med.data[i]));
		put_indexed_on_top(*so, get_element_index(so->a_stack, so->quicksort_less[i].elem));
		// Switch :
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RRB);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
	}

	if (DEBUG == true)
	{
		printf("S3 \n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	// put_indexed_on_top(*so, get_element_index(so->a_stack, min));
	put_indexed_on_top(*so, relative_to_real_index(so, min_relative_index));
	// if min not in stack A ??

	// execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RA);

	// Put at correct indexes
	i = -1;
	relative_index = 0;
	while (++i < switch_max)
	{
		while (relative_index != so->quicksort_more[i].relative_index)
		{
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RA);
			relative_index++;
		}
		optimise_last_rotations(so->operations, so->a_stack->size);
		if (so->b_stack->size > 1)
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RRB);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
	}
	// all_b_to_a(so->a_stack, so->b_stack, so->operations);
	if (DEBUG == true)
	{
		printf("Quicksorting done : \n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
		printf("====================\n");

		printf("Reminder : min = %i, max = %i, median = %f\n", min, max, median);

		printf("mid_point_relative_index = %i\n", mid_point_relative_index);
		// ft_exit("");

		if (ft_lstlen(*so->operations) > 200)
			ft_exit("Killing program, too many operations !");
	}
	// mid_point_index = get_element_index(so->a_stack, min) + mid_point_relative_index;
	// mid_point_index = mid_point_index > so->a_stack->max_size ?
	// 					mid_point_index -  so->a_stack->max_size : mid_point_index;
	// mid_point_elem = nb_at_index_mod(so->a_stack, mid_point_index);
	// next_min = number_at_index(*so->a_stack, (mid_point_index % so->a_stack->max_size) + 1);

	mid_point_index = relative_to_real_index(so, min_relative_index + mid_point_relative_index);
	mid_point_elem = nb_at_index_mod(so->a_stack, mid_point_index);

	if (DEBUG == true)
		printf("mid_point_elem = %i\n", mid_point_elem);

	next_min = nb_at_index_mod(so->a_stack, relative_to_real_index(so, min_relative_index));
	next_max = nb_at_index_mod(so->a_stack, relative_to_real_index(so, max_relative_index));

	if (DEBUG == true)
	{
		printf("Reminder : min = %i, max = %i\n", min, max);
		printf("Considering section %i to %i...\n", next_min, mid_point_elem);
	}
	if (section_in_order(so, relative_to_real_index(so, min_relative_index), mid_point_index) == false)
	{
		// printf("Would call quicksort_core with min = %i, max = %i\n", min, mid_point_elem);
		// quicksort_core(so, min, mid_point_elem);
		quicksort_core(so, min_relative_index, min_relative_index + mid_point_relative_index, depth + 1);
	}
	else if (DEBUG == true)
		printf("Section %i to %i is in order !\n", next_min, mid_point_elem);

	// mid_point_index = get_element_index(so->a_stack, next_min);
	// mid_point_index = get_element_index(so->a_stack, mid_point_elem);
	// next_min = mid_point_elem;

	// mid_point_index = get_element_index(so->a_stack, min) + mid_point_relative_index + 1;
	// mid_point_index = mid_point_index > so->a_stack->max_size ?
	// 					mid_point_index -  so->a_stack->max_size : mid_point_index;
	// mid_point_elem = nb_at_index_mod(so->a_stack, mid_point_index);

	// mid_point_index = relative_to_real_index(so, min_relative_index + mid_point_relative_index + 1);
	mid_point_index = relative_to_real_index(so, min_relative_index + mid_point_relative_index);
	mid_point_elem = nb_at_index_mod(so->a_stack, mid_point_index);

	// mid_point_elem = number_at_index(*so->a_stack, mid_point_index);
	if (DEBUG == true)
		printf("Considering section %i to %i...\n", mid_point_elem, next_max);	
	if (section_in_order(so, mid_point_index, relative_to_real_index(so, max_relative_index)) == false)
	{
		// quicksort_core(so, mid_point_elem, max);
		// printf("Would call quicksort_core with min = %i, max = %i\n", mid_point_elem, max);
		quicksort_core(so, min_relative_index + mid_point_relative_index, max_relative_index, depth + 1);

	}
	else if (DEBUG == true)
		printf("Section %i to %i is in order !\n", mid_point_elem, next_max);	
	// ft_exit("");
}

void		min_on_top_max_at_bottom(t_so *so)
{
	put_indexed_on_top(*so, get_element_index(so->a_stack, \
						so->ordered_numbers[so->a_stack->max_size - 1]));
	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
	put_indexed_on_top(*so, get_element_index(so->a_stack, \
						so->ordered_numbers[0]));
	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RA);
}

void		new_quicksort(t_so *so)
{
	min_on_top_max_at_bottom(so);
	// quicksort_core(so, so->ordered_numbers[0],
	// 		so->ordered_numbers[so->a_stack->max_size - 1]);
	so->quicksort_less = (t_to_switch *)malloc(sizeof(t_to_switch) * so->a_stack->max_size);
	so->quicksort_more = (t_to_switch *)malloc(sizeof(t_to_switch) * so->a_stack->max_size);
	if (so->quicksort_less == NULL || so->quicksort_more == NULL)
		ft_exit("Malloc error");
	// quicksort_core(so, 0, so->a_stack->max_size - 1);
	// quicksort_core(so, so->ordered_numbers[0], so->ordered_numbers[so->a_stack->max_size - 1]);
	quicksort_core(so, 0, so->a_stack->max_size - 1, 0);
	free(so->quicksort_less);
	free(so->quicksort_more);
	rotate_minimum_on_top(so);
}