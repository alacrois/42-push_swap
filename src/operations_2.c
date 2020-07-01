/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/01 23:14:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void		execute_and_save_operation(t_list **a_stack, t_list **b_stack, \
										t_list **operations, t_operation o)
{
	t_list	*new_operation;

	new_operation = NULL;
	// printf("D1.4.1\n");
	add_operation(&new_operation, o);
	// printf("D1.4.2\n");
	execute_operations(a_stack, b_stack, new_operation);
	// printf("D1.4.3\n");
	free_list(&new_operation);
	// printf("D1.4.4\n");
	add_operation(operations, o);
	// printf("D1.4.5\n");

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

	operations = a_stack == NULL ? NULL : NULL;
	// add_operation(&operations, SA);
	// add_operation(&operations, PB);
	// add_operation(&operations, SB);
	// add_operation(&operations, RR);
	// add_operation(&operations, PA);
	// add_operation(&operations, RRR);


	b_stack = NULL;
	// printf("D1\n");
	while (is_ordered(*a_stack) == false)
	{
		// printf("D1.1\n");
		n1 = *((int *)(*a_stack)->content);
		// printf("D1.2\n");

		n2 = *((int *)(*a_stack)->next->content);
		// printf("D1.3\n");
		if (n1 > n2)
		{
			// printf("D1.4\n");
			execute_and_save_operation(a_stack, &b_stack, &operations, SA);
			// printf("D1.5\n");
		}
		// printf("D1.6\n");
		execute_and_save_operation(a_stack, &b_stack, &operations, PB);
	}
	// printf("D2\n");
	all_b_to_a(a_stack, &b_stack, &operations);
	// printf("D3\n");
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

	// printf("D4\n");
	elem = operations;
	while (elem != NULL)
	{
		// printf("D4.1\n");
		o = *(t_operation *)elem->content;
		// printf("D4.2\n");
		display_operation(o);
		// printf("D4.3\n");
		elem = elem->next;
	}
	// printf("D5\n");
}