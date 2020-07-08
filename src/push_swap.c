/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/08 03:21:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	return_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}

int			main(int ac, char **av)
{
	t_stack		a_stack;
	t_list		*operations;

	if (ac < 2)
		return (0);
	a_stack = parse_stack(ac, av);
	if (a_stack.size == 0 || stack_has_duplicates(a_stack) == true)
		return (return_error());
	operations = generate_operations(&a_stack);
	display_operations(operations);
	free_list(&operations);
	return (0);
}
