/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/25 11:29:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		sort_array(int *array, int size)
{
	int			i;
	int			tmp;
	t_bool		switched;

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

int				set_median(t_stack *s, int size)
{
	int			i;
	int			array[size];

	i = -1;
	while (++i < size)
		array[i] = nb_at_index_mod(s, 1 + i);
	sort_array(array, size);
	return (array[size / 2]);
}

int				count_unsorted(int *elements, int size, t_bool in_order)
{
	int			i;
	t_to_sort	elems[size];
	int			count;

	i = -1;
	while (++i < size)
	{
		elems[i].value = elements[i];
		elems[i].ooo = 0;
		elems[i].used = true;
	}
	set_unsorted(elems, size, in_order);
	while (remove_first_most_unsorted(elems, size) == 1)
		set_unsorted(elems, size, in_order);
	count = 0;
	i = -1;
	while (++i < size)
	{
		count += elems[i].used == true ? 0 : 1;
	}
	return (count);
}
