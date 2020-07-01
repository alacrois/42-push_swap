/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/01 22:56:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void		execute_and_save_operation(t_list **a_stack, t_list **b_stack, \
										t_list **operations, t_operation o)
{
	t_list	*new_operation;

	add_operation(&new_operation, o);
	execute_operations(a_stack, b_stack, new_operation);
	free_list(&new_operation);
	add_operation(operations, o);
}

void		put_indexed_element_on_top(t_list **a_stack, int index, \
										t_list **operations)
{
	while (index > 1)
	{
		execute_and_save_operation(a_stack, NULL, operations, RA);
		index--;
	}
}


void		swap_elements(t_list **a_stack, int index, t_list **operations)
{
	put_indexed_element_on_top(a_stack, index, operations);
	execute_and_save_operation(a_stack, NULL, operations, SA);
}

void		all_b_to_a(t_list **a_stack, t_list **b_stack, \
										t_list **operations)
{
	while (*b_stack != NULL)
	{
		execute_and_save_operation(a_stack, b_stack, operations, PA);
	}
}

t_list		*generate_operations(t_list **a_stack)
{
	t_list	*operations;
	t_list	*b_stack;
	int		n1;
	int		n2;

	// operations = a_stack == NULL ? NULL : NULL;
	// add_operation(&operations, SA);
	// add_operation(&operations, PB);
	// add_operation(&operations, SB);
	// add_operation(&operations, RR);
	// add_operation(&operations, PA);
	// add_operation(&operations, RRR);
	b_stack = NULL;
	while (is_ordered(*a_stack) == false)
	{
		n1 = *(int *)(*a_stack)->content;
		n2 = *(int *)(*a_stack)->next->content;
		if (n1 > n2)
			execute_and_save_operation(a_stack, &b_stack, &operations, SA);
		execute_and_save_operation(a_stack, &b_stack, &operations, PB);
	}
	all_b_to_a(a_stack, &b_stack, &operations);
	return (operations);
}

void		display_operation(t_operation o)
{
	if (o == SA)
		ft_putendl("sa");
	else if (o == SB)
		ft_putendl("sb");
	else if (o == SS)
		ft_putendl("ss");
	else if (o == PA)
		ft_putendl("pa");
	else if (o == PB)
		ft_putendl("pb");
	else if (o == RA)
		ft_putendl("ra");
	else if (o == RB)
		ft_putendl("rb");
	else if (o == RR)
		ft_putendl("rr");
	else if (o == RRA)
		ft_putendl("rra");
	else if (o == RRB)
		ft_putendl("rrb");
	else if (o == RRR)
		ft_putendl("rrr");
}

void		display_operations(t_list *operations)
{
	t_list		*elem;
	t_operation	o;

	elem = operations;
	while (elem != NULL)
	{
		o = *(t_operation *)elem->content;
		display_operation(o);
		elem = elem->next;
	}
}