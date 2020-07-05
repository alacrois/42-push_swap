/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/05 23:20:32 by marvin           ###   ########.fr       */
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
			// printf("Trimmed operation : %i(1)\n", *((t_operation *)elem->content));
			free(elem->content);
		}
		free(elem);
		elem = nextnext;
		i++;
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
	// printf("D2\n");
	while (elem != NULL && *((t_operation *)elem->content) == o && count > 0)
	{
		next_elem = elem->next;
	// printf("D2.1\n");

		if (elem->content != NULL)
		{
			// printf("Trimmed operation : %i(2)\n", *((t_operation *)elem->content));
			free(elem->content);
		}
		free(elem);
		count--;
		deleted++;
		elem = next_elem;
	}
	// printf("D3\n");
	if (before_cut != NULL)
		before_cut->next = elem;
	// printf("D4\n");

	return (deleted);
}

static void		trim_core(t_list *elem, t_list *previous)
{
	t_list		*ne;
	t_list		*before_cut;
	t_operation o;
	int			count;
	int			deleted;

	o = *((t_operation *)elem->content);
	count = 1;
	before_cut = elem;
	ne = elem->next;
	// printf("D1\n");
	// if (ne == NULL)
		// printf("ne == NULL\n");
	while (ne != NULL && *((t_operation *)ne->content) == o)
	{
		// printf("D1.1\n");
		// printf("d1, o = %i\n", *((t_operation *)elem->content));
		count++;
		before_cut = ne;
		ne = ne->next;
	}
	deleted = 0;
	// printf("D2\n");
	if (o == RA)
		deleted = trim_next(ne, count, RRA, before_cut);
	else if (o == RRA)
		deleted = trim_next(ne, count, RA, before_cut);
	else if (o == PA)
		deleted = trim_next(ne, count, PB, before_cut);
	else if (o == PB)
		deleted = trim_next(ne, count, PA, before_cut);
	// printf("D3\n");
	if (deleted > 0)
		delete_next_n_elem(previous, deleted);
	// printf("D4\n");
}

void		trim_operations(t_list **operations)
{
	t_list	*elem;
	t_list	*previous_elem;

	if (operations == NULL || *operations == NULL)
		return ;
	elem = *operations;
	// printf("Operations before trim :\n");
	// display_operations(*operations);
	// printf("========================\n");
	previous_elem = NULL;
	while (elem != NULL)
	{
		// if (previous_elem == NULL)
		// 	*operations = trim_core(elem);
		// else
		// 	previous_elem->next = trim_core(elem);
		// printf("D0\n");
		if (previous_elem != NULL)
			trim_core(elem, previous_elem);
		previous_elem = elem;
		elem = elem->next;
	}
	// printf("Operations AFTER trim :\n");

}
