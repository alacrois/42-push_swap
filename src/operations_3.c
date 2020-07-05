/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/05 22:20:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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
			printf("Trimmed operation : %i\n", *((t_operation *)elem->content));
			free(elem->content);
		}
		free(elem);
		elem = nextnext;
	}
	start->next = elem;
}

static int		trim_next(t_list *start, int count, t_operation o, t_list *before_cut)
{
	int			deleted;
	t_list		*elem;
	t_list		*next_elem;


	elem = start;
	deleted = 0;
	while (elem != NULL && *((t_operation *)elem->content) == o && count > 0)
	{
		next_elem = elem->next;
		if (elem->content != NULL)
			free(elem->content);
		free(elem);
		count--;
		deleted++;
		elem = next_elem;
	}
	if (before_cut != NULL)
		before_cut->next = elem;
	return (deleted);
}

static void		trim_core(t_list *elem)
{
	t_list		*ne;
	t_list		*before_cut;
	t_operation o;
	int			count;
	int			deleted;

	o = *((t_operation *)elem->content);
	count = 1;
	ne = elem->next;
	while (ne != NULL && *((t_operation *)ne->content) == o)
	{
		count++;
		before_cut = ne;
		ne = ne->next;
	}
	if (o == RA)
		deleted = trim_next(ne, count, RRA, before_cut);
	else if (o == RRA)
		deleted = trim_next(ne, count, RA, before_cut);
	if (deleted > 0)
		delete_next_n_elem(elem, deleted);
}

void		trim_operations(t_list **operations)
{
	t_list	*elem;
	// t_list	*previous_elem;

	if (operations == NULL || *operations == NULL)
		return ;
	elem = *operations;
	// previous_elem = NULL;
	while (elem != NULL)
	{
		// if (previous_elem == NULL)
		// 	*operations = trim_core(elem);
		// else
		// 	previous_elem->next = trim_core(elem);
		trim_core(elem);
		// previous_elem = elem;
		elem = elem->next;
	}
}
