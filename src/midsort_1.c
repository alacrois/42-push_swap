/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/18 18:58:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	sort_section_core(t_so *so, int size, t_bool from_a, int median)
{
	t_stack		*s;
	t_operation	push;
	t_operation	rotate;
	t_operation	rrotate;
	int			i;
	int			rotation_count;
	int			push_count;


	i = -1;
	rotation_count = 0;
	s = from_a == true ? so->a_stack : so->b_stack;
	push = from_a == true ? PB : PA;
	rotate = from_a == true ? RA : RB;
	rrotate = from_a == true ? RRA : RRB;
	push_count = 0;
	while (++i < size)
	{
		if ((from_a == true && nb_at_index_mod(s, 1) <= median) || \
			(from_a == false && nb_at_index_mod(s, 1) > median))
		{
			do_operation(so, push);
			push_count++;
		}
		else
		{
			do_operation(so, rotate);
			rotation_count++;
		}
	}
	while (rotation_count > 0)
	{
		do_operation(so, rrotate);
		rotation_count--;
	}
	return (push_count);
}

void	midsort_section(t_so *so, int size, t_bool from_a)
{
	t_stack		*s;
	t_operation	push;
	// t_operation	rotate;
	int			i;
	int			median;
	int			push_count;

	if (DEBUG_MIDSORT == true)
	{
		printf("Start of sort_section : stack is %c, size is %i\n", from_a == true ? 'A' : 'B', size);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	if (section_is_sorted(so, size, from_a) == true)
		return ;
	else if (size == 2)
	{
		if (from_a == true)
			do_operation(so, SA);
		else
			do_operation(so, SB);
		return ;
	}
	s = from_a == true ? so->a_stack : so->b_stack;
	push = from_a == true ? PB : PA;
	// rotate = from_a == true ? RA : RB;
	median = set_median(s, size);
	if (DEBUG_MIDSORT == true)
		printf("Before main loop, median is %i\n", median);
	push_count = sort_section_core(so, size, from_a, median);
	if (DEBUG_MIDSORT == true)
	{
		printf("After main loop, %i elements pushed & %i elements rotated\n", \
				push_count, size - push_count);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);

	}
	midsort_section(so, push_count, from_a == true ? false : true);
	midsort_section(so, size - push_count, from_a);
	i = -1;
	while (++i < size)
	{
		do_operation(so, push);
	}
}

void	midsort(t_so *so)
{
	midsort_section(so, so->a_stack->max_size, true);
	if (DEBUG_MIDSORT == true)
	{
		printf("MIDSORT DONE :\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);

	}
}