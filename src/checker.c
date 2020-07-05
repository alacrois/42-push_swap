/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/05 23:21:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		return_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}

int		main(int ac, char **av)
{
	t_stack		a_stack;
	t_stack		b_stack;
	t_list		*operations;

	if (ac < 2)
		return (return_error());
	a_stack = parse_stack(ac, av);
	if (a_stack.size == 0 || stack_has_duplicates(a_stack) == true)
		return (return_error());
	operations = parse_operations();

	// display_operations(operations);
	
	b_stack = new_stack(a_stack.size);
	b_stack.size = 0;
	execute_stack_operations(&a_stack, &b_stack, operations);
	if (DISPLAY_INFOS == true)
		display_infos(a_stack, b_stack, operations);
	if (b_stack.size > 0 || stack_is_ordered(a_stack) == false)
		ft_putendl("\e[1;31mKO\e[0m");
	else
		ft_putendl("\e[1;32mOK\e[0m");
	free_list(&operations);
	return (0);
}
