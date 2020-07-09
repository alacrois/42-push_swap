/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/09 19:00:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_order(t_stack s)
{
	int		i;
	int		tmp;

	i = -1;
	while (++i <= s.size / 2)
	{
		tmp = s.data[s.size - i];
		s.data[s.size - i] = s.data[i]
		s.data[i] = tmp;
	}
}

void		quicksort(t_so *so)
{
	t_stack	more_than_med;
	t_stack	less_than_med;
	int		median;
	int		median_order_index;
	int		size;

	more_than_med = new_stack(so->a_stack->max_size);
	less_than_med = new_stack(so->a_stack->max_size);
	median_order_index = (int)((float)so->a_stack->max_size * 0.5);
	median = so->ordered_numbers[median_order_index];
	size = so->a_stack / 2;
}