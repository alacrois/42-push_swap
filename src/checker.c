/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 17:41:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// static void			checker_result(t_stack a, t_stack b, 
// 						t_list *operations, t_options options)
static void				checker_result(t_so *so)
{
	// display_infos(a, b, operations, options);
	// display_infos(so);
	// display_infos(so);
	// display_infos(so);
	// display_infos(so);
	if (so->b_stack->size > 0)
	{
		if (so->options.color == true)
			ft_putendl("\e[1;31mKO\e[0m (B stack not empty)");
		else
			ft_putendl("KO");
	}
	else if (stack_is_ordered(*so->a_stack) == false)
	{
		if (so->options.color == true)
			ft_putendl("\e[1;31mKO\e[0m (not in order)");
		else
			ft_putendl("KO");
	}
	else
	{
		if (so->options.color == true)
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
	options.display_stacks = 1;
	return (options);
}

int					main(int ac, char **av)
{
	t_stack			a_stack;
	t_stack			b_stack;
	t_list			*operations;
	// t_options		options;
	t_so			so;

	// display_test();
	if (ac < 2)
		return (0);
	a_stack = parse_stack(ac, av);
	if (a_stack.size == 0 || stack_has_duplicates(a_stack) == true)
		return (return_error());
	so.options = set_options(ac, av);
	operations = parse_operations();
	b_stack = new_stack(a_stack.size);
	b_stack.size = 0;
	so.a_stack = &a_stack;
	so.b_stack = &b_stack;
	so.operations = &operations;
	so.printed_lines = 0;
	so.checker = true;
	// execute_all_operations(&a_stack, &b_stack, operations);
	execute_all_operations(&so);
	// checker_result(a_stack, b_stack, operations, options);
	checker_result(&so);
	free_list(&operations);
	free_stack(a_stack);
	free_stack(b_stack);
	return (0);
}
