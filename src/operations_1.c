/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 13:45:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_so		init(t_stack *a_stack, t_stack *b_stack, t_list **operations)
{
	t_so	so;

	*b_stack = new_stack(a_stack->max_size);
	b_stack->size = 0;
	so.a_stack = a_stack;
	so.b_stack = b_stack;
	*operations = NULL;
	so.operations = operations;
	return (so);
}

static void		first_sort(t_so *so)
{
	size_t	op_len;

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
}

static void		small_sort_2(t_so *so, int *method, \
					size_t *best_len, size_t *len)
{
	first_sort(so);
	optimize_operations(so->operations);
	optimize_rotations(so->operations);
	*len = ft_lstlen(*so->operations);
	*method = *len < *best_len ? 2 : *method;
	*best_len = *len < *best_len ? *len : *best_len;
	undo_all_operations(so);
	midsort(so);
	optimize_operations(so->operations);
	optimize_rotations(so->operations);
	*len = ft_lstlen(*so->operations);
}

static void		small_sort(t_so *so)
{
	t_section	all_a;
	int			method;
	size_t		best_len;
	size_t		len;

	method = 1;
	all_a.size = so->a_stack->size;
	all_a.first_elem = nb_at_index_mod(so->a_stack, 1);
	all_a.last_elem = nb_at_index_mod(so->a_stack, 0);
	simple_sort(so, &all_a, true);
	optimize_operations(so->operations);
	optimize_rotations(so->operations);
	best_len = ft_lstlen(*so->operations);
	undo_all_operations(so);
	small_sort_2(so, &method, &best_len, &len);
	if (best_len < len)
	{
		undo_all_operations(so);
		if (method == 1)
			simple_sort(so, &all_a, true);
		else
			first_sort(so);
	}
}

t_list			*generate_operations(t_stack *a_stack)
{
	t_so		so;
	t_stack		b_stack;
	int			numbers[a_stack->max_size];
	t_list		*operations;

	so = init(a_stack, &b_stack, &operations);
	get_ordered_numbers_in_array(a_stack, numbers);
	so.ordered_numbers = numbers;
	if (so.a_stack->size <= SMALL_SORT_THRESHOLD)
		small_sort(&so);
	else
		midsort(&so);
	rotate_elem_on_top(&so, true, stack_minimum(so.a_stack));
	optimize_operations(so.operations);
	optimize_rotations(so.operations);
	free_stack(b_stack);
	return (*so.operations);
}
