/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_operations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/22 22:54:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_sequence		new_sequence(t_operation s[], int size)
{
	t_sequence	seq;
	int			i;

	seq.o = (t_operation *)ft_malloc(sizeof(t_operation) * size);
	seq.size = size;
	i = -1;
	while (++i < size)
		seq.o[i] = s[i];
	return (seq);
}

static void		init_original_sequences(t_sequence *s)
{
	t_operation		original_a[] = {RA, PB, RRA};
	t_operation		original_b[] = {RB, PA, RRB};
	t_operation		original_c[] = {RA, PA, RRA};
	t_operation		original_d[] = {RB, PB, RRB};

	// o = {RA, PB, RRA};
	s[0] = new_sequence(original_a, 3);
	s[1] = new_sequence(original_b, 3);
	s[2] = new_sequence(original_c, 3);
	s[3] = new_sequence(original_d, 3);
	
	// sr[0] = new_sequence({SA, PB}, 2);
	// sr[1] = new_sequence({SB, PA}, 2);
	// sr[2] = new_sequence({PA, SA}, 2);
	// sr[3] = new_sequence({PB, SB}, 2);
	// if (sr == NULL)
	// 	printf("Blablba\n");
}

static void		init_new_sequences(t_sequence *s)
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

static void		free_sequences(t_sequence *so, t_sequence *sr)
{
	int			i;

	i = -1;
	while (++i < 4)
	{
		free(so[i].o);
		free(sr[i].o);
	}
	if (sr == NULL)
		printf("Blablba\n");
}

int				identify_sequence(t_list *start, t_sequence *so)
{
	int			i;
	int			si;
	// int			li;
	t_bool		id;
	t_operation	o;
	t_list		*elem;

	// li = -1;
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

static void		replace_with_new_sequence(t_list *start, t_sequence *old, \
											t_sequence *new, int id)
{
	t_list		*elem;
	int			i;
	// t_operation	o;
	int			to_delete;


	i = -1;
	while (++i < new[id].size)
	{
		elem = ft_lstelem(start, 1 + i);
		// o = *((t_operation *)elem->content);
		*((t_operation *)elem->content) = new[id].o[i];
	}
	to_delete = old[id].size - new[id].size;
	elem = ft_lstelem(start, new[id].size);
	delete_next_n_elem(elem, to_delete);
}

void	optimize_operations_sequences(t_list **operations)
{
	t_list		*elem;
	// t_list		*previous;
	// t_list		*pp;
	// int			to_delete;
	// t_operation	o;
	int			index;
	t_sequence	seq_original[4];
	t_sequence	seq_replacement[4];
	int			seq_id;

	if (operations == NULL || *operations == NULL)
		return ;
	if (DEBUG_OPTIMIZE == true)
		printf("optimize_operations_sequences START\n");
	init_original_sequences(seq_original);
	init_new_sequences(seq_replacement);
	// previous = NULL;
	// pp = NULL;
	index = 1;
	elem = *operations;
	while (elem != NULL && elem->next != NULL)
	{
		if (DEBUG_OPTIMIZE == true)
		{
			// printf("D1\n");
			seq_id = identify_sequence(elem, seq_original);
			if (seq_id != -1)
			{
				printf("Sequence identified at index %i, id = %i\n", index, seq_id);
				replace_with_new_sequence(elem, seq_original, seq_replacement, seq_id);
			}
		}
			// previous = elem;
			elem = elem->next;
			index++;
		// }
		// if (DEBUG_OPTIMIZE == true)
		// 	printf("D5\n");			
	}
	free_sequences(seq_original, seq_replacement);

	if (DEBUG_OPTIMIZE == true)
		printf("optimize_operations_sequences END\n");
}