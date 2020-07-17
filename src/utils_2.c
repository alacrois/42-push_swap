/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/18 01:36:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	free_list(t_list **list)
{
	t_list	*elem;
	t_list	*next_elem;

	elem = list != NULL ? *list : NULL;
	while (elem != NULL)
	{
		next_elem = elem->next;
		if (elem->content != NULL)
			free(elem->content);
		free(elem);
		elem = next_elem;
	}
	if (list != NULL)
		*list = NULL;
}

int		get_index_distance(int a, int b, int size)
{
	int	d1;
	int	d2;

	if (a <= b)
	{
		d1 = b - a;
		d2 = a + (size - b);
	}
	else
	{
		d1 = a - b;
		d2 = b + (size - a);
	}
	return (d1 < d2 ? d1 : d2);
}

void	free_stack(t_stack s)
{
	if (s.data != NULL)
		free(s.data);
}

void	optimize_rotations(t_list **operations)
{
	t_list		*elem;
	// t_list		*previous;
	int			to_delete;
	t_operation	o;

	if (operations == NULL || *operations == NULL)
		return ;
	// previous = NULL;
	elem = *operations;
	while (elem->next != NULL)
	{
		o = *((t_operation *)elem->content);
		if (o == RA || o == RB || o == RRA || o == RRB)
		{
			to_delete = next_rotation_to_delete(elem, o);
			if (to_delete > 0)
				replace_next_rotations(elem, o, to_delete);
		}
		elem = elem->next;
	}
}

void		check_swap(t_so *so)
{
	t_bool	sa;
	t_bool	sb;

	sa = false;
	sb = false;
	if (so->a_stack->size > 1 && nb_at_index_mod(so->a_stack, 1) > nb_at_index_mod(so->a_stack, 2))
		sa = true;
	if (so->b_stack->size > 1 && nb_at_index_mod(so->b_stack, 1) < nb_at_index_mod(so->b_stack, 2))
		sb = true;
	if (sa == true && sb == true)
		do_operation(so, SS);
	else if (sa == true)
		do_operation(so, SA);
	else if (sb == true)
		do_operation(so, SB);
}