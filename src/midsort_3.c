/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/20 00:38:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		indexed_on_top(t_so *so, int index, t_bool a)
{
	t_stack		*s;
	int			step;
	t_operation	rotation;

	s = a == true ? so->a_stack : so->b_stack;
	index = index > s->size ? index - s->size : index;
	index = index < 1 ? index + s->size : index;
	if (s->size == 0)
		return ;
	step = index - 1 <= s->size / 2 ? -1 : 1;
	if (a == true)
		rotation = index - 1 <= s->size / 2 ? RA : RRA;
	else
		rotation = index - 1 <= s->size / 2 ? RB : RRB;
	while (index > 1 && index <= s->size)
	{
		do_operation(so, rotation);
		index += step;
	}
}

int			sort_by_median(t_so *so, t_bool a_to_b, int size, int median)
{
	int				i;
	t_operation		rotation;
	t_operation		push;
	int				elem;
	t_stack			*s;
	int				pushed;

	rotation = a_to_b == true ? RA : RB;
	push = a_to_b == true ? PB : PA;
	s = a_to_b == true ? so->b_stack : so->b_stack;
	i = -1;
	pushed = 0;
	while (++i < size)
	{
		elem = nb_at_index_mod(s, 1);
		if ((a_to_b == true && elem < median) || (a_to_b == false && elem >= median))
		{
			do_operation(so, push);
			pushed++;
		}
		else
			do_operation(so, rotation);
	}
	return (pushed);
}

void		b_in_a(t_so *so, t_section *section)
{
	int		median;
	int		pushed_to_a;
	int		i;

	indexed_on_top(so, get_element_index(so->b_stack, section->first_elem), false);
	median = set_median(so->b_stack, section->size);
	if (DEBUG_MIDSORT == true)
	{
		printf("In b_in_a, median = %i\n", median);
	}
	if (section->size == 2)
	{
		do_operation(so, SB);
		section->first_elem = nb_at_index_mod(so->b_stack, 1);
		section->last_elem = nb_at_index_mod(so->b_stack, 2);
		if (DEBUG_MIDSORT == true)
			printf("In b_in_a, swapped the only 2 elements\n");
		return ;	
	}
	pushed_to_a = sort_by_median(so, false, section->size, median);
	if (DEBUG_MIDSORT == true)
	{
		printf("In b_in_a, pushed %i elements to A\n", pushed_to_a);
	}
	section->size -= pushed_to_a;
	do_operation(so, RRB);
	section->last_elem = nb_at_index_mod(so->b_stack, 1);
	i = 0;
	while (++i < section->size)
		do_operation(so, RRB);
	section->first_elem = nb_at_index_mod(so->b_stack, 1);
	// Can update first and last without rotation with nb_at_index_mod at indexes 0 & 1 - section.size

}

void		recursive_sort_section(t_so *so, t_section section, int median)
{
	int		i;
	
	if (DEBUG_MIDSORT == true)
		printf("\e[1;33mIn 'recursive_sort_section' : section %i to %i, size = %i, median = %i\e[0m...\n", \
				section.first_elem, section.last_elem, section.size, median);
	// ========= ALL TO A ===========
	// i = -1;
	// while (++i < section.size)
	// 	do_operation(so, PA);
	//===============================

	while (section_sorted(so, section, false) == false)
	{
		if (DEBUG_MIDSORT == true)
		{
			printf("\e[1;33mSection %i to %i not yet sorted.\e[0m\n", \
					section.first_elem, section.last_elem);
			display_infos(*so->a_stack, *so->b_stack, *so->operations);
			printf("Calling 'b_in_a'...\n");
		}
		b_in_a(so, &section);
	}
	// When remaining section is sorted :
	indexed_on_top(so, get_element_index(so->b_stack, section.first_elem), false);
	i = -1;
	while (++i < section.size)
		do_operation(so, PA);
}