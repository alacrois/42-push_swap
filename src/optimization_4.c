/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimization_4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 13:44:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void			init_original_sequences(t_sequence *s)
{
	t_operation		original_a[] = {RA, PB, RRA};
	t_operation		original_b[] = {RB, PA, RRB};
	t_operation		original_c[] = {RA, PA, RRA};
	t_operation		original_d[] = {RB, PB, RRB};

	s[0] = new_sequence(original_a, 3);
	s[1] = new_sequence(original_b, 3);
	s[2] = new_sequence(original_c, 3);
	s[3] = new_sequence(original_d, 3);
}

static void			init_new_sequences(t_sequence *s)
{
	t_operation		new_a[] = {SA, PB};
	t_operation		new_b[] = {SB, PA};
	t_operation		new_c[] = {PA, SA};
	t_operation		new_d[] = {PB, SB};

	s[0] = new_sequence(new_a, 2);
	s[1] = new_sequence(new_b, 2);
	s[2] = new_sequence(new_c, 2);
	s[3] = new_sequence(new_d, 2);
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
			o = *((t_operation *)elem->content);
			if (so[i].o[si] != o)
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
			replace_with_new_sequence(elem, seq_original, \
										seq_replacement, seq_id);
		elem = elem->next;
		index++;
	}
	free_sequences(seq_original, seq_replacement);
}
