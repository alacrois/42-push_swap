/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/07 00:16:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

#define DEBUG false
#define DEBUG_INFOS false

int			check_for_next_targets(t_so so, int order_index, int index)
{
	int		next_target;
	int		target;

	// return (0);
	target = so.ordered_numbers[order_index];
	if (order_index + 1 < so.a_stack->max_size)
	{
		next_target = so.ordered_numbers[order_index + 1];
		// printf("Target = %i && next target = %i\n", target, next_target);
		if (so.a_stack->data[so.a_stack->size - 1] == next_target)
		{
			execute_and_save_operation(so.a_stack, so.b_stack, so.operations, PB);
			add_operation(so.pending_b_operations, SB);
			if (DEBUG == true)
				printf("Next target (%i) is on top ! (current target = %i & target index = %i)\n", \
					next_target, target, index);
			return (1);
		}
	}
	return (0);
}

void		put_indexed_element_on_top(t_so so, int order_index, int index)
{
	int		len;
	t_stack	*a_stack;
	t_list	**operations;
	int		target;
	// int		next_target;

	a_stack = so.a_stack;
	operations = so.operations;
	if (a_stack->size == 0)
		return ;
	target = so.ordered_numbers[order_index];
	// if (order_index + 1 < a_stack->max_size)
	// {
	// 	next_target = so.ordered_numbers[order_index + 1];
	// 	printf("Target = %i && next target = %i\n", target, next_target);
	// }
	len = a_stack->size;
	if (index - 1 <= len / 2)
	{
		while (index != 1)
		{
			if (DEBUG == true)
				printf("Element on top : %i (target : %i)\n", \
				a_stack->data[a_stack->size - 1], target);
			if (check_for_next_targets(so, order_index, index) == 1)
				index--;
			else
			{
				execute_and_save_operation(a_stack, NULL, operations, RA);
				index--;
			}
		}
	}
	else
	{
		while (index <= a_stack->size)
		{
			if (DEBUG == true)
				printf("Element on top : %i (target : %i)\n", \
				a_stack->data[a_stack->size - 1], target);
			if (check_for_next_targets(so, order_index, index) == 1)
				index--;
			else
			{
				execute_and_save_operation(a_stack, NULL, operations, RRA);
				index++;
			}
		}
	}
}

void		execute_pending_b_operations(t_so so)
{
	t_operation		o;
	t_list			*elem;

	elem = *so.pending_b_operations;
	while (elem != NULL)
	{
		o = *((t_operation *)elem->content);
		execute_and_save_operation(so.a_stack, so.b_stack, so.operations, o);
		if (DEBUG == true)
		{
			ft_putstr("Executed operation ");
			ft_putnbr((int)o);
			ft_putendl(" from 'pending_b_operations' list !");
		}
		elem = elem->next;
	}
	free_list(so.pending_b_operations);
}

t_so		init_stacks_and_operations(t_stack *a_stack, t_stack *b_stack, \
				t_list **operations, t_list **pending_b_operations)
{
	t_so	so;

	so.a_stack = a_stack;
	so.b_stack = b_stack;
	so.operations = operations;
	so.pending_b_operations = pending_b_operations;
	return (so);
}

void		execute_one_operation(t_so *so, t_operation o)
{
	stack_swap(so->a_stack, so->b_stack, o);
	stack_push(so->a_stack, so->b_stack, o);
	stack_rotate(so->a_stack, so->b_stack, o);
	stack_reverse_rotate(so->a_stack, so->b_stack, o);
}

void		undo_all_operations(t_so *so)
{
	t_list		*elem;
	t_operation	o;
	int			len;
	int			i;

	elem = *(so->operations);
	// printf("Operations before changing : \n");
	// display_operations(*so->operations);
	while (elem != NULL)
	{
		o = *((t_operation *)elem->content);
		if (o == PA)
			*((t_operation *)elem->content) = PB;
		else if (o == PB)
			*((t_operation *)elem->content) = PA;
		else if (o == RR)
			*((t_operation *)elem->content) = RRR;
		else if (o == RRR)
			*((t_operation *)elem->content) = RR;
		else if (o == RA)
			*((t_operation *)elem->content) = RRA;
		else if (o == RRA)
			*((t_operation *)elem->content) = RA;
		else if (o == RB)
			*((t_operation *)elem->content) = RRB;
		else if (o == RRB)
			*((t_operation *)elem->content) = RB;
		elem = elem->next;		
	}
	// printf("Operations AFTER changing : \n");
	// display_operations(*so->operations);
	// ft_putendl("=============================");
	len = ft_lstlen(*so->operations);
	i = len;
	while (i > 0)
	{
		elem = ft_lstelem(*(so->operations), i);
		o = *((t_operation *)elem->content);
		execute_one_operation(so, o);
		i--;
	}
	// ft_putendl("D1");
	free_list(so->operations);
	// ft_putendl("D2");
	*(so->operations) = NULL;
}

t_list		*generate_operations(t_stack *a_stack)
{
	t_list	*operations;
	t_list	*pending_b_operations;
	t_so	so;
	t_stack	b_stack;
	int		numbers[a_stack->max_size];
	int		i;
	int		len;
	// int		target;
	int		element_to_find_index;
	int		ooo;
	size_t		op_len;

	operations = NULL;
	pending_b_operations = NULL;
	b_stack = new_stack(a_stack->max_size);
	b_stack.size = 0;
	so = init_stacks_and_operations(a_stack, &b_stack, \
							&operations, &pending_b_operations);
	get_ordered_numbers_in_array(a_stack, numbers);
	so.ordered_numbers = numbers;
	len = a_stack->size;

	// printf("Stack is of size : %i\n", len);
	if (len >= SMALL_STACK_THRESHOLD)
		pre_sort_stack(&so);
	else
	{
		ooo = out_of_order(&so);
		// printf("Out of order : %i (size = %i)\n\n", ooo, a_stack->max_size);
		// if (ooo >= (a_stack->max_size / 2) + 1)
		if (ooo >= 1)
		{
			sort_small(&so);
			op_len = ft_lstlen(*so.operations);

			// printf("Stack before undoing all :\n");
			// display_infos(*a_stack, b_stack, operations);
			undo_all_operations(&so);
			// printf("Stack after undoing all :\n");
			// display_infos(*a_stack, b_stack, operations);
			// printf("=====================\n");

			inverse_order(&so);
			sort_small(&so);
			if (op_len < ft_lstlen(*so.operations))
			{
				undo_all_operations(&so);
				sort_small(&so);
				// printf("'inverse order' not used !\n");
			}
			else
			{
				// printf("'inverse order' used !\n");
			}
			
			// printf("Stack inversed :\n");
			// display_infos(*a_stack, b_stack, operations);
			// ooo = out_of_order(&so);
			// printf("Out of order : %i (size = %i)\n\n", ooo, a_stack->max_size);

		}
		else
			sort_small(&so);
		// trim_operations(&operations);
		if (DEBUG_INFOS == true)
			printf("Total number of operations (before trimming): %i\n", (int)ft_lstlen(operations));
		return (operations);
	}
	i = -1;
	while (++i < len)
	{
		// target = so.ordered_numbers[i];
		element_to_find_index = get_element_index(a_stack, numbers[i]);
		if (element_to_find_index != -1)
		{
			put_indexed_element_on_top(so, i, element_to_find_index);
			execute_and_save_operation(a_stack, &b_stack, &operations, PB);
			if (pending_b_operations != NULL)
			{
				if (DEBUG == true)
					printf("Before 'execute_pending_b_operations' : top a = %i && top b = %i\n", \
						a_stack->data[a_stack->size - 1], b_stack.data[b_stack.size - 1]);
				// display_infos(*a_stack, b_stack, operations);
				// ft_putstr("=================\n");

				execute_pending_b_operations(so);
			}
		}
	}
	if (pending_b_operations != NULL)
	{
			if (DEBUG == true)
				printf("D2\n");
			execute_pending_b_operations(so);
	}
	all_b_to_a(a_stack, &b_stack, &operations);
	if (DEBUG_INFOS == true)
		printf("Total number of operations (before trimming): %i\n", (int)ft_lstlen(operations));
	// trim_operations(&operations);
	return (operations);
}

