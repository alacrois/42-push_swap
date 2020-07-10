/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/10 03:15:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_order(t_stack s)
{
	int		i;
	int		tmp;

	i = -1;
	while (++i <= s.size / 2)
	{
		tmp = s.data[s.size - i];
		s.data[s.size - i] = s.data[i];
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
	while (++i < size)
	{
		index = start + i;
		// index = index > so->a_stack->size ? index - so->a_stack->size : index;
		nb = nb_at_index_mod(so->a_stack, index, so->a_stack->size);
		printf("Considering %i for gtm...\n", nb);
		if (nb > med)
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
		printf("Considering %i for ltm...\n", nb);
		if (nb < med)
		{
			add_top(s, nb);
			printf("Added %i in ltm\n", nb);
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

void		quicksort(t_so *so)
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

	more_than_med = new_stack(so->a_stack->max_size);
	more_than_med.size = 0;
	less_than_med = new_stack(so->a_stack->max_size);
	less_than_med.size = 0;
	median_order_index = (int)((float)so->a_stack->max_size * 0.5);
	median = so->ordered_numbers[median_order_index];
	size = so->a_stack->size / 2;
	greater_than_median(so, &more_than_med, median, size);
	less_than_median(so, &less_than_med, median, size);
	max = more_than_med.size > less_than_med.size ? \
			less_than_med.size : more_than_med.size;
	printf("median = %i\n", median);
	printf("max = %i\n", max);
	reverse_order(less_than_med);
	median_index = get_element_index(so->a_stack, median);
	tmp = median_index - size;
	tmp = tmp < 1 ? tmp + so->a_stack->size : tmp;
	put_indexed_on_top(*so, tmp); // Necessary ??
	i = -1;
	while (++i < max)
	{
		put_indexed_on_top(*so, get_element_index(so->a_stack, more_than_med.data[i]));
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
	}
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
	// printf("Before all_b_to_a, putting %i on top\n", so->b_stack->size);
	put_indexed_on_top(*so, median_index); // Necessary ??
	printf("Before all_b_to_a, b size = %i\n", so->b_stack->size);
	display_infos(*so->a_stack, *so->b_stack, *so->operations);
	all_b_to_a(so->a_stack, so->b_stack, so->operations);
	printf("After all_b_to_a, b size = %i\n", so->b_stack->size);
	display_infos(*so->a_stack, *so->b_stack, *so->operations);



}