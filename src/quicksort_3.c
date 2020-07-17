/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quicksort_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/18 00:41:22 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define DEBUG_NEW_SORT false

static void	init(t_so *so, int size, int *elements, t_to_sort *elems)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		elements[i] = nb_at_index_mod(so->a_stack, 1 + i);
		elems[i].value = elements[i];
		elems[i].ooo = 0;
		elems[i].used = true;

		if (DEBUG_NEW_SORT == true)
			printf("elems[%i] = %i\n", i, elements[i]);
	}
}

void		print_array(int *selected, int size)
{
	int		i;

	i = -1;
	if (DEBUG_NEW_SORT == true)
	{
		printf("Selected to remove :\n");
		i = -1;
		while (++i < size)
			printf("selected[%i] = %i\n", i, selected[i]);
	}
}

static void	set_unsorted(t_to_sort *elements, int size)
{
	int		i1;
	int		i2;

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
					if ((i2 < i1 && elements[i2].value > elements[i1].value) || \
						(i2 > i1 && elements[i2].value < elements[i1].value))
						elements[i1].ooo++;
				}
				
			}
		}
	}
	if (DEBUG_NEW_SORT == true)
	{
		printf("In set_unsorted :\n\n");
		i1 = -1;
		while (++i1 < size)
		{
			printf("elements[%i] : v = %i, used = %i, ooo = %i\n", \
				i1, elements[i1].value, elements[i1].used == true ? 1 : 0, elements[i1].ooo);
		}
	}
}

static int	remove_first_most_unsorted(t_to_sort *elements, int size)
{
	int		ooo_max;
	int		selected_index;
	int		i;

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

void		select_elements_to_remove(t_so *so, int size, int *selected)
{
	int			i;
	int			elements[size];
	t_to_sort	elems[size];

	init(so, size, elements, elems);
	i = -1;
	set_unsorted(elems, size);
	while (remove_first_most_unsorted(elems, size) == 1)
		set_unsorted(elems, size);
	while (++i < size)
	{
		// if (elements[i] == 0)
		// 	selected[i] = 1;
		// else
		// 	selected[i] = 0;
		selected[i] = elems[i].used == true ? 0 : 1;

	}
	print_array(selected, size);
}

int		count_unsorted(int *elements, int size)
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

	set_unsorted(elems, size);
	while (remove_first_most_unsorted(elems, size) == 1)
		set_unsorted(elems, size);
	count = 0;
	i = -1;
	while (++i < size)
	{
		count += elems[i].used == true ? 0 : 1;
	}
	return (count);
}