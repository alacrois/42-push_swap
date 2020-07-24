/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/13 02:10:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define DEBUG false

static void	reverse_order(t_stack s, int size)
{
	int		i;
	int		tmp;

	i = -1;
	while (++i < size)
	{
		tmp = s.data[size - 1 - i];
		s.data[size - 1 - i] = s.data[i];
		s.data[i] = tmp;
	}
}

static void	greater_than_median(t_so *so, t_stack *s, \
										int med, int size)
{
	int		i;
	int		start;
	int		index;
	int		nb;

	i = -1;
	start = get_element_index(so->a_stack, med) - size;
	start = start < 1 ? start + so->a_stack->size : start;
	while (++i <= size)
	{
		index = start + i;
		// index = index > so->a_stack->size ? index - so->a_stack->size : index;
		nb = nb_at_index_mod(so->a_stack, index);
		if (nb >= med)
		{
			add_top(s, nb);
		}
	}
}

static void	less_than_median(t_so *so, t_stack *s, \
										int med, int size)
{
	int		i;
	int		start;
	int		index;
	int		nb;

	i = -1;
	start = get_element_index(so->a_stack, med) + size;
	start = start < 1 ? start + so->a_stack->size : start;
	while (++i < size)
	{
		index = start - i;
		// index = index > so->a_stack->size ? index - so->a_stack->size : index;
		nb = nb_at_index_mod(so->a_stack, index);
		// printf("Considering %i for ltm...\n", nb);
		if (nb < med)
		{
			add_top(s, nb);
			// printf("Added %i in ltm\n", nb);
		}
	}
}

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

static t_bool	only_min_and_max(t_so *so, t_stack ltm, t_stack gtm)
{
	if (ltm.data[0] == so->ordered_numbers[0] && \
		gtm.data[0] == so->ordered_numbers[so->a_stack->max_size - 1])
		return (true);
	else
		return (false);
}

void		quicksort(t_so *so, float median_ratio, int div)
{
	t_stack	more_than_med;
	t_stack	less_than_med;
	int		median;
	int		median_order_index;
	int		median_index;
	int		size;
	int		max;
	int		tmp;
	int		i;

	printf("quicksort start : median_ratio = %f, div = %i\n", median_ratio, div);
	more_than_med = new_stack(so->a_stack->max_size);
	more_than_med.size = 0;
	less_than_med = new_stack(so->a_stack->max_size);
	less_than_med.size = 0;
	median_order_index = (int)((float)so->a_stack->max_size * median_ratio);
	median = so->ordered_numbers[median_order_index];
	printf("median = %i\n", median);
	// size = so->a_stack->size / 2;
	size = so->a_stack->size / div;
	greater_than_median(so, &more_than_med, median, size);
	less_than_median(so, &less_than_med, median, size);
	max = more_than_med.size > less_than_med.size ? \
			less_than_med.size : more_than_med.size;
	printf("max = %i\n", max);
	if (check_order(so) == true)
	{
		printf("Leaving quicksort (stack already in order)\n");
		return ;
	}
	if (max == 0)
	{
		printf("Leaving quicksort (max = 0)\n");
		return ;
	}
	else if (max == 1 && \
		only_min_and_max(so, less_than_med, more_than_med) == true)
	{
		if (more_than_med.size == 2)
		{
			less_than_med.data[0] = median;
		}
		else
		{
			printf("Leaving quicksort (only min and max)\n");
			return ;
		}
	}
	reverse_order(less_than_med, max);

	i = -1;
	while (++i < max)
		printf("mtm[%i] = %i & ltm[%i] = %i\n", i, more_than_med.data[i], i,
						less_than_med.data[i]);

	median_index = get_element_index(so->a_stack, median);
	tmp = median_index - size;
	tmp = tmp < 1 ? tmp + so->a_stack->size : tmp;
	//put_indexed_on_top(*so, tmp); // Necessary ??
	i = -1;
	while (++i < max)
	{
		put_indexed_on_top(*so, get_element_index(so->a_stack, more_than_med.data[i]));
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
	}

	printf("S1 \n");
	display_infos(*so->a_stack, *so->b_stack, *so->operations);

	i = -1;
	while (++i < max)
	{
		put_indexed_on_top(*so, get_element_index(so->a_stack, less_than_med.data[i]));
		// Switch :
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RRB);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
	}
	median_index = get_element_index(so->a_stack, median);
	// tmp = median_index - size;
	// tmp = tmp < 1 ? tmp + so->a_stack->size : tmp;
	printf("Before all_b_to_a, putting %i on top\n", so->b_stack->size);
	put_indexed_on_top(*so, median_index);

	printf("S2 Before all_b_to_a, b siz e = %i\n", so->b_stack->size);
	display_infos(*so->a_stack, *so->b_stack, *so->operations);

	all_b_to_a(so->a_stack, so->b_stack, so->operations);

	printf("S3 After all_b_to_a, b size = %i\n", so->b_stack->size);
	display_infos(*so->a_stack, *so->b_stack, *so->operations);
	
	div = div * 2;
	quicksort(so, median_ratio - (1 / (float)div), div);
	quicksort(so, median_ratio + (1 / (float)div), div);

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

void		put_at_correct_index(t_so *so, int order_index)
{
	int		nb;
	int		stack_index;
	int		min_stack_index;
	int		index_diff;

	nb = so->ordered_numbers[order_index];
	stack_index = get_element_index(so->a_stack, nb);
	if (stack_index == -1)
		ft_exit("error, stack_index not found.");
	min_stack_index = get_element_index(so->a_stack, so->ordered_numbers[0]);
	index_diff = stack_index - min_stack_index;
	index_diff = index_diff < 0 ? index_diff + so->a_stack->max_size : index_diff;
	if (index_diff != order_index)
	{
		printf("Index of '%i' WRONG (+%i relative to min)\nCorrecting...\n", nb, index_diff);
		put_indexed_on_top(*so, stack_index);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
		rotate_minimum_on_top(so);
		while (order_index > 0)
		{
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RA);
			order_index--;
		}
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
	}
	else
	{
		printf("Index of '%i' OK (+%i relative to min)\n", nb, index_diff);
	}
	
}

t_bool		section_in_order(t_so *so, int min_stack_index, int max_stack_index)
{
	int		i;
	int		a;
	int		b;
	int		size;

	size = max_stack_index - min_stack_index;
	size = size < 0 ? size + so->a_stack->max_size : size;
	i = -1;
	while (++i < size)
	{
		a = nb_at_index_mod(so->a_stack, min_stack_index + i);
		b = nb_at_index_mod(so->a_stack, min_stack_index + i + 1);
		if (a > b)
		{
			if (DEBUG == true)
				printf("section in order returns false, %i > %i\n", a, b);
			return (false);
		}
	}
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
void		quicksort_core(t_so *so, int min_relative_index, int max_relative_index)
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
		quicksort_core(so, min_relative_index, min_relative_index + mid_point_relative_index);
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
		quicksort_core(so, min_relative_index + mid_point_relative_index, max_relative_index);

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
	quicksort_core(so, 0, so->a_stack->max_size - 1);
	free(so->quicksort_less);
	free(so->quicksort_more);
}