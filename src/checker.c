/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 16:54:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void			checker_result(t_stack a, t_stack b, \
						t_list *operations, t_options options)
{
	display_infos(a, b, operations, options);
	if (b.size > 0)
	{
		if (options.color == true)
			ft_putendl("\e[1;31mKO\e[0m (B stack not empty)");
		else
			ft_putendl("KO");
	}
	else if (stack_is_ordered(a) == false)
	{
		if (options.color == true)
			ft_putendl("\e[1;31mKO\e[0m (not in order)");
		else
			ft_putendl("KO");
	}
	else
	{
		if (options.color == true)
			ft_putendl("\e[1;32mOK\e[0m");
		else
			ft_putendl("OK");
	}
}

static t_options	set_options(int ac, char **av)
{
	t_options		options;

	if (ac == 0 || av == NULL)
		ft_exit("Help !!");
	options.color = true;
	options.details = 1;
	return (options);
}

int					main(int ac, char **av)
{
	t_stack			a_stack;
	t_stack			b_stack;
	t_list			*operations;
	t_options		options;

	if (ac < 2)
		return (return_error());
	a_stack = parse_stack(ac, av);
	if (a_stack.size == 0 || stack_has_duplicates(a_stack) == true)
		return (return_error());
	options = set_options(ac, av);
	operations = parse_operations();
	b_stack = new_stack(a_stack.size);
	b_stack.size = 0;
	execute_all_operations(&a_stack, &b_stack, operations);
	checker_result(a_stack, b_stack, operations, options);
	free_list(&operations);
	return (0);
}
