/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/22 09:06:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Adapt for size > 3 ?
void		section_small_sort(t_so *so, t_section *section, t_bool a)
{
	int		i;
	int		x;
	int		y;
	t_stack	*s;
	int		min;

	s = a == true ? so->a_stack : so->b_stack;
	min = -1;
	if (DEBUG_MIDSORT == true)
			printf("\e[1;36mIn section_small_sort\e[0m\n");
	while (section_sorted(so, *section, a) == false)
	{
		i = min;
		while (++i < section->size - 1)
		{
			x = nb_at_index_mod(s, 1);
			y = nb_at_index_mod(s, 2);
			//update first elem
			if (i == min + 1)
				section->first_elem = x;
			if ((a == true && x > y) || (a == false && x < y))
				do_operation(so, a == true ? SA : SB);
			if (i < section->size - 2)
				do_operation(so, a == true ? RA : RB);
		}
		//update first elem
		if (min == -1)
			section->last_elem = nb_at_index_mod(s, 2);
		i = min;
		while (++i < section->size - 2)
		{
			do_operation(so, a == true ? RRA : RRB);
			x = nb_at_index_mod(s, 1);
			y = nb_at_index_mod(s, 2);
			if ((a == true && x > y) || (a == false && x < y))
				do_operation(so, a == true ? SA : SB);
		}
		min++;
	}
}

t_section			first_sort_a_in_b_by_median(t_so *so, t_section section)
{
	int			i;
	// int				next_to_sort_index;
	t_section		new_section;
	int				median;
	// int				count;
	int				a;
	int				b;

	// to remove ? get next_to_sort_index from given first elem index instead of 1
	median = set_median(so->a_stack, section.size);
	new_section.size = 0;
	// indexed_on_top(so, get_element_index(so->a_stack, section.first_elem), true);
	// next_to_sort_index = get_next_to_sort_index(so->a_stack, median);
	// if (next_to_sort_index != -1)
	// 	new_section.last_elem = nb_at_index_mod(so->a_stack, next_to_sort_index);
	// while (next_to_sort_index != -1)
	// {
	// 	indexed_on_top(so, next_to_sort_index, true);
	// 	new_section.size++;
	// 	new_section.first_elem = nb_at_index_mod(so->a_stack, 1);
	// 	do_operation(so, PB);
	// 	next_to_sort_index = get_next_to_sort_index(so->a_stack, median);
	// }
	// count = 0;
	i = 0;
	// while (i < section.size)
	while (get_next_to_sort_index(so->a_stack, median) != -1)
	{
		a = nb_at_index_mod(so->a_stack, 1);
		b = nb_at_index_mod(so->a_stack, 2);
		if (a < median)
		{
			do_operation(so, PB);
			if (new_section.size == 0)
				new_section.last_elem = a;
			new_section.size++;
			new_section.first_elem = a;
		}
		else if (a > b && b != so->ordered_numbers[0] && new_section.size >= 2 \
					&& nb_at_index_mod(so->b_stack, 1) < nb_at_index_mod(so->b_stack, 2))
			do_operation(so, SS);
		else
		{
			do_operation(so, RRA);
			i++;
		}
	}
	return (new_section);
}