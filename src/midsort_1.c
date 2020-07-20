/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/20 02:06:28 by marvin           ###   ########.fr       */
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

void	midsort_section(t_so *so, int size, t_bool from_a, int depth)
{
	t_stack		*s;
	t_operation	push;
	t_operation	rotate;
	t_operation	rrotate;
	int			i;
	int			median;
	int			push_count;

	s = from_a == true ? so->a_stack : so->b_stack;
	median = set_median(s, size);
	rotate = from_a == true ? RA : RB;
	rrotate = from_a == true ? RRA : RRB;
	if (DEBUG_MIDSORT == true)
	{
		printf("\e[1;32mStart of sort_section\e[0m : stack is %c, size is %i, median is %i\n", \
							from_a == true ? 'A' : 'B', size, median);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	if (section_is_sorted(so, size, from_a) == true)
	{
		if (DEBUG_MIDSORT == true)
			printf("\e[1;33mEnd of sort_section\e[0m (already sorted)\n");
		return ;
	}
	else if (size == 2)
	{
		if (from_a == true)
			do_operation(so, SA);
		else
			do_operation(so, SB);
				if (DEBUG_MIDSORT == true)
		printf("\e[1;33mEnd of sort_section\e[0m (section sorted after a single swap)\n");
		return ;
	}
	push = from_a == true ? PB : PA;
	// rotate = from_a == true ? RA : RB;
	// median = set_median(s, size);
	// if (DEBUG_MIDSORT == true)
	// 	printf("Before main loop, median is %i\n", median);
	push_count = sort_section_core(so, size, from_a, median);
	if (DEBUG_MIDSORT == true)
	{
		printf("\e[1;33mAfter main loop\e[0m, %i elements pushed & %i elements rotated\n", \
				push_count, size - push_count);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);

	}
	midsort_section(so, push_count, from_a == true ? false : true, depth + 1);

	if (DEBUG_MIDSORT == true)
	{
		// printf("\e[1;33mBetween 2 recursive calls\e[0m, rotate will be called %i times.\n",
		// size - push_count);
		printf("\e[1;33mBetween 2 recursive calls\e[0m, stack is %c, size is %i, median is %i\n", \
			from_a == true ? 'A' : 'B', size, median);
		if (depth == 0)
		{
			printf("\e[1;33mDepth = 0\e[0m, will do %i rrotate\n", size - push_count);
			display_infos(*so->a_stack, *so->b_stack, *so->operations);

		}
	}
	if (rrotate == SS || rotate == SS)
		printf("The sky is falling !\n");

	if (depth == 0)
	{
		i = -1;
		while (++i < size - push_count)
			do_operation(so, rrotate);
	}
	midsort_section(so, size - push_count, from_a, depth + 1);
	i = -1;
	while (depth > -1 && ++i < size)
	{
		do_operation(so, push);
	}
	// i = -1;
	// while (++i < push_count)
	// 	do_operation(so, rotate);

	if (DEBUG_MIDSORT == true)
	{
		printf("\e[1;33mEnd of sort_section\e[0m (after recursive calls)\n");
		if (depth == 0)
		{
			printf("\e[1;33mDepth = 0\e[0m, final state :\n");
			display_infos(*so->a_stack, *so->b_stack, *so->operations);

		}
	}
}

void	midsort(t_so *so)
{
	// midsort_section(so, so->a_stack->max_size, true, 0);
	midpoint_sort(so);
	// all_b_to_a(so->a_stack, so->b_stack, so->operations);
	// rotate_minimum_on_top(so);
	if (DEBUG_MIDSORT == true)
	{
		printf("MIDSORT DONE :\n");
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
		if (stack_is_ordered(*so->a_stack) == true)
			ft_putendl("\e[1;32mStack is ordered.\e[0m");
		else
			ft_putendl("\e[1;31mStack is not ordered.\e[0m");
	}
}