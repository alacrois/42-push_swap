/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/17 18:06:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define DEBUG_NEW_SORT false

void		do_operation(t_so *so, t_operation o)
{
	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, o);
}

static void	rotate_elem_on_top(t_so *so, t_bool a_stack, int elem)
{
	t_stack		*s;
	int			len;
	int			index;
	t_operation	rotate_op;

	s = a_stack == true ? so->a_stack : so->b_stack;
	len = s->size;
	index = get_element_index(s, elem);
	if (a_stack == true)
		rotate_op = index - 1 <= len / 2 ? RA : RRA;
	else
		rotate_op = index - 1 <= len / 2 ? RB : RRB;
	while (number_at_index(*s, 1) != elem)
		execute_and_save_operation(so->a_stack, so->b_stack, \
									so->operations, rotate_op);
}

static int	stack_max(t_stack *s)
{
	int		max;
	int		i;

	i = -1;
	max = s->data[0];
	while (++i < s->size)
	{
		if (s->data[i] > max)
			max = s->data[i];
	}
	return (max);
}

static int	max_less_than(t_stack *s, int a)
{
	int		i;
	int		tmp;

	i = -1;
	tmp = a;
	while (++i < s->size)
	{
		if ((tmp == a || s->data[i] > tmp) && s->data[i] < a)
			tmp = s->data[i];
	}
	tmp = tmp == a ? stack_max(s) : tmp;
	return (tmp);
}

void		put_in_ordered_b(t_so *so)
{
	int		a;
	int		b;

	if (so->b_stack->size <= 1)
	{
		execute_and_save_operation(so->a_stack, so->b_stack, \
							so->operations, PB);
		return ;
	}
	a = nb_at_index_mod(so->a_stack, 1);
	b = max_less_than(so->b_stack, a);
	rotate_elem_on_top(so, false, b);
	execute_and_save_operation(so->a_stack, so->b_stack, \
					so->operations, PB);
}

// static void		put_b_max_on_top(t_so *so)
// {
// 	int			max;
// 	int			i;
// 	int			index;
// 	int			len;
// 	t_operation	rotate_op;


// 	if (so->b_stack->size < 2)
// 		return ;
// 	max = stack_max(so->b_stack);
// 	len = so->b_stack->size;
// 	index = get_element_index(so->b_stack, max);
// 	rotate_op = index - 1 <= len / 2 ? RB : RRB;
// 	while (number_at_index(*so->b_stack, 1) != max)
// 		execute_and_save_operation(so->a_stack, so->b_stack,
// 									so->operations, rotate_op);
// }

static t_bool	in_section(t_so *so, int index, int section_rel_min, int section_rel_max)
{
	int			relative_index;

	section_rel_max = section_rel_max >= so->a_stack->size ? \
						section_rel_max - so->a_stack->size : section_rel_max;
	section_rel_max = section_rel_max < 0 ? \
					section_rel_max + so->a_stack->size : section_rel_max;
	section_rel_min = section_rel_min >= so->a_stack->size ? \
						section_rel_min - so->a_stack->size : section_rel_min;
	section_rel_min = section_rel_min < 0 ? \
					section_rel_min + so->a_stack->size : section_rel_min;
	relative_index = real_to_relative_index(so, index);
	if (relative_index >= section_rel_min && relative_index <= section_rel_max)
		return (true);
	else
		return (false);
}

void		new_sort_section(t_so *so, int relative_min_index, int relative_max_index)
{
	int		size;
	// int		ooo;
	int		a;
	int		b;
	int		c;
	// t_operation		rotation;
	int		i;

	size = relative_max_index - relative_min_index;
	size = size < 0 ? size + so->a_stack->max_size + 1 : size + 1;
	// put_indexed_on_top(*so, relative_to_real_index(so, relative_min_index));
	put_indexed_on_top(*so, relative_to_real_index(so, relative_min_index + 1));
	i = -1;
	while (++i < size - 1)
	{
		// a = nb_at_index_mod(so->a_stack, so->a_stack->size);
		// b = nb_at_index_mod(so->a_stack, 1);
		// c = nb_at_index_mod(so->a_stack, 2);
		a = nb_at_index_mod(so->a_stack, so->a_stack->size);
		b = nb_at_index_mod(so->a_stack, 1);
		// c = nb_at_index_mod(so->a_stack, 2);
		if (DEBUG_NEW_SORT == true)
			printf("S1 - Considering %i and comparing to %i... ", b, a);
		// if (c < b && c < a)
		// {
		// 	do_operation(so, SA);
		// 	do_operation(so, RA);
		// }
		// else if (c < b)
		if (b < a)
		{
			if (DEBUG_NEW_SORT == true)
				printf("%i put in B !\n", b);
			put_in_ordered_b(so);
		}
		else
		{
			if (DEBUG_NEW_SORT == true)
				printf("OK\n");
			do_operation(so, RA);
		}
	}
	if (so->b_stack->size > 1)
		rotate_elem_on_top(so, false, stack_max(so->b_stack));
	while (so->b_stack->size > 0)
	{
		a = nb_at_index_mod(so->a_stack, so->a_stack->size);
		b = nb_at_index_mod(so->a_stack, 1);
		c = nb_at_index_mod(so->b_stack, 1);
		if (DEBUG_NEW_SORT == true)
			printf("S2 - Considering %i and comparing to %i and %i... ", c, a, b);
		if ((c < b || in_section(so, 1, relative_min_index, relative_max_index - so->b_stack->size) == false) && \
			(c > a || in_section(so, so->a_stack->size, relative_min_index, relative_max_index - so->b_stack->size) == false))
		{
			if (DEBUG_NEW_SORT == true)
				printf("%i put in A !\n", c);
			do_operation(so, PA);
		}
		else
		{
			if (DEBUG_NEW_SORT == true)
				printf("KO\n");
			do_operation(so, RRA);
		}
	}
}