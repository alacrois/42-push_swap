/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 16:34:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		max_less_than_in_b(t_so *so, int a, t_section *section)
{
	int			i;
	int			tmp;
	int			start_index;
	int			elem;

	i = -1;
	tmp = a;
	start_index = get_element_index(so->b_stack, section->first_elem);
	while (++i < section->size)
	{
		elem = nb_at_index_mod(so->b_stack, start_index + i);
		if ((tmp == a || elem > tmp) && elem < a)
			tmp = elem;
	}
	if (tmp == a)
	{
		tmp = nb_at_index_mod(so->b_stack, start_index + section->size);
	}
	return (tmp);
}

static int		min_more_than_in_a(t_so *so, int a, t_section *section)
{
	int			i;
	int			tmp;
	int			start_index;
	int			elem;

	i = -1;
	tmp = a;
	start_index = get_element_index(so->a_stack, section->first_elem);
	while (++i < section->size)
	{
		elem = nb_at_index_mod(so->a_stack, start_index + i);
		if ((tmp == a || elem < tmp) && elem > a)
			tmp = elem;
	}
	if (tmp == a)
	{
		tmp = nb_at_index_mod(so->a_stack, start_index + section->size);
	}
	return (tmp);
}

static void		update_section_values(int new_elem, t_section *section, \
										t_bool b)
{
	if (b == true && new_elem > section->first_elem)
		section->first_elem = new_elem;
	else if (b == true && new_elem < section->last_elem)
		section->last_elem = new_elem;
	else if (b == false && new_elem < section->first_elem)
		section->first_elem = new_elem;
	else if (b == false && new_elem > section->last_elem)
		section->last_elem = new_elem;
	section->size++;
}

void			put_in_ordered_stack(t_so *so, t_bool b, t_section *section)
{
	t_stack		*s;
	t_operation	push;
	int			new_elem;
	int			tmp;

	s = b == true ? so->b_stack : so->a_stack;
	push = b == true ? PB : PA;
	new_elem = nb_at_index_mod(b == false ? so->b_stack : so->a_stack, 1);
	if (section->size == 0)
	{
		operation(so, push);
		section->size = 1;
		section->first_elem = nb_at_index_mod(s, 1);
		section->last_elem = nb_at_index_mod(s, 1);
		return ;
	}
	tmp = b == true ? max_less_than_in_b(so, new_elem, section) : \
						min_more_than_in_a(so, new_elem, section);
	rotate_elem_on_top(so, b == true ? false : true, tmp);
	operation(so, push);
	update_section_values(new_elem, section, b);
}

void			insert_back(t_so *so, t_bool a, int unsorted_count, \
							int *rotations_count)
{
	t_operation	rotation;
	t_operation	push;
	int			x;
	int			y;

	rotation = a == true ? RRA : RRA;
	push = PA;
	while (unsorted_count > 0 && *rotations_count > 0)
	{
		x = nb_at_index_mod(so->a_stack, a == true ? 0 : 0);
		y = nb_at_index_mod(so->b_stack, 1);
		if ((a == true && y > x) || (a == false && y > x))
		{
			operation(so, push);
			unsorted_count--;
		}
		else
		{
			operation(so, rotation);
			*rotations_count = *rotations_count - 1;
		}
	}
	while (--unsorted_count >= 0)
		operation(so, push);
}
