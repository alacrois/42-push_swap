/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 13:58:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		execute_one_operation(t_so *so, t_operation o)
{
	stack_swap(so->a_stack, so->b_stack, o);
	stack_push(so->a_stack, so->b_stack, o);
	stack_rotate(so->a_stack, so->b_stack, o);
	stack_reverse_rotate(so->a_stack, so->b_stack, o);
}

static void		invert_all(t_so *so)
{
	t_list		*elem;
	t_operation	o;

	elem = *(so->operations);
	while (elem != NULL)
	{
		o = *((t_operation *)elem->content);
		if (o == PA)
			*((t_operation *)elem->content) = PB;
		else if (o == PB)
			*((t_operation *)elem->content) = PA;
		else if (o == RR)
			*((t_operation *)elem->content) = RRR;
		else if (o == RRR)
			*((t_operation *)elem->content) = RR;
		else if (o == RA)
			*((t_operation *)elem->content) = RRA;
		else if (o == RRA)
			*((t_operation *)elem->content) = RA;
		else if (o == RB)
			*((t_operation *)elem->content) = RRB;
		else if (o == RRB)
			*((t_operation *)elem->content) = RB;
		elem = elem->next;
	}
}

void			undo_all_operations(t_so *so)
{
	t_list		*elem;
	t_operation	o;
	int			len;
	int			i;

	invert_all(so);
	len = ft_lstlen(*so->operations);
	i = len;
	while (i > 0)
	{
		elem = ft_lstelem(*(so->operations), i);
		o = *((t_operation *)elem->content);
		execute_one_operation(so, o);
		i--;
	}
	free_list(so->operations);
	*(so->operations) = NULL;
}
