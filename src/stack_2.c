/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/27 19:44:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			stack_swap(t_stack *a_stack, t_stack *b_stack, t_operation o)
{
	t_stack		*stack;
	int			tmp;

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

void			execute_all_operations(t_so *so)
{
	t_operation	o;
	t_list		*elem;
	int			i;

	elem = *so->operations;
	i = 0;
	if (elem == NULL)
		display_infos(so, i, -1, false);
	while (elem != NULL)
	{
		i++;
		o = *(t_operation *)elem->content;
		if (so->options.display_stacks == true)
			display_infos(so, i, o, true);
		stack_swap(so->a_stack, so->b_stack, o);
		stack_push(so->a_stack, so->b_stack, o);
		stack_rotate(so->a_stack, so->b_stack, o);
		stack_reverse_rotate(so->a_stack, so->b_stack, o);
		elem = elem->next;
		if (so->options.display_stacks == true)
			display_infos(so, i, o, false);
		else if (elem == NULL)
			display_infos(so, i, -1, false);
	}
}
