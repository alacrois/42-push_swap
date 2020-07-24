/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 14:47:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_bool	not_in_order(t_to_sort *e, int index1, int index2, \
								t_bool in_order)
{
	if (in_order == true)
	{
		if ((index2 < index1 && e[index2].value > e[index1].value) || \
		(index2 > index1 && e[index2].value < e[index1].value))
			return (true);
	}
	else
	{
		if ((index2 < index1 && e[index2].value < e[index1].value) || \
			(index2 > index1 && e[index2].value > e[index1].value))
			return (true);
	}
	return (false);
}

static void		set_unsorted(t_to_sort *elements, int size, t_bool in_order)
{
	int			i1;
	int			i2;

	i1 = -1;
	while (++i1 < size)
	{
		if (elements[i1].used == true)
		{
			elements[i1].ooo = 0;
			i2 = -1;
			while (++i2 < size)
			{
				if (i1 != i2 && elements[i2].used == true)
				{
					if (not_in_order(elements, i1, i2, in_order) == true)
						elements[i1].ooo++;
				}
			}
		}
	}
}

static int		remove_first_most_unsorted(t_to_sort *elements, int size)
{
	int			ooo_max;
	int			selected_index;
	int			i;

	ooo_max = 0;
	selected_index = 0;
	i = -1;
	while (++i < size)
	{
		if (elements[i].used == true && elements[i].ooo > ooo_max)
		{
			ooo_max = elements[i].ooo;
			selected_index = i;
		}
	}
	if (ooo_max > 0)
	{
		elements[selected_index].ooo = 0;
		elements[selected_index].used = false;
		return (1);
	}
	else
		return (0);
}

int				get_min(t_to_sort *elems, int size)
{
	int			i;
	int			min;

	i = -1;
	min = elems[0].value;
	while (++i < size)
	{
		min = elems[i].value < min ? elems[i].value : min;
	}
	return (min);
}

int				get_max(t_to_sort *elems, int size, t_bool used)
{
	int			i;
	int			max;
	t_bool		found;

	i = -1;
	found = false;
	while (++i < size)
	{
		if (elems[i].used == used && (found == false || elems[i].value > max))
		{
			max = elems[i].value;
			found = true;
		}
	}
	if (found == false)
		ft_exit("Couldnt find max unused !");
	return (max);
}
