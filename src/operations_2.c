/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/09 16:42:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_so		init_stacks_and_operations(t_stack *a_stack, t_stack *b_stack, \
					t_list **operations, t_list **pending_b_operations)
{
	t_so	so;

	so.a_stack = a_stack;
	so.b_stack = b_stack;
	so.operations = operations;
	so.pending_b_operations = pending_b_operations;
	return (so);
}

static int		first_sort(t_so *so)
{
	size_t	op_len;

	if (so->a_stack->size >= SMALL_STACK_THRESHOLD)
		pre_sort_stack(so);
	else
	{
		if (out_of_order(so) >= 1)
		{
			sort_small(so);
			op_len = ft_lstlen(*so->operations);
			undo_all_operations(so);
			inverse_order(so);
			sort_small(so);
			if (op_len < ft_lstlen(*so->operations))
			{
				undo_all_operations(so);
				sort_small(so);
			}
		}
		else
			sort_small(so);
		return (1);
	}
	return (0);
}

static void		generate_operations_core(t_so *so)
{
	int		i;
	int		len;
	int		element_to_find_index;
	t_stack	*a_stack;

	i = -1;
	a_stack = so->a_stack;
	len = a_stack->size;
	while (++i < len)
	{
		element_to_find_index = get_element_index(a_stack, \
									so->ordered_numbers[i]);
		if (element_to_find_index != -1)
		{
			put_indexed_element_on_top(*so, i, element_to_find_index);
			check_swap_b(so);
			execute_and_save_operation(a_stack, so->b_stack, \
										so->operations, PB);
			check_swap_b(so);
		}
	}
}

static void		get_numbers_isolation(t_so *so, int *numbers_isolation)
{
	int			i;
	int			indexes[so->a_stack->max_size];
	int			isolation;
	float		average_isolation;

	i = -1;
	while (++i < so->a_stack->max_size)
		indexes[i] = get_element_index(so->a_stack, so->ordered_numbers[i]);
	i = -1;
	average_isolation = 0;
	so->max_isolation = -2147483648;
	while (++i < so->a_stack->max_size)
	{
		if (i == 0)
			isolation = 0;
		else if (i == 1)
			isolation = get_index_distance(indexes[i], indexes[i - 1], \
							so->a_stack->max_size);
		else
			isolation = get_index_distance(indexes[i], indexes[i - 1], so->a_stack->max_size) + \
							get_index_distance(indexes[i - 1], indexes[i - 2], so->a_stack->max_size);
		average_isolation += isolation;
		numbers_isolation[i] = isolation;
		if (isolation > so->max_isolation)
			so->max_isolation = isolation;
		// printf("isolation of number %i at index %i is %i\n",
		// 		so->ordered_numbers[i], indexes[i], isolation);
	}
	average_isolation = average_isolation / (float)so->a_stack->max_size;
	so->average_isolation = average_isolation;
	// printf("average_isolation = %f\n", average_isolation);
}

t_list			*generate_operations(t_stack *a_stack)
{
	t_list	*operations;
	t_list	*pending_b_operations;
	t_so	so;
	t_stack	b_stack;
	int		numbers[a_stack->max_size];
	int		numbers_isolation[a_stack->max_size];

	operations = NULL;
	pending_b_operations = NULL;
	b_stack = new_stack(a_stack->max_size);
	b_stack.size = 0;
	so = init_stacks_and_operations(a_stack, &b_stack, \
							&operations, &pending_b_operations);
	get_ordered_numbers_in_array(a_stack, numbers);
	so.ordered_numbers = numbers;

	if (first_sort(&so) == 1)
		return (operations);
	get_numbers_isolation(&so, numbers_isolation);
	so.numbers_isolation = numbers_isolation;

	generate_operations_core(&so);
	all_b_to_a(a_stack, &b_stack, &operations);
	return (operations);
}
