/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/11 04:48:17 by marvin           ###   ########.fr       */
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
		if (so->ordered_numbers[i] >= min ?)
			nb_count++;
	}
	if (nb_count % 2 == 0)
	{
		median = (so->ordered_numbers[min_index + nb_count / 2] + \
				so->ordered_numbers[min_index - 1 + nb_count / 2]) / 2;
	}
	else
	{
		median = so->ordered_numbers[min_index + (nb_count - 1) / 2]
	}
	return (median);
}

void		quicksort_core(t_so *so, int min, int max)
{
	t_stack	more_than_med;
	t_stack	less_than_med;
	float	median;
	int 	max;

	more_than_med = new_stack(so->a_stack->max_size);
	more_than_med.size = 0;
	less_than_med = new_stack(so->a_stack->max_size);
	less_than_med.size = 0;
	median = get_median(so, min, max);
	put_indexed_on_top(*so, get_element_index(so->a_stack, min));
	max = (get_element_index(so->a_stack, max) + 1) / 2;
}

void		new_quicksort(t_so *so
{

})