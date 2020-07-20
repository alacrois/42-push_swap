/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/20 02:06:19 by marvin           ###   ########.fr       */
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
	s = a_to_b == true ? so->a_stack : so->b_stack;
	i = -1;
	pushed = 0;
	while (++i < size)
	{
		elem = nb_at_index_mod(s, 1);
		// if (DEBUG_MIDSORT == true)
		// 	printf("In sort_by_median, elem = %i, median = %i, a_to_b = %i\n",
		// 				elem, median, a_to_b == true ? 1 : 0);
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

void		a_in_b(t_so *so, t_section *section)
{
	int			median;
	int			pushed_to_b;
	int			i;
	t_section	new_b_section;
	t_bool		sorted;

	indexed_on_top(so, get_element_index(so->a_stack, section->first_elem), true);
	median = set_median(so->a_stack, section->size);
	if (DEBUG_MIDSORT == true)
		printf("In a_in_b, median = %i\n", median);
	if (section->size == 2)
	{
		do_operation(so, SA);
		section->first_elem = nb_at_index_mod(so->a_stack, 1);
		section->last_elem = nb_at_index_mod(so->a_stack, 2);
		if (DEBUG_MIDSORT == true)
			printf("In a_in_b, swapped the only 2 elements\n");
		// return ;
	}
	if (section_sorted(so, *section, true) == true)
	{
		if (DEBUG_MIDSORT == true)
			printf("Section already sorted in a_in_b, returning...\n");
		// i = -1;
		// while (++i < section->size)
		// 	do_operation(so, PA);
		// return (true);
		return ;
	}

	pushed_to_b = sort_by_median(so, true, section->size, median);
	if (DEBUG_MIDSORT == true)
	{
		printf("\e[1;35mIn a_in_b, pushed %i elements to B\e[0m\n", pushed_to_b);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);

	}
	section->size -= pushed_to_b;
	do_operation(so, RRA);
	section->last_elem = nb_at_index_mod(so->a_stack, 1);
	i = 0;
	while (++i < section->size)
		do_operation(so, RRA);
	section->first_elem = nb_at_index_mod(so->a_stack, 1);
	// ================ sorting remaining section in A before B ====
	sorted = section_sorted(so, *section, true);
	// sorted = a_in_b(so, section);
	while (sorted == false)
	{
		if (DEBUG_MIDSORT == true)
		{
			printf("\e[1;35mSection %i to %i in A not yet sorted.\e[0m\n", \
					section->first_elem, section->last_elem);
			display_infos(*so->a_stack, *so->b_stack, *so->operations);
			printf("Recursive call 'a_in_b'... \n");
		}
		// indexed_on_top(so, get_element_index(so->a_stack, stack_minimum(so->a_stack)), true);
		// sorted = a_in_b(so, section);
		a_in_b(so, section);
		sorted = section_sorted(so, *section, true);
	}

	//=========================================================
	new_b_section.size = pushed_to_b;
	new_b_section.first_elem = nb_at_index_mod(so->b_stack, 1);
	new_b_section.last_elem = nb_at_index_mod(so->b_stack, pushed_to_b);
	sorted = b_in_a(so, &new_b_section);
	// while (section_sorted(so, new_b_section, false) == false)
	while (sorted == false)
	{
		if (DEBUG_MIDSORT == true)
		{
			printf("\e[1;35mSection %i to %i in B not yet sorted.\e[0m\n", \
					new_b_section.first_elem, new_b_section.last_elem);
			display_infos(*so->a_stack, *so->b_stack, *so->operations);
			printf("Calling 'b_in_a'... (putting minimum %i on top of A)\n", \
				stack_minimum(so->a_stack));
		}
		indexed_on_top(so, get_element_index(so->a_stack, stack_minimum(so->a_stack)), true);
		sorted = b_in_a(so, &new_b_section);
	}
}

t_bool			b_in_a(t_so *so, t_section *section)
{
	int			median;
	int			pushed_to_a;
	int			i;
	t_section	new_a_section;

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
		// return ;
	}
	if (section_sorted(so, *section, false) == true)
	{
		if (DEBUG_MIDSORT == true)
			printf("Section already sorted in b_in_a, pushing all to A...\n");
		i = -1;
		while (++i < section->size)
			do_operation(so, PA);
		return (true);
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

	//=========================================================
	new_a_section.size = pushed_to_a;
	new_a_section.first_elem = nb_at_index_mod(so->a_stack, 1);
	new_a_section.last_elem = nb_at_index_mod(so->a_stack, pushed_to_a);
	while (section_sorted(so, new_a_section, true) == false)
	{
		if (DEBUG_MIDSORT == true)
		{
			printf("\e[1;33mSection %i to %i in A not yet sorted.\e[0m\n", \
					new_a_section.first_elem, new_a_section.last_elem);
			display_infos(*so->a_stack, *so->b_stack, *so->operations);
			printf("Calling 'a_in_b'...\n");
		}
		a_in_b(so, &new_a_section);
	}
	return (false);
}

void		recursive_sort_section(t_so *so, t_section section, int median)
{
	// int		i;
	t_bool	sorted;
	
	if (DEBUG_MIDSORT == true)
		printf("\e[1;33mIn 'recursive_sort_section' : section %i to %i, size = %i, median = %i\e[0m...\n", \
				section.first_elem, section.last_elem, section.size, median);
	// ========= ALL TO A ===========
	// i = -1;
	// while (++i < section.size)
	// 	do_operation(so, PA);
	//===============================
	sorted = b_in_a(so, &section);
	// while (section_sorted(so, section, false) == false)
	while (sorted == false)
	{
		if (DEBUG_MIDSORT == true)
		{
			printf("\e[1;33mSection %i to %i in B not yet sorted.\e[0m\n", \
					section.first_elem, section.last_elem);
			display_infos(*so->a_stack, *so->b_stack, *so->operations);
			printf("Calling 'b_in_a'...\n");
		}
		// b_in_a(so, &section);
		indexed_on_top(so, get_element_index(so->a_stack, stack_minimum(so->a_stack)), true);
		sorted = b_in_a(so, &section);
	}
	// When remaining section is sorted :
	// indexed_on_top(so, get_element_index(so->b_stack, section.first_elem), false);
	// i = -1;
	// while (++i < section.size)
	// 	do_operation(so, PA);
}