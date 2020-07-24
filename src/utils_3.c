/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 13:46:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			rotate_elem_on_top(t_so *so, t_bool a_stack, int elem)
{
	t_stack		*s;
	int			len;
	int			index;
	t_operation	rotate_op;

	s = a_stack == true ? so->a_stack : so->b_stack;
	len = s->size;
	index = get_element_index(s, elem);
	if (a_stack == true)
		rotate_op = index - 1 <= len / 2 ? RA : RRA;
	else
		rotate_op = index - 1 <= len / 2 ? RB : RRB;
	while (number_at_index(*s, 1) != elem)
		execute_and_save_operation(so->a_stack, so->b_stack, \
									so->operations, rotate_op);
}

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

void			free_sequences(t_sequence *so, t_sequence *sr)
{
	int			i;

	i = -1;
	while (++i < 4)
	{
		free(so[i].o);
		free(sr[i].o);
	}
}

void			delete_next_n_elem(t_list *start, int n)
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
			free(elem->content);
		}
		free(elem);
		elem = nextnext;
		start->next = elem;
		i++;
	}
}
