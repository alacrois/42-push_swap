/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/18 00:11:59 by marvin           ###   ########.fr       */
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

int				next_rotation_to_delete(t_list *start, t_operation rotation)
{
	int			same_rotation_count;
	int			mirror_rotation_count;
	t_list		*elem;
	t_operation	mirror_rotation;
	t_operation	o;
	int			to_delete;

	elem = start;
	same_rotation_count = 0;
	mirror_rotation = get_mirror_rotation(rotation);
	o = *((t_operation *)elem->content);
	while (elem != NULL && o == rotation)
	{
		same_rotation_count++;
		elem = elem->next;
		if (elem != NULL)
			o = *((t_operation *)elem->content);
	}
	mirror_rotation_count = 0;
	while (elem != NULL && o == mirror_rotation)
	{
		mirror_rotation_count++;
		elem = elem->next;
		if (elem != NULL)
			o = *((t_operation *)elem->content);
	}
	if (same_rotation_count == 0 || mirror_rotation_count == 0)
		to_delete = 0;
	else if (same_rotation_count > mirror_rotation_count)
		to_delete = 0;
	else
		to_delete = same_rotation_count;
	return (to_delete);
}

static void		delete_next_n_elem(t_list *start, int n)
{
	t_list		*elem;
	t_list		*nextnext;
	int			i;

	elem = start->next;
	i = 0;
	while (elem != NULL && i < n)
	{
		nextnext = elem->next;
		if (elem->content != NULL)
		{
			// printf("Trimmed operation : %i(1)\n", *((t_operation *)elem->content));
			free(elem->content);
		}
		free(elem);
		elem = nextnext;
		start->next = elem;
		i++;
	}
}

void			replace_next_rotations(t_list *start, t_operation o, int n)
{
	t_list		*elem;
	t_list		*previous;
	int			i;
	t_operation	new_rotation;

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