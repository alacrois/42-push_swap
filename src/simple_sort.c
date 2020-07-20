/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/21 00:59:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"


static void	init(t_to_sort *elems, t_stack *s, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		elems[i].value = nb_at_index_mod(s, 1 + i);
		elems[i].ooo = 0;
		elems[i].used = true;
		if (DEBUG_SIMPLE_SORT == true)
			printf("init simple sort - elem at index %i is %i\n", i, elems[i].value);
	}
}

void		print_array(t_to_sort *elems, int size)
{
	int		i;

	i = -1;
	if (DEBUG_SIMPLE_SORT == true)
	{
		printf("Selected to remove :\n");
		i = -1;
		while (++i < size)
		{
			if (elems[i].used == false)
				printf("Removing %i at index %i\n", elems[i].value, i);
		}
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
	if (DEBUG_SIMPLE_SORT == true)
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


// ===================================================

void			insert_back(t_so *so, t_bool a, int unsorted_count, int rotations_count)
{
	t_operation	rotation;
	t_operation	push;
	int			x;
	int			y;

	rotation = a == true ? RA : RB;
	push = a == true ? PA : PB;
	while (unsorted_count > 0 && rotations_count > 0)
	{
		x = nb_at_index_mod(a == true ? so->a_stack : so->b_stack, 0);
		y = nb_at_index_mod(a == true ? so->b_stack : so->a_stack, 1);
		if ((a == true && y > x) || (a == false && y < x))
		{
			do_operation(so, push);
			unsorted_count--;	
		}
		else
		{
			do_operation(so, rotation);
			rotations_count--;
		}
	}
	if (unsorted_count > 0)
		do_operation(so, push);
}

static int	section_max(t_so *so, t_bool a, t_section *section)
{
	int		i;
	int		max;
	int		start_index;
	int		elem;
	t_stack	*s;

	i = -1;
	s = a == true ? so->a_stack : so->b_stack;
	start_index = get_element_index(s, section->first_elem);
	max = nb_at_index_mod(s, start_index);
	while (++i < section->size)
	{
		elem = nb_at_index_mod(s, start_index + i);
		max = elem > max ? elem : max;
	}
	return (max);
}

static int	max_less_than_in_b(t_so *so, int a, t_section *section)
{
	int		i;
	int		tmp;
	int		start_index;
	int		elem;

	i = -1;
	tmp = a;
	start_index = nb_at_index_mod(so->b_stack, \
		get_element_index(so->b_stack, section->first_elem));
	// rotate_elem_on_top(so, false, section->first_elem);
	while (++i < section->size)
	{
		elem = nb_at_index_mod(so->b_stack, start_index + i);
		if ((tmp == a || elem > tmp) && elem < a)
			tmp = elem;
	}
	tmp = tmp == a ? section_max(so, false, section) : tmp;
	return (tmp);
}

static int	min_more_than_in_a(t_so *so, int a, t_section *section)
{
	ft_exit("Noooooooooooooo !!");
}

void			put_in_ordered_stack(t_so *so, t_bool b, t_section *section)
{
	t_stack		*s;
	t_operation	push;
	int			new_elem;


	s = b == true ? so->b_stack : so->a_stack;
	push = b == true ? PB : PA;
	new_elem = nb_at_index_mod(b == false ? so->b_stack : so->a_stack, 1);
	if (section->size == 0)
	{
		do_operation(so, push);
		section->size = 1;
		section->first_elem = nb_at_index_mod(s, 1);
		section->last_elem = nb_at_index_mod(s, 1);
		return ;
	}
	if (b == true)
		rotate_elem_on_top(so, false, max_less_than_in_b(so, new_elem, section));
	else
		rotate_elem_on_top(so, true, min_more_than_in_a(so, new_elem, section));
	do_operation(so, push);
	if (b == true && new_elem > section->first_elem)
		section->first_elem = new_elem;
	else if (b == true && new_elem < section->last_elem)
		section->last_elem = new_elem;
	else if (b == false && new_elem < section->first_elem)
		section->first_elem = new_elem;
	else if (b == false && new_elem > section->last_elem)
		section->last_elem = new_elem;
	section->size++;
}

void			simple_sort(t_so *so, t_section *section, t_bool a)
{
	t_to_sort	elems[section->size];
	int			unsorted_count;
	int			i;
	int			nb;
	t_stack		*s;
	int			rotations;
	t_section	unsorted;

	if (a == false)
		ft_exit("No simple sort available for B stack yet !\nQuitting program...\n");
	s = a == true ? so->a_stack : so->b_stack;
	init(elems, s, section->size);
	set_unsorted(elems, section->size);
	while (remove_first_most_unsorted(elems, section->size) == 1)
		set_unsorted(elems, section->size);
	print_array(elems, section->size);
	i = -1;
	unsorted_count = 0;
	unsorted.size = 0;
	while (++i < section->size)
	{
		nb = nb_at_index_mod(s, 1 + i);
		if (elems[i].used == false)
		{
			// do_operation(so, a == true ? PB : PA);
			put_in_ordered_stack(so, a, &unsorted);
			unsorted_count++;
		}
		else
			do_operation(so, a == true ? RA : RB);
	}
	insert_back(so, a, unsorted_count, section->size - unsorted_count);
}