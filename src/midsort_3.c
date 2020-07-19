/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/19 22:32:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		recursive_sort_section(t_so *so, t_section section, int median)
{
	int		i;
	
	if (DEBUG_MIDSORT == true)
		printf("\e[1;33mIn 'recursive_sort_section' : section %i to %i, size = %i, median = %i\e[0m...\n", \
				section.first_elem, section.last_elem, section.size, median);
	i = -1;
	while (++i < section.size)
	{
		do_operation(so, PA);
	}
}