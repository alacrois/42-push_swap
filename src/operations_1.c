/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/09 01:22:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		execute_and_save_operation(t_stack *a_stack, t_stack *b_stack, \
										t_list **operations, t_operation o)
{
	if (o < PA)
		stack_swap(a_stack, b_stack, o);
	else if (o < RA)
		stack_push(a_stack, b_stack, o);
	else if (o < RRA)
		stack_rotate(a_stack, b_stack, o);
	else
		stack_reverse_rotate(a_stack, b_stack, o);
	add_operation(operations, o);
	if (o == PB)
		display_infos(*a_stack, *b_stack, *operations);
}

int			get_element_index(t_stack *stack, int to_find)
{
	int		index;
	int		to_compare;
	int		i;

	index = 1;
	i = stack->size;
	while (--i >= 0)
	{
		to_compare = stack->data[i];
		if (to_find == to_compare)
			return (index);
		index++;
	}
	return (-1);
}

void		all_b_to_a(t_stack *a_stack, t_stack *b_stack, \
										t_list **operations)
{
	while (b_stack->size > 0)
		execute_and_save_operation(a_stack, b_stack, operations, PA);
}

int			get_minimum(t_stack *stack, int *nextmin)
{
	int		tmp;
	int		n;
	int		i;

	tmp = 2147483647;
	i = -1;
	while (++i < stack->size)
	{
		n = stack->data[i];
		if (n <= tmp && (nextmin == NULL || n >= *nextmin))
			tmp = n;
	}
	if (nextmin != NULL && tmp < *nextmin)
	{
		ft_putstr("get_minimum error ! tmp = ");
		ft_putnbr(tmp);
		ft_putstr(" & *nextmin = ");
		ft_putnbr(*nextmin);
		ft_exit(0);
	}
	return (tmp);
}

void		get_ordered_numbers_in_array(t_stack *a_stack, int numbers[])
{
	int		i;
	int		len;
	int		nextmin;

	if (a_stack->size == 0)
		return ;
	len = a_stack->size;
	numbers[0] = get_minimum(a_stack, NULL);
	nextmin = numbers[0] + 1;
	i = 0;
	while (++i < len)
	{
		numbers[i] = get_minimum(a_stack, &nextmin);
		nextmin = numbers[i] + 1;
	}
}
