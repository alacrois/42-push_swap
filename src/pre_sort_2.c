/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_sort_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/06 22:25:41 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

void			optimise_last_rotations(t_list **operations, int stack_size)
{
	int			len;
	t_list		*elem;
	t_list		*tmp;
	t_operation	o;
	t_operation	last_rotation;
	int			count;
	int			index;

	if (operations == NULL || *operations == NULL)
		return ;
	len = ft_lstlen(*operations);
	index = len;
	elem = ft_lstelem(*operations, index);
	o = *((t_operation *)elem->content);
	// ft_putendl("D11");
	if (o != RA && o != RRA)
		return ;
	last_rotation = o;
	count = 0;
	// ft_putendl("D12");
	while (o == last_rotation && index > 0)
	{
		elem = ft_lstelem(*operations, index);
		o = *((t_operation *)elem->content);
		if (o == last_rotation)
			count++;
		index--;
	}
	// ft_putendl("D13");
	if (stack_size - count < count)
	{
		// if (last_rotation == RA)
		// 	printf("Replacing last %i RA with %i RRA\n", count, stack_size - count);
		// else
		// 	printf("Replacing last %i RRA with %i RA\n", count, stack_size - count);
		// printf("Sequence previously was :\n");
		// display_operations(*operations);
		// printf("===================\n");
		if (o != last_rotation)
		{
			tmp = elem;
			elem = elem->next;
			tmp->next = NULL;
			free_list(&elem);
		}
		else
		{
			free_list(operations);
			*operations = NULL;
		}
		
		// if (*operations == NULL)
		// 	printf("*operations == NULL\n");
		// else
		// {
		// 	printf("*operations != NULL\n");
		// 	o = *((t_operation *)(*operations)->content);
		// 	printf("o = %i\n", (int)o);
		// }
		
		o = last_rotation == RA ? RRA : RA;
		while (count < stack_size)
		{
			add_operation(operations, o);
			count++;
		}
	}
	// ft_putendl("D14");

}

void	inverse_order(t_so *so)
{
	int	len;
	int i;

	len = so->a_stack->max_size;
	i = len;
	while (--i >= 2)
	{
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PB);
		if (so->b_stack->size > 1)
			execute_and_save_operation(so->a_stack, so->b_stack, so->operations, RB);
	}
	execute_and_save_operation(so->a_stack, so->b_stack, so->operations, SA);
	while (so->b_stack->size > 0)
		execute_and_save_operation(so->a_stack, so->b_stack, so->operations, PA);
}