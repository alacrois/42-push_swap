/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 11:05:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_bool		a_in_b_1(t_so *so, t_section *section, int *pushed_to_b)
{
	int				median;
	int				i;

	indexed_on_top(so, get_element_index(so->a_stack, \
						section->first_elem), true);
	median = set_median(so->a_stack, section->size);
	if (section->size == 2)
	{
		operation(so, SA);
		section->first_elem = nb_at_index_mod(so->a_stack, 1);
		section->last_elem = nb_at_index_mod(so->a_stack, 2);
	}
	if (section_sorted(so, *section, true) == true)
		return (true);
	if (check_simple_sort(so, section, true) == true)
		return (true);
	*pushed_to_b = sort_by_median(so, true, section->size, median);
	section->size -= *pushed_to_b;
	operation(so, RRA);
	section->last_elem = nb_at_index_mod(so->a_stack, 1);
	i = 0;
	while (++i < section->size)
		operation(so, RRA);
	return (false);
}

static void			a_in_b(t_so *so, t_section *section)
{
	int				pushed_to_b;
	t_section		new_b_section;
	t_bool			sorted;

	if (a_in_b_1(so, section, &pushed_to_b) == true)
		return ;
	section->first_elem = nb_at_index_mod(so->a_stack, 1);
	sorted = section_sorted(so, *section, true);
	while (sorted == false)
	{
		a_in_b(so, section);
		sorted = section_sorted(so, *section, true);
	}
	new_b_section.size = pushed_to_b;
	new_b_section.first_elem = nb_at_index_mod(so->b_stack, 1);
	new_b_section.last_elem = nb_at_index_mod(so->b_stack, pushed_to_b);
	sorted = b_in_a(so, &new_b_section);
	while (sorted == false)
	{
		indexed_on_top(so, get_element_index(so->a_stack, \
						stack_minimum(so->a_stack)), true);
		sorted = b_in_a(so, &new_b_section);
	}
}

static t_bool		b_in_a_1(t_so *so, t_section *section, int *pushed_to_a)
{
	int				median;
	int				i;

	indexed_on_top(so, get_element_index(so->b_stack, \
							section->first_elem), false);
	median = set_median(so->b_stack, section->size);
	if (section->size == 2)
	{
		operation(so, SB);
		section->first_elem = nb_at_index_mod(so->b_stack, 1);
		section->last_elem = nb_at_index_mod(so->b_stack, 2);
	}
	if (section_sorted(so, *section, false) == true)
	{
		i = -1;
		while (++i < section->size)
			operation(so, PA);
		return (true);
	}
	if (check_simple_sort(so, section, false) == true)
		return (true);
	*pushed_to_a = sort_by_median(so, false, section->size, median);
	section->size -= *pushed_to_a;
	return (false);
}

t_bool				b_in_a(t_so *so, t_section *section)
{
	int				pushed_to_a;
	t_section		new_a_section;

	if (b_in_a_1(so, section, &pushed_to_a) == true)
		return (true);
	section->last_elem = nb_at_index_mod(so->b_stack, 0);
	section->first_elem = nb_at_index_mod(so->b_stack, 1 - section->size);
	rotate_elem_on_top(so, false, section->first_elem);
	new_a_section.size = pushed_to_a;
	new_a_section.first_elem = nb_at_index_mod(so->a_stack, 1);
	new_a_section.last_elem = nb_at_index_mod(so->a_stack, pushed_to_a);
	while (section_sorted(so, new_a_section, true) == false)
		a_in_b(so, &new_a_section);
	return (false);
}
