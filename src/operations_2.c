/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/01 15:14:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	rotate(t_list **a_stack, t_list **b_stack, t_operation o)
{
	t_list	*elem;
	t_list	**stack;

	stack = o == RA ? a_stack : NULL;
	stack = o == RB ? b_stack : stack;
	if (o == RR)
	{
		rotate(a_stack, b_stack, RA);
		rotate(a_stack, b_stack, RB);
	}
	if (stack != NULL)
	{
		if (ft_lstlen(*stack) >= 2)
		{
			elem = *stack;
			*stack = elem->next;
			elem->next = NULL;
			ft_lstaddend(stack, elem);
		}
	}
}

void	reverse_rotate(t_list **a_stack, t_list **b_stack, t_operation o)
{
	t_list	*elem;
	t_list	**stack;

	stack = o == RRA ? a_stack : NULL;
	stack = o == RRB ? b_stack : stack;
	if (o == RRR)
	{
		reverse_rotate(a_stack, b_stack, RRA);
		reverse_rotate(a_stack, b_stack, RRB);
	}
	if (stack != NULL)
	{
		if (ft_lstlen(*stack) >= 2)
		{
			elem = ft_lstelem(*stack, ft_lstlen(*stack) - 1);
			elem->next->next = *stack;
			*stack = elem->next;
			elem->next = NULL;
		}
	}
}
