/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/02 18:01:04 by marvin           ###   ########.fr       */
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

int			get_element_index(t_list **stack, int to_find)
{
	int		index;
	int		to_compare;
	t_list	*elem;

	index = 1;
	elem = stack != NULL ? *stack : NULL;
	while (elem != NULL)
	{
		to_compare = *((int *)elem->content);
		if (to_find == to_compare)
			return (index);
		index++;
		elem = elem->next;
	}
	return (-1);
}

void		put_indexed_element_on_top(t_list **a_stack, int index, \
										t_list **operations)
{
	int		len;

	if (a_stack == NULL || *a_stack == NULL)
		return ;
	len = ft_lstlen(*a_stack);
	// TO DO : Optimize the number of shifts (RRA or RA)
	if (index <= len / 2)
	{
		while (index != 1)
		{
			execute_and_save_operation(a_stack, NULL, operations, RA);
			index--;
		}
	}
	else
	{
		while (index <= len)
		{
			execute_and_save_operation(a_stack, NULL, operations, RRA);
			index++;
		}
	}
}

// void		insert_at_index(t_list **a_stack)


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

int			get_minimum(t_list *stack, int *nextmin)
{
	int		tmp;
	int		n;

	// n = *((int *)stack->content);
	tmp = 2147483647;
	while (stack != NULL)
	{
		n = *((int *)stack->content);
		if (n <= tmp && (nextmin == NULL || n >= *nextmin))
			tmp = n;
		stack = stack->next;
	}
	if (nextmin != NULL && tmp < *nextmin)
	{
		ft_putendl("get_minimum error !");
		printf("tmp = %i  &&  *nextmin = %i\n", tmp, *nextmin);
	}
	else
	{
		// printf("get_minimum returns %i\n", tmp);
	}
	
	return (tmp);
}

void		get_ordered_numbers_in_array(t_list	**a_stack, int numbers[])
{
	int		i;
	int		len;
	int		nextmin;

	if (a_stack == NULL || *a_stack == NULL)
		return ;
	len = ft_lstlen(*a_stack);
	numbers[0] = get_minimum(*a_stack, NULL);
	nextmin = numbers[0] + 1;
	i = 0;
	while (++i < len)
	{
		numbers[i] = get_minimum(*a_stack, &nextmin);
		nextmin = numbers[i] + 1;
	}
}

t_list		*generate_operations(t_list **a_stack)
{
	t_list	*operations;
	t_list	*b_stack;
	int		n1;
	int		n2;
	int		numbers[ft_lstlen(*a_stack)];
	int		i;
	int		len;

	get_ordered_numbers_in_array(a_stack, numbers);
	i = -1;
	len = ft_lstlen(*a_stack);
	while (++i < len)
	{
		printf("numbers[%i] = %i\n", i, numbers[i]);
	}

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