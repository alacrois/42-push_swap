/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/12 03:00:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		nb = nb_at_index_mod(so->a_stack, index, so->a_stack->size);
		printf("Considering %i for gtm...\n", nb);
		if (nb >= med)
		{
			add_top(s, nb);
			printf("Added %i in gtm\n", nb);
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
		nb = nb_at_index_mod(so->a_stack, index, so->a_stack->size);
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

float		get_median(t_so *so, int min, int max)
{
	int		i;
	float	median;
	int	nb_count;
	int	min_index;

	i = -1;
	nb_count = 0;
	while (so->ordered_numbers[++i] <= max)
	{
		if (so->ordered_numbers[i] == min)
			min_index = i;
		if (so->ordered_numbers[i] >= min)
			nb_count++;
	}
	printf("nb_count = %i\n", nb_count);
	if (nb_count % 2 == 0)
	{
		printf("D1\n");
		median = ((float)so->ordered_numbers[min_index + nb_count / 2] + \
				(float)so->ordered_numbers[min_index - 1 + (nb_count / 2)]) / 2;
	}
	else
	{
		printf("D2\n");
		median = so->ordered_numbers[min_index + (nb_count - 1) / 2];
	}
	return (median);
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
			printf("adding %i to mtm !\n", a);
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
	printf("index_max = %i, i_max = %i\n", index_max, i_max);
	// median = get_median(so, min, max);
	while (++i < i_max)
	{
		// a = number_at_index(so->a_stack, 1 + i);
		b = number_at_index(*so->a_stack, index_max - i);
		// if ((float)a > median)
			// add_top(mtm, a);
		if ((float)b < median)
		{
			printf("adding %i to ltm !\n", b);
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

t_bool		section_in_order(t_so *so, int min_order_index, int max_order_index)
{
	int		i;
	int		min_stack_index;
	int		size;

	i = -1;
	size = max_order_index - min_order_index;
	min_stack_index = get_element_index(so->a_stack, so->ordered_numbers[min_order_index]);
	while (++i < size)
	{
		
	}
}

// void		quicksort_core(t_so *so, int min, int max)
void		quicksort_core(t_so *so, int min_order_index, int max_order_index)
{
	t_stack	more_than_med;
	t_stack	less_than_med;
	int		i;
	int		min;
	int		max;
	int		switch_max;
	float	median;
	int		mid_point_index;

	// printf("Before put_at_correct_index\n");
	// display_infos(*so->a_stack, *so->b_stack, *so->operations);
	min = so->ordered_numbers[min_order_index];
	max = so->ordered_numbers[max_order_index];
	put_at_correct_index(so, min_order_index);
	put_at_correct_index(so, max_order_index);
	// printf("After put_at_correct_index\n");
	// put_at_correct_index(so, 2);

	display_infos(*so->a_stack, *so->b_stack, *so->operations);

	more_than_med = new_stack(so->a_stack->max_size);
	more_than_med.size = 0;
	less_than_med = new_stack(so->a_stack->max_size);
	less_than_med.size = 0;
	put_indexed_on_top(*so, get_element_index(so->a_stack, min));
	median = get_median(so, min, max);
	get_more_than_median(so, get_element_index(so->a_stack, max), &more_than_med, median);
	get_less_than_median(so, get_element_index(so->a_stack, max), &less_than_med, median);

	switch_max = more_than_med.size > less_than_med.size ? \
			less_than_med.size : more_than_med.size;
	printf("switch_max = %i, median = %f\n", switch_max, median);
	printf("S1 \n");
	display_infos(*so->a_stack, *so->b_stack, *so->operations);

	i = -1;
	while (++i < switch_max)
	{
		put_indexed_on_top(*so, get_element_index(so->a_stack, more_than_med.data[i]));
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
	}

	printf("S2 \n");
	display_infos(*so->a_stack, *so->b_stack, *so->operations);

	i = -1;
	while (++i < switch_max)
	{
		put_indexed_on_top(*so, get_element_index(so->a_stack, less_than_med.data[i]));
		// Switch :
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RRB);
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
	}

	put_indexed_on_top(*so, get_element_index(so->a_stack, min));
	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RA);

	printf("S3 \n");
	display_infos(*so->a_stack, *so->b_stack, *so->operations);

	all_b_to_a(so->a_stack, so->b_stack, so->operations);
	// if 'section' in order == false ---> quicksort_core(section)
	mid_point_index = (min_order_index + max_order_index) / 2;
	if (section_in_order(so, min_order_index, mid_point_index) == false)
		quicksort_core(so, min_order_index, mid_point_index);
	if (section_in_order(so, mid_point_index, max_order_index) == false)
		quicksort_core(so, mid_point_index, max_order_index);
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
	quicksort_core(so, 0, so->a_stack->max_size - 1);
}