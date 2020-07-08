/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_sort_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/08 03:11:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool			check_order(t_so *so)
{
	int			len;
	int			i;
	int			a;
	int			b;

	len = so->a_stack->max_size;
	i = 0;
	while (++i <= len)
	{
		a = number_at_index(*so->a_stack, i);
		b = number_at_index(*so->a_stack, i < len ? i + 1 : 1);
		if ((b != so->ordered_numbers[0] || a != so->ordered_numbers[len - 1]) \
			&& a > b)
			return (false);
	}
	return (true);
}
