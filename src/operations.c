/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/06/30 20:42:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void	operation_sa(t_list **a_stack, t_list **b_stack, t_operation o)
{
	int		*a;
	int		*b;
	int		tmp;

	if (a_stack == NULL && b_stack == NULL)
		return ;
	if (o == SA || o == SS)
	{
		if (ft_lstlen(*a_stack) >= 2)
		{
			a = (int *)ft_lstelem(*a_stack, 1)->content;
			b = (int *)ft_lstelem(*a_stack, 2)->content;
			tmp = *a;
			*a = *b;
			*b = tmp;
		}
	}
}

void	operation_sb(t_list **a_stack, t_list **b_stack, t_operation o)
{
	int		*a;
	int		*b;
	int		tmp;

	if (a_stack == NULL && b_stack == NULL)
		return ;
	if (o == SB || o == SS)
	{
		if (ft_lstlen(*a_stack) >= 2)
		{
			a = (int *)ft_lstelem(*b_stack, 1)->content;
			b = (int *)ft_lstelem(*b_stack, 2)->content;
			tmp = *a;
			*a = *b;
			*b = tmp;
		}
	}
}

void	execute_operations(t_list **a_stack, t_list **b_stack, t_list *operations)
{
	t_operation	o;

	while (operations != NULL)
	{
		o = *(t_operation *)operations->content;
		operation_sa(a_stack, b_stack, o);
		operations = operations->next;
	}
}

int		is_ordered(t_list *stack)
{
	int	a;
	int	b;

	if (stack == NULL)
		return 1;
	a = *(int *)(stack->content);
	stack = stack->next;
	while (stack != NULL)
	{
		b = *(int *)(stack->content);
		if (a > b)
			return (0);
		if (a == b)
		{
			// Doublon -> erreur
		}
		stack = stack->next;
		a = b;
	}
	return (1);
}