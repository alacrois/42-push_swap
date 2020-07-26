/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 10:28:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int					sort_by_median(t_so *so, t_bool a_to_b, int size, \
									int median)
{
	int				i;
	t_operation		rotation;
	t_operation		push;
	int				elem;
	int				pushed;

	rotation = a_to_b == true ? RA : RB;
	push = a_to_b == true ? PB : PA;
	i = -1;
	pushed = 0;
	while (++i < size)
	{
		elem = nb_at_index_mod(a_to_b == true ? so->a_stack : so->b_stack, 1);
		if ((a_to_b == true && elem < median) || (a_to_b == false \
													&& elem >= median))
		{
			operation(so, push);
			pushed++;
		}
		else
			operation(so, rotation);
	}
	return (pushed);
}

t_bool				check_simple_sort(t_so *so, t_section *section, t_bool a)
{
	int				numbers[section->size];
	int				i;
	t_stack			*s;
	int				unsorted;

	i = -1;
	s = a == true ? so->a_stack : so->b_stack;
	while (++i < section->size)
		numbers[i] = nb_at_index_mod(s, 1 + i);
	unsorted = count_unsorted(numbers, section->size, a);
	if (unsorted > 20)
		return (false);
	simple_sort(so, section, a);
	return (true);
}

void				recursive_sort_section(t_so *so, t_section section)
{
	t_bool			sorted;

	sorted = b_in_a(so, &section);
	while (sorted == false)
	{
		indexed_on_top(so, get_element_index(so->a_stack, \
							stack_minimum(so->a_stack)), true);
		sorted = b_in_a(so, &section);
	}
}
