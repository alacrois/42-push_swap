/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/08 03:10:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			stack_swap(t_stack *a_stack, t_stack *b_stack, t_operation o)
{
	t_stack	*stack;
	int		tmp;

	stack = o == SA ? a_stack : NULL;
	stack = o == SB ? b_stack : stack;
	if (o == SS)
	{
		stack_swap(a_stack, b_stack, SA);
		stack_swap(a_stack, b_stack, SB);
	}
	if (stack != NULL)
	{
		if (stack->size >= 2)
		{
			tmp = stack->data[stack->size - 1];
			stack->data[stack->size - 1] = stack->data[stack->size - 2];
			stack->data[stack->size - 2] = tmp;
		}
	}
}

void			stack_push(t_stack *a_stack, t_stack *b_stack, t_operation o)
{
	t_stack		*stack1;
	t_stack		*stack2;

	stack1 = o == PA ? a_stack : NULL;
	stack1 = o == PB ? b_stack : stack1;
	stack2 = o == PA ? b_stack : NULL;
	stack2 = o == PB ? a_stack : stack2;
	if (stack2 != NULL && stack2->size >= 1)
	{
		add_top(stack1, stack2->data[stack2->size - 1]);
		remove_top(stack2);
	}
}

void			stack_rotate(t_stack *a_stack, t_stack *b_stack, t_operation o)
{
	t_stack		*stack;
	int			index;
	int			tmp;

	stack = o == RA ? a_stack : NULL;
	stack = o == RB ? b_stack : stack;
	if (o == RR)
	{
		stack_rotate(a_stack, b_stack, RA);
		stack_rotate(a_stack, b_stack, RB);
	}
	if (stack != NULL && stack->size >= 2)
	{
		index = stack->size - 1;
		tmp = stack->data[index];
		while (index > 0)
		{
			stack->data[index] = stack->data[index - 1];
			index--;
		}
		stack->data[0] = tmp;
	}
}

void			stack_reverse_rotate(t_stack *a_stack, t_stack *b_stack, \
				t_operation o)
{
	t_stack		*stack;
	int			index;
	int			tmp;

	stack = o == RRA ? a_stack : NULL;
	stack = o == RRB ? b_stack : stack;
	if (o == RRR)
	{
		stack_reverse_rotate(a_stack, b_stack, RRA);
		stack_reverse_rotate(a_stack, b_stack, RRB);
	}
	if (stack != NULL && stack->size >= 2)
	{
		index = 0;
		tmp = stack->data[0];
		while (index < stack->size - 1)
		{
			stack->data[index] = stack->data[index + 1];
			index++;
		}
		stack->data[stack->size - 1] = tmp;
	}
}

void			execute_stack_operations(t_stack *a_stack, t_stack *b_stack, \
									t_list *operations)
{
	t_operation	o;

	while (operations != NULL)
	{
		o = *(t_operation *)operations->content;
		stack_swap(a_stack, b_stack, o);
		stack_push(a_stack, b_stack, o);
		stack_rotate(a_stack, b_stack, o);
		stack_reverse_rotate(a_stack, b_stack, o);
		operations = operations->next;
	}
}
