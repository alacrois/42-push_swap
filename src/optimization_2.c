/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/25 08:34:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_operation	get_mirror_rotation(t_operation o)
{
	if (o == RA)
		return (RB);
	else if (o == RRA)
		return (RRB);
	else if (o == RB)
		return (RA);
	else if (o == RRB)
		return (RRA);
	return (-1);
}

static int			iterate_through_list(t_list **elem, t_operation to_compare)
{
	t_operation		o;
	int				count;

	if (elem == NULL || *elem == NULL)
		return (0);
	count = 0;
	o = *((t_operation *)(*elem)->content);
	while (*elem != NULL && o == to_compare)
	{
		count++;
		*elem = (*elem)->next;
		if (*elem != NULL)
			o = *((t_operation *)(*elem)->content);
	}
	return (count);
}

static int			next_rotation_to_delete(t_list *start, t_operation rotation)
{
	int				same_rotation_count;
	int				mirror_rotation_count;
	t_list			*elem;
	t_operation		mirror_rotation;
	int				to_delete;

	elem = start;
	mirror_rotation = get_mirror_rotation(rotation);
	same_rotation_count = iterate_through_list(&elem, rotation);
	mirror_rotation_count = iterate_through_list(&elem, mirror_rotation);
	if (same_rotation_count == 0 || mirror_rotation_count == 0)
		to_delete = 0;
	else if (same_rotation_count > mirror_rotation_count)
		to_delete = 0;
	else
		to_delete = same_rotation_count;
	return (to_delete);
}

static void			replace_next_rotations(t_list *start, t_operation o, int n)
{
	t_list			*elem;
	t_list			*previous;
	int				i;
	t_operation		new_rotation;

	new_rotation = (o == RA || o == RB) ? RR : RRR;
	elem = start;
	i = -1;
	while (++i < n)
	{
		*((t_operation *)elem->content) = new_rotation;
		previous = elem;
		elem = elem->next;
	}
	delete_next_n_elem(previous, n);
}

void				optimize_rotations(t_list **operations)
{
	t_list			*elem;
	int				to_delete;
	t_operation		o;

	if (operations == NULL || *operations == NULL)
		return ;
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
