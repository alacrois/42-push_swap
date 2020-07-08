/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_sort_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/08 03:21:04 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		remove_last_rotations(t_list **operations, t_list *elem, \
									t_operation o, t_operation last_rotation)
{
	t_list		*tmp;

	if (o != last_rotation)
	{
		tmp = elem;
		elem = elem->next;
		tmp->next = NULL;
		free_list(&elem);
	}
	else
	{
		free_list(operations);
		*operations = NULL;
	}
}

static int		olr_init(t_list **operations, t_list **elem, \
							t_operation *o, t_operation *last_rotation)
{
	int			len;

	if (operations == NULL || *operations == NULL)
		return (0);
	len = ft_lstlen(*operations);
	*elem = ft_lstelem(*operations, len);
	*o = *((t_operation *)(*elem)->content);
	*last_rotation = *o;
	if (*o != RA && *o != RRA)
		return (0);
	return (1);
}

static int		count_last_rotations(t_list **operations, \
					t_operation last_rotation, t_operation *o, t_list **elem)
{
	int			count;
	int			index;
	int			len;

	len = ft_lstlen(*operations);
	index = len;
	count = 0;
	while (*o == last_rotation && index > 0)
	{
		*elem = ft_lstelem(*operations, index);
		*o = *((t_operation *)(*elem)->content);
		if (*o == last_rotation)
			count++;
		index--;
	}
	return (count);
}

void			optimise_last_rotations(t_list **operations, int stack_size)
{
	t_list		*elem;
	t_operation	o;
	t_operation	last_rotation;
	int			count;

	if (olr_init(operations, &elem, &o, &last_rotation) == 0)
		return ;
	count = count_last_rotations(operations, last_rotation, &o, &elem);
	if (stack_size - count < count)
	{
		remove_last_rotations(operations, elem, o, last_rotation);
		o = last_rotation == RA ? RRA : RA;
		while (count < stack_size)
		{
			add_operation(operations, o);
			count++;
		}
	}
}

void			inverse_order(t_so *so)
{
	int			len;
	int			i;

	len = so->a_stack->max_size;
	i = len;
	while (--i >= 2)
	{
		execute_and_save_operation(so->a_stack, so->b_stack, \
									so->operations, PB);
		if (so->b_stack->size > 1)
			execute_and_save_operation(so->a_stack, so->b_stack, \
										so->operations, RB);
	}
	execute_and_save_operation(so->a_stack, so->b_stack, \
								so->operations, SA);
	while (so->b_stack->size > 0)
		execute_and_save_operation(so->a_stack, so->b_stack, \
									so->operations, PA);
}
