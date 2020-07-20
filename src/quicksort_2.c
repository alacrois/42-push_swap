/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/21 00:34:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define DEBUG_NEW_SORT false


void		do_operation(t_so *so, t_operation o)
{
	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, o);
}

void		rotate_elem_on_top(t_so *so, t_bool a_stack, int elem)
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

static int	get_tmp_min(t_so *so, int size)
{
	float	section_percent;
	int		i;
	int		max_index;
	int		min;

	min = nb_at_index_mod(so->a_stack, 1);
	section_percent = 0.33;
	max_index = (int)((float)size * section_percent) + 1;
	max_index = max_index > size ? size : max_index;
	if (DEBUG_NEW_SORT == true)
		printf("In get_tmp_min, max_index = %i (size = %i)\n", max_index, size);
	i = 0;
	while (++i < max_index)
	{
		if (nb_at_index_mod(so->a_stack, 1 + i) < min)
			min = nb_at_index_mod(so->a_stack, 1 + i);
	}
	return (min);
}

// static void	select_elements_to_remove(t_so *so, int size, int *selected)
// {
// 	int		i;
// 	int		elements[size];

// 	i = -1;
// 	while (++i < size)
// 	{
// 		elements[i] = nb_at_index_mod(so->a_stack, 1 + i);
// 		if (DEBUG_NEW_SORT == true)
// 			printf("elems[%i] = %i\n", i, elements[i]);
// 	}
// 	i = -1;
// 	while (++i < size)
// 	{
// 		if (elements[i] == 0)
// 			selected[i] = 1;
// 		else
// 			selected[i] = 0;

// 	}
// 	if (DEBUG_NEW_SORT == true)
// 	{
// 		printf("Selected to remove :\n");
// 		i = -1;
// 		while (++i < size)
// 			printf("selected[%i] = %i\n", i, selected[i]);
// 	}
// }

static void	new_sort_section_core(t_so *so, int a, int b, int c, t_bool tmp_min_found, int *selected, int i)
{
	// int		elems[size];
	// int		selected[size];
	// int		i;

	// select_elements_to_remove(elems, size, (int *)selected);
	if (selected[i] == 1)
	{
		put_in_ordered_b(so);
		if (DEBUG_NEW_SORT == true)
			printf("\e[1;33m%i is selected to remove\n\e[0m", b);
	}
	else
		do_operation(so, RA);
	
	if (true == false && a == c && tmp_min_found == false)
		printf("The sky is falling !\n");
		
	// if (b < a || tmp_min_found == false)
	// {
	// 	if (DEBUG_NEW_SORT == true)
	// 	{
	// 		printf("%i put in B !", b);
	// 		if (tmp_min_found == false)
	// 			printf("(tmp_min not found)\n");
	// 		else
	// 			printf("\n");
	// 	}
	// 	put_in_ordered_b(so);
	// }
	// else if (c < b && c > a)
	// {
	// 	// if c out of section ??
	// 	if (DEBUG_NEW_SORT == true)
	// 		printf("%i and %i swapped !\n", b, c);
	// 	do_operation(so, SA);
	// 	do_operation(so, RA);
	// }
	// else
	// {
	// 	if (DEBUG_NEW_SORT == true)
	// 		printf("OK\n");
	// 	do_operation(so, RA);
	// }
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
	int		tmp_min;
	t_bool	tmp_min_found;

	size = relative_max_index - relative_min_index;
	size = size < 0 ? size + so->a_stack->max_size + 1 : size + 1;
	
	// put_indexed_on_top(*so, relative_to_real_index(so, relative_min_index));
	put_indexed_on_top(*so, relative_to_real_index(so, relative_min_index));
	int		selected[size];
	select_elements_to_remove(so, size, (int *)selected);

	// if (nb_at_index_mod(so->a_stack, 1) > nb_at_index_mod(so->a_stack, 2))
	// 	do_operation(so, SA);
	// do_operation(so, RA);
	tmp_min = get_tmp_min(so, size);
	if (DEBUG_NEW_SORT == true)
	{
		printf("First elem in section : %i\n", nb_at_index_mod(so->a_stack, 1));
		printf("tmp_min set to %i\n", tmp_min);
	}
	i = -1;
	// while (++i < size - 1)
	tmp_min_found = true;
	while (++i < size)
	{
		// a = nb_at_index_mod(so->a_stack, so->a_stack->size);
		// b = nb_at_index_mod(so->a_stack, 1);
		// c = nb_at_index_mod(so->a_stack, 2);
		if (in_section(so, so->a_stack->size, relative_min_index, relative_max_index - so->b_stack->size) == true)
		{

			a = nb_at_index_mod(so->a_stack, so->a_stack->size);
		}
		else
		{
			tmp_min_found = false;
			a = tmp_min;
		}
		
		b = nb_at_index_mod(so->a_stack, 1);
		if (b == tmp_min)
			tmp_min_found = true;
		c = nb_at_index_mod(so->a_stack, 2);
		if (DEBUG_NEW_SORT == true)
			printf("S1 - Considering %i and comparing to %i... ", b, a);

		new_sort_section_core(so, a, b, c, tmp_min_found, selected, i);
		// if (b < a || tmp_min_found == false)
		// {
		// 	if (DEBUG_NEW_SORT == true)
		// 	{
		// 		printf("%i put in B !", b);
		// 		if (tmp_min_found == false)
		// 			printf("(tmp_min not found)\n");
		// 		else
		// 			printf("\n");
		// 	}
		// 	put_in_ordered_b(so);
		// }
		// else if (c < b && c > a)
		// {
		// 	// if c out of section ??
		// 	if (DEBUG_NEW_SORT == true)
		// 		printf("%i and %i swapped !\n", b, c);
		// 	do_operation(so, SA);
		// 	do_operation(so, RA);
		// }
		// else
		// {
		// 	if (DEBUG_NEW_SORT == true)
		// 		printf("OK\n");
		// 	do_operation(so, RA);
		// }
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