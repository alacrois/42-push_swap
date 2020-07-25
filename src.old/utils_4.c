/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/25 10:39:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_operation	get_opposite_operation(t_operation o)
{
	if (o == RA)
		return (RRA);
	else if (o == RRA)
		return (RA);
	else if (o == RB)
		return (RRB);
	else if (o == RRB)
		return (RB);
	else if (o == PA)
		return (PB);
	else if (o == PB)
		return (PA);
	else if (o == RR)
		return (RRR);
	else if (o == RRR)
		return (RR);				
	return (-1);
}

int				next_operations_to_delete(t_list *start, t_operation rotation)
{
	int			same_rotation_count;
	int			mirror_rotation_count;
	t_list		*elem;
	t_operation	mirror_rotation;
	t_operation	o;
	int			to_delete;

	elem = start;
	same_rotation_count = 0;
	mirror_rotation = get_opposite_operation(rotation);
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
			// printf("Trimmed operation : %i(1)\n", *((t_operation *)elem->content));
			free(elem->content);
		}
		free(elem);
		elem = nextnext;
		start->next = elem;
		i++;
	}
}

// void			delete_next_operations(t_list *start, t_operation o, int n)
// {
// 	t_list		*elem;
// 	t_list		*previous;
// 	int			i;
// 	t_operation	new_rotation;

// 	new_rotation = (o == RA || o == RB) ? RR : RRR;
// 	elem = start;
// 	i = -1;
// 	while (++i < n)
// 	{
// 		*((t_operation *)elem->content) = new_rotation;
// 		previous = elem;
// 		elem = elem->next;
// 	}
// 	delete_next_n_elem(previous, n);
// }


void	optimize_operations(t_list **operations)
{
	t_list		*elem;
	t_list		*previous;
	// t_list		*pp;
	int			to_delete;
	t_operation	o;
	int			index;

	if (operations == NULL || *operations == NULL)
		return ;
	// if (DEBUG_OPTIMIZE == true)
	// 	printf("optimize_operations START\n");
	previous = NULL;
	// pp = NULL;
	index = 1;
	elem = *operations;
	while (elem != NULL && elem->next != NULL)
	{
		// if (DEBUG_OPTIMIZE == true)
		// 	printf("D1\n");
		o = *((t_operation *)elem->content);
		to_delete = next_operations_to_delete(elem, o);
		// if (DEBUG_OPTIMIZE == true)
		// 	printf("D2\n");
		if (previous != NULL && to_delete > 0)
		{
			// if (DEBUG_OPTIMIZE == true)
			// 	printf("D3\n");			
			delete_next_n_elem(previous, to_delete * 2);
			elem = previous->next;
			// previous = ft_lstelem(*operations, index - 1);
		}
		else
		{
			// if (DEBUG_OPTIMIZE == true)
			// 	printf("D4\n");				
			previous = elem;
			elem = elem->next;
			index++;
		}
		// if (DEBUG_OPTIMIZE == true)
		// 	printf("D5\n");			
	}
	// if (DEBUG_OPTIMIZE == true)
	// 	printf("optimize_operations END\n");
	optimize_operations_sequences(operations);
}