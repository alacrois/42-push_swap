/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/22 07:02:20 by marvin           ###   ########.fr       */
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
			//update first elem at i = 0 ?
			x = nb_at_index_mod(s, 1);
			y = nb_at_index_mod(s, 2);
			if ((a == true && x > y) || (a == false && x < y))
				do_operation(so, a == true ? SA : SB);
			if (i < section->size - 2)
				do_operation(so, a == true ? RA : RB);
		}
		section->last_elem = nb_at_index_mod(s, 2);
		i = -1;
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