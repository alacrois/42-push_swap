/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   midsort_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/18 20:25:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool		section_is_sorted(t_so *so, int size, t_bool from_a)
{
	int		i;
	int		a;
	int		b;
	t_stack	*s;

	s = from_a == true ? so->a_stack : so->b_stack;
	i = -1;
	while (++i < size - 1)
	{
		a = nb_at_index_mod(s, i + 1);
		b = nb_at_index_mod(s, i + 2);
		if ((from_a == true && a > b) || (from_a == false && a < b))
			return (false);
	}
	return (true);
}

static void	sort_array(int *array, int size)
{
	int		i;
	int		tmp;
	t_bool	switched;

	switched = true;
	while (switched == true)
	{
		switched = false;
		i = -1;
		while (++i < size - 1)
		{
			if (array[i] > array[i + 1])
			{
				tmp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = tmp;
				switched = true;
			}
		}
	}
}

int			set_median(t_stack *s, int size)
{
	int		i;
	int		array[size];

	i = -1;
	while (++i < size)
		array[i] = nb_at_index_mod(s, 1 + i);
	sort_array(array, size);
	// if (DEBUG_MIDSORT == true)
	// {
	// 	i = -1;
	// 	printf("Array sorted is :\n");
	// 	while (++i < size)
	// 		printf("%i\n", array[i]);
	// }
	return (array[size / 2]);
}
