/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/01 15:37:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	swap(t_list **a_stack, t_list **b_stack, t_operation o)
{
	int		*a;
	int		*b;
	t_list	*stack;
	int		tmp;

	stack = o == SA ? *a_stack : NULL;
	stack = o == SB ? *b_stack : stack;
	if (o == SS)
	{
		swap(a_stack, b_stack, SA);
		swap(a_stack, b_stack, SB);
	}
	if (stack != NULL)
	{
		if (ft_lstlen(stack) >= 2)
		{
			a = (int *)ft_lstelem(stack, 1)->content;
			b = (int *)ft_lstelem(stack, 2)->content;
			tmp = *a;
			*a = *b;
			*b = tmp;
		}
	}
}

void	push(t_list **a_stack, t_list **b_stack, t_operation o)
{
	t_list	*elem;
	t_list	**stack1;
	t_list	**stack2;

	stack1 = o == PA ? a_stack : NULL;
	stack1 = o == PB ? b_stack : stack1;
	stack2 = o == PA ? b_stack : NULL;
	stack2 = o == PB ? a_stack : stack2;
	if (stack2 != NULL)
	{
		if (ft_lstlen(*stack2) >= 1)
		{
			elem = *stack2;
			*stack2 = elem->next;
			elem->next = *stack1;
			*stack1 = elem;
		}
	}
}

void	execute_operations(t_list **a_stack, t_list **b_stack, \
							t_list *operations)
{
	t_operation	o;

	while (operations != NULL)
	{
		o = *(t_operation *)operations->content;
		swap(a_stack, b_stack, o);
		push(a_stack, b_stack, o);
		rotate(a_stack, b_stack, o);
		reverse_rotate(a_stack, b_stack, o);
		operations = operations->next;
	}
}
