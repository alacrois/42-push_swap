/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/21 06:14:04 by marvin           ###   ########.fr       */
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
		// if (DEBUG_SIMPLE_SORT == true)
		// 	printf("init simple sort - elem at index %i is %i\n", i, elems[i].value);
	}
}

void		print_simple_sort_array(t_to_sort *elems, int size)
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

// static void	set_inverse_unsorted(t_to_sort *elements, int size)
// {
// 	int		i1;
// 	int		i2;

// 	i1 = -1;
// 	while (++i1 < size)
// 	{
// 		if (elements[i1].used == true)
// 		{
// 			elements[i1].ooo = 0;
// 			i2 = -1;
// 			while (++i2 < size)
// 			{
// 				if (i1 != i2 && elements[i2].used == true)
// 				{
// 					if ((i2 < i1 && elements[i2].value < elements[i1].value) ||
// 						(i2 > i1 && elements[i2].value > elements[i1].value))
// 						elements[i1].ooo++;
// 				}
// 			}
// 		}
// 	}
// }

static	t_bool	not_in_order(t_to_sort *elements, int index1, int index2, \
								t_bool in_order)
{
	if (in_order == true)
	{

	if ((index2 < index1 && elements[index2].value > elements[index1].value) || \
		(index2 > index1 && elements[index2].value < elements[index1].value))
		return (true);
	}
	else
	{
		if ((index2 < index1 && elements[index2].value < elements[index1].value) || \
			(index2 > index1 && elements[index2].value > elements[index1].value))
		return (true);
	}
	return (false);
}

static void	set_unsorted(t_to_sort *elements, int size, t_bool in_order)
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
					// if ((i2 < i1 && elements[i2].value > elements[i1].value) ||
					// 	(i2 > i1 && elements[i2].value < elements[i1].value))
					if (not_in_order(elements, i1, i2, in_order) == true)
						elements[i1].ooo++;
				}
			}
		}
	}
	/*
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
	*/
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

// void			insert_back(t_so *so, t_bool a, int unsorted_count, int rotations_count)
void			insert_back(t_so *so, t_bool a, int unsorted_count, int *rotations_count)
{
	t_operation	rotation;
	t_operation	push;
	int			x;
	int			y;

	// rotation = a == true ? RRA : RRB;
	// push = a == true ? PA : PB;
	rotation = a == true ? RRA : RRA;
	push = PA;
	// if (a == false)
	// 	*rotations_count = unsorted_count;
	if (DEBUG_SIMPLE_SORT == true)
		printf("Starting insert_back with rotation_count = %i, unsorted_count = %i\n", \
				*rotations_count, unsorted_count);
	while (unsorted_count > 0 && *rotations_count > 0)
	{
		// x = nb_at_index_mod(a == true ? so->a_stack : so->b_stack, 0);
		// y = nb_at_index_mod(a == true ? so->b_stack : so->a_stack, 1);
		// x = nb_at_index_mod(so->a_stack, a == true ? 0 : 1);
		x = nb_at_index_mod(so->a_stack, a == true ? 0 : 0);
		y = nb_at_index_mod(so->b_stack, 1);
		// if ((a == true && y > x) || (a == false && y < x))
		if (DEBUG_SIMPLE_SORT == true)
			printf("In loop, x = %i, y = %i (rc = %i, uc = %i)\n", x, y, \
						*rotations_count, unsorted_count);
		if ((a == true && y > x) || (a == false && y > x))
		{
			do_operation(so, push);
			unsorted_count--;
			// *rotations_count = unsorted_count;
			if (DEBUG_SIMPLE_SORT == true)
				printf("Pushed to A, uc is now %i\n", unsorted_count);
		}
		else
		{
			do_operation(so, rotation);
			// if (a == true)
			*rotations_count = *rotations_count - 1;
			// else
			// 	*rotations_count = *rotations_count + 1;
			if (DEBUG_SIMPLE_SORT == true)
				printf("Rotated A, rc is now %i\n", *rotations_count);
		}
	}
	while (unsorted_count > 0)
	{
		do_operation(so, push);
		unsorted_count--;
	}
}

/*
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
*/

static int	max_less_than_in_b(t_so *so, int a, t_section *section)
{
	int		i;
	int		tmp;
	int		start_index;
	int		elem;

	i = -1;
	tmp = a;
	start_index = get_element_index(so->b_stack, section->first_elem);
	// rotate_elem_on_top(so, false, section->first_elem);
	if (DEBUG_SIMPLE_SORT == true)
	{
		printf("In max_less_than_in_b, trying to find for %i...\n", a);
		printf("Section : first = %i last = %i  size = %i, start_index = %i\n", \
				section->first_elem, section->last_elem, section->size, start_index);
	}
	while (++i < section->size)
	{
		elem = nb_at_index_mod(so->b_stack, start_index + i);
		if (DEBUG_SIMPLE_SORT == true)
			printf("In loop, comparing %i to %i... (tmp is %i)\n", elem, a, tmp);
		if ((tmp == a || elem > tmp) && elem < a)
			tmp = elem;
	}
	if (DEBUG_SIMPLE_SORT == true)
		printf("After loop, tmp =  %i\n", tmp);
	// tmp = tmp == a ? section_max(so, false, section) : tmp;
	if (tmp == a)
	{
		// Found no elements less then a, must put a the end(bottom) of section
		tmp = nb_at_index_mod(so->b_stack, start_index + section->size);
		if (DEBUG_SIMPLE_SORT == true)
			printf("Found no elements less then a, tmp =  %i\n", tmp);
	}
	return (tmp);
}

static int	min_more_than_in_a(t_so *so, int a, t_section *section)
{
	// ft_exit("Noooooooooooooo !!");
	int		i;
	int		tmp;
	int		start_index;
	int		elem;

	i = -1;
	tmp = a;
	start_index = get_element_index(so->a_stack, section->first_elem);
	// rotate_elem_on_top(so, false, section->first_elem);
	if (DEBUG_SIMPLE_SORT == true)
	{
		printf("In min_more_than_in_a, trying to find for %i...\n", a);
		printf("Section : first = %i last = %i  size = %i, start_index = %i\n", \
				section->first_elem, section->last_elem, section->size, start_index);
	}
	while (++i < section->size)
	{
		elem = nb_at_index_mod(so->a_stack, start_index + i);
		if (DEBUG_SIMPLE_SORT == true)
			printf("In loop, comparing %i to %i... (tmp is %i)\n", elem, a, tmp);
		if ((tmp == a || elem < tmp) && elem > a)
			tmp = elem;
	}
	if (DEBUG_SIMPLE_SORT == true)
		printf("After loop, tmp =  %i\n", tmp);
	// tmp = tmp == a ? section_max(so, false, section) : tmp;
	if (tmp == a)
	{
		// Found no elements less then a, must put a the end(bottom) of section
		tmp = nb_at_index_mod(so->a_stack, start_index + section->size);
		if (DEBUG_SIMPLE_SORT == true)
			printf("Found no elements more then a, tmp =  %i\n", tmp);
	}
	return (tmp);
}

void			put_in_ordered_stack(t_so *so, t_bool b, t_section *section)
{
	t_stack		*s;
	t_operation	push;
	int			new_elem;
	int			tmp;


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
		tmp = max_less_than_in_b(so, new_elem, section);
	else
		tmp = min_more_than_in_a(so, new_elem, section);

	if (DEBUG_SIMPLE_SORT == true)
		printf("In put_in_ordered_stack, rotating %i on top...\n", tmp);
	if (b == true)
		rotate_elem_on_top(so, false, tmp);
	else
		rotate_elem_on_top(so, true, tmp);
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

void			simple_sort(t_so *so, t_section *section, t_bool a)
{
	t_to_sort	elems[section->size];
	int			unsorted_count;
	int			i;
	// int			nb;
	t_stack		*s;
	int			rotations;
	t_section	unsorted;

	// if (a == false)
	// 	ft_exit("No simple sort available for B stack yet !\nQuitting program...\n");
	s = a == true ? so->a_stack : so->b_stack;
	init(elems, s, section->size);
	set_unsorted(elems, section->size, a);
	while (remove_first_most_unsorted(elems, section->size) == 1)
		set_unsorted(elems, section->size, a);
	print_simple_sort_array(elems, section->size);
	i = -1;
	unsorted_count = 0;
	rotations = 0;
	unsorted.size = 0;
	while (++i < section->size)
	{
		if (elems[i].used == false)
		// if ((a == true && elems[i].used == false) ||
		// 	(a == false && elems[i].used == true))
		{
			if (DEBUG_SIMPLE_SORT == true)
			{
				printf("\e[1;36mBefore put_in_ordered_stack, elem is %i\e[0m\n", \
							elems[i].value);
				display_infos(*so->a_stack, *so->b_stack, *so->operations);
			}
			put_in_ordered_stack(so, a, &unsorted);
			if (DEBUG_SIMPLE_SORT == true)
			{
				printf("\e[1;36mAfter put_in_ordered_stack, elem is %i\e[0m\n", \
							elems[i].value);
				display_infos(*so->a_stack, *so->b_stack, *so->operations);
			}
			unsorted_count++;
		}
		else
		{
			do_operation(so, a == true ? RA : RB);
			if (a == true)
				rotations++;
		}
	}
	if (a == true)
		rotate_elem_on_top(so, false, unsorted.first_elem);
	else
	{
		// do_operation(so, RRB);
		if (DEBUG_SIMPLE_SORT == true)
			printf("Setting up stacks for insert_back...\n");
		rotate_elem_on_top(so, false, get_max(elems, section->size, true));
		rotate_elem_on_top(so, true, get_max(elems, section->size, false));
		do_operation(so, RA);
		rotations = unsorted_count;
	}
	if (DEBUG_SIMPLE_SORT == true)
	{
		printf("\e[1;36mBefore insert_back (section %i to %i, size = %i, unsorted_count = %i, rotations = %i) :\e[0m\n", \
				section->first_elem, section->last_elem, section->size, unsorted_count, rotations);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
	}
	// insert_back(so, a, unsorted_count, section->size - unsorted_count);

	if (a == true)
		insert_back(so, a, unsorted_count, &rotations);
	else
		insert_back(so, a, section->size - unsorted_count, &rotations);
		
	if (DEBUG_SIMPLE_SORT == true)
	{
		printf("\e[1;36mAfter insert_back (section %i to %i, size = %i, unsorted_count = %i) :\e[0m\n", \
				section->first_elem, section->last_elem, section->size, unsorted_count);
		display_infos(*so->a_stack, *so->b_stack, *so->operations);
		// if (a == true)
		printf("\e[1;36mRotating back %i times :\e[0m\n", rotations);
	}
	while (a == true && rotations > 0)
	{
		do_operation(so, RRA);
		rotations--;
	}
	if (a == false)
		rotate_elem_on_top(so, true, get_min(elems, section->size));
	// while (a == false && rotations > 0)
	// {
	// 	do_operation(so, a == true ? RRA : RRB);
	// 	rotations--;
	// }
}