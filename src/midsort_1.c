/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 10:25:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int			get_next_to_sort_index(t_stack *s, int median)
{
	int				best_index_diff;
	int				index_diff;
	int				tmp_index;
	t_bool			found;
	int				i;

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
	int				next_to_sort_index;
	t_section		new_section;
	int				median;

	median = set_median(so->a_stack, section.size);
	new_section.size = 0;
	next_to_sort_index = get_next_to_sort_index(so->a_stack, median);
	if (next_to_sort_index != -1)
		new_section.last_elem = nb_at_index_mod(so->a_stack, \
									next_to_sort_index);
	while (next_to_sort_index != -1)
	{
		indexed_on_top(so, next_to_sort_index, true);
		new_section.size++;
		new_section.first_elem = nb_at_index_mod(so->a_stack, 1);
		operation(so, PB);
		next_to_sort_index = get_next_to_sort_index(so->a_stack, median);
	}
	return (new_section);
}

static void			sort_section_b_in_a(t_so *so, t_section section)
{
	int				i;

	if (section_sorted(so, section, false) == true)
	{
		indexed_on_top(so, get_element_index(so->b_stack, section.first_elem), \
												false);
		i = -1;
		while (++i < section.size)
			operation(so, PA);
	}
	else
	{
		recursive_sort_section(so, section);
	}
}

void				midsort(t_so *so)
{
	t_section		sections[so->a_stack->max_size];
	t_section		all_a;
	int				sections_count;

	sections_count = 0;
	all_a.first_elem = nb_at_index_mod(so->a_stack, 1);
	all_a.last_elem = nb_at_index_mod(so->a_stack, 0);
	all_a.size = so->a_stack->size;
	while (section_sorted(so, all_a, true) == false)
	{
		sections[sections_count] = sort_a_in_b_by_median(so, all_a);
		all_a.first_elem = nb_at_index_mod(so->a_stack, 1);
		all_a.last_elem = nb_at_index_mod(so->a_stack, 0);
		all_a.size = so->a_stack->size;
		sections_count++;
	}
	while (--sections_count >= 0)
	{
		sort_section_b_in_a(so, sections[sections_count]);
	}
}
