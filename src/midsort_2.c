/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/21 03:33:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int		get_next_to_sort_index(t_stack *s, int median)
{
	int			best_index_diff;
	int			index_diff;
	int			tmp_index;
	// int			tmp_elem;
	t_bool		found;
	int			i;

	found = false;
	i = -1;
	while (++i < s->size)
	{
		if (nb_at_index_mod(s, 1 + i) < median)
		{
			index_diff = s->size - i;
			index_diff = i < index_diff ? i : index_diff;
			if (found == false || index_diff < best_index_diff)
			{
				best_index_diff = index_diff;
				tmp_index = 1 + i;
				// tmp_elem = nb_at_index_mod(s, 1 + i);
				found = true;
			}
		}
	}
	if (found == false)
		return (-1);
	return (tmp_index);
}

static t_section	sort_a_in_b_by_median(t_so *so, t_section section)
{
	// int			i;
	int				next_to_sort_index;
	t_section		new_section;
	int				median;

	// to remove ? get next_to_sort_index from given first elem index instead of 1
	indexed_on_top(so, get_element_index(so->a_stack, section.first_elem), true);
	median = set_median(so->a_stack, section.size);
	new_section.size = 0;
	next_to_sort_index = get_next_to_sort_index(so->a_stack, median);
	if (next_to_sort_index != -1)
		new_section.last_elem = nb_at_index_mod(so->a_stack, next_to_sort_index);
	while (next_to_sort_index != -1)
	{
		indexed_on_top(so, next_to_sort_index, true);
		new_section.size++;
		new_section.first_elem = nb_at_index_mod(so->a_stack, 1);
		do_operation(so, PB);
		next_to_sort_index = get_next_to_sort_index(so->a_stack, median);
	}
	return (new_section);
}

void			sort_section_b_in_a(t_so *so, t_section section)
{
	int			i;

	if (DEBUG_MIDSORT == true)
	{
		printf("\e[1;33mSorting section %i to %i in A\e[0m...\n", \
				section.first_elem, section.last_elem);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	if (section_sorted(so, section, false) == true)
	{
		if (DEBUG_MIDSORT == true)
			printf("\e[1;32mSection %i to %i already in order, pushing to A\e[0m...\n", \
					section.first_elem, section.last_elem);
		indexed_on_top(so, get_element_index(so->b_stack, section.first_elem), false);
		i = -1;
		while (++i < section.size)
			do_operation(so, PA);
	}
	else
	{
		if (DEBUG_MIDSORT == true)
			printf("\e[1;33mSection not in order, calling recurive_sort_section\e[0m...\n");
		recursive_sort_section(so, section, set_median(so->b_stack, section.size));
	}
}

void			midpoint_sort(t_so *so)
{
	int			median;
	t_section	sections[so->a_stack->max_size];
	t_section	all_a;
	int			sections_count;

	if (DEBUG_MIDSORT == true)
	{
		printf("Starting midpoint_sort...\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	sections_count = 0;
	median = set_median(so->a_stack, so->a_stack->size);
	all_a.first_elem = nb_at_index_mod(so->a_stack, 1);
	all_a.last_elem = nb_at_index_mod(so->a_stack, 0);
	all_a.size = so->a_stack->size;
	// while (section_is_sorted(so, so->a_stack->size, true) == false)
	while (section_sorted(so, all_a, true) == false)
	{
		if (DEBUG_MIDSORT == true)
			printf("Before sort_a_in_b_by_median, all_a : fe = %i, le = %i, size = %i\n", \
						all_a.first_elem, all_a.last_elem, all_a.size);
		sections[sections_count] = sort_a_in_b_by_median(so, all_a);
		all_a.first_elem = nb_at_index_mod(so->a_stack, 1);
		all_a.last_elem = nb_at_index_mod(so->a_stack, 0);
		all_a.size = so->a_stack->size;
		if (DEBUG_MIDSORT == true)
		{
			printf("Sorted a in b with median = %i, sections_count = %i\n", median, sections_count);
			printf("Section info : first_elem = %i, last_elem = %i, size = %i\n", \
					sections[sections_count].first_elem, sections[sections_count].last_elem, \
					sections[sections_count].size);
			display_infos(*so->a_stack, *so->b_stack, *so->operations);
		}
		sections_count++;
		median = set_median(so->a_stack, so->a_stack->size);
	}
	while (--sections_count >= 0)
	{
		sort_section_b_in_a(so, sections[sections_count]);
	}
}