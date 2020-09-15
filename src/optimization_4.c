/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 11:36:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void			init_original_sequences(t_sequence *s)
{
	s[0] = new_sequence(3, PA, PB, RRA);
	s[1] = new_sequence(3, RB, PA, RRB);
	s[2] = new_sequence(3, RA, PA, RRA);
	s[3] = new_sequence(3, RB, PB, RRB);
}

static void			init_new_sequences(t_sequence *s)
{
	s[0] = new_sequence(2, SA, PB, 0);
	s[1] = new_sequence(2, SB, PA, 0);
	s[2] = new_sequence(2, PA, SA, 0);
	s[3] = new_sequence(2, PB, SB, 0);
}

static int			identify_sequence(t_list *start, t_sequence *so)
{
	int				i;
	int				si;
	t_bool			id;
	t_operation		o;
	t_list			*elem;

	i = -1;
	while (++i < 4)
	{
		si = -1;
		id = true;
		while (++si < so[i].size)
		{
			elem = ft_lstelem(start, 1 + si);
			o = elem != NULL ? *((t_operation *)elem->content) : o;
			if (elem == NULL || so[i].o[si] != o)
			{
				id = false;
				break ;
			}
		}
		if (id == true)
			return (i);
	}
	return (-1);
}

static void			replace_with_new_sequence(t_list *start, t_sequence *old, \
											t_sequence *new, int id)
{
	t_list			*elem;
	int				i;
	int				to_delete;

	i = -1;
	while (++i < new[id].size)
	{
		elem = ft_lstelem(start, 1 + i);
		*((t_operation *)elem->content) = new[id].o[i];
	}
	to_delete = old[id].size - new[id].size;
	elem = ft_lstelem(start, new[id].size);
	delete_next_n_elem(elem, to_delete);
}

void				optimize_operations_sequences(t_list **operations)
{
	t_list			*elem;
	int				index;
	t_sequence		seq_original[4];
	t_sequence		seq_replacement[4];
	int				seq_id;

	if (operations == NULL || *operations == NULL)
		return ;
	init_original_sequences(seq_original);
	init_new_sequences(seq_replacement);
	index = 1;
	elem = *operations;
	while (elem != NULL && elem->next != NULL)
	{
		seq_id = identify_sequence(elem, seq_original);
		if (seq_id != -1)
		{
			replace_with_new_sequence(elem, seq_original, \
										seq_replacement, seq_id);
		}
		elem = elem->next;
		index++;
	}
	free_sequences(seq_original, seq_replacement);
}
