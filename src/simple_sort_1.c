/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 15:53:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void			init(t_to_sort *elems, t_stack *s, int size, \
							t_simple_sort ss)
{
	int				i;

	i = -1;
	while (++i < size)
	{
		elems[i].value = nb_at_index_mod(s, 1 + i);
		elems[i].ooo = 0;
		elems[i].used = true;
	}
	set_unsorted(elems, size, ss->a);
	while (remove_first_most_unsorted(elems, size) == 1)
		set_unsorted(elems, size, ss->a);
	ss->unsorted_count = 0;
	ss->rotations = 0;
	ss->unsorted.size = 0;
	ss->elems = elems;
}

void				simple_sort_1(t_so *so, t_section *section, \
						t_simple_sort *ss)
{
	int				i;

	i = -1;
	while (++i < section->size)
	{
		if (elems[i].used == false)
		{
			put_in_ordered_stack(so, ss->a, &(ss->unsorted));
			ss->unsorted_count++;
		}
		else
		{
			operation(so, ss->a == true ? RA : RB);
			ss->rotations += ss->a == true ? 1 : 0;
		}
	}
	if (ss->a == true)
		rotate_elem_on_top(so, false, ss->unsorted.first_elem);
	else
	{
		rotate_elem_on_top(so, false, get_max(ss->elems, section->size, true));
		rotate_elem_on_top(so, true, get_max(ss->elems, section->size, false));
		operation(so, RA);
		ss->rotations = ss->unsorted_count;
	}
}

void				simple_sort(t_so *so, t_section *section, t_bool a)
{
	t_to_sort		elems[section->size];
	int				unsorted_count;
	int				rotations;
	t_simple_sort	ss;
	t_section		unsorted;

	ss.a = a;
	init(elems, a == true ? so->a_stack : so->b_stack, section->size, &ss);
	simple_sort_1(so, section, &ss);
	insert_back(so, a, a == true ? ss->unsorted_count : \
				(section->size - ss->unsorted_count), &(ss->rotations));
	while (a == true && ss->rotations > 0)
	{
		operation(so, RRA);
		ss->rotations--;
	}
	if (a == false)
		rotate_elem_on_top(so, true, get_min(elems, section->size));
}
