/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/25 22:45:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void			checker_result(t_so *so)
{
	if (so->b_stack->size > 0 || stack_is_ordered(*so->a_stack) == false)
	{
		if (so->options.color == true)
			ft_putendl("\e[1;31mKO\e[0m");
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

static void			init_so(t_so *so, t_stack *a, t_stack *b, \
							t_list **operations)
{
	*b = new_stack(a->size);
	b->size = 0;
	so->a_stack = a;
	so->b_stack = b;
	so->operations = operations;
	so->printed_lines = 0;
	so->checker = true;
}

int					main(int ac, char **av)
{
	t_stack			a_stack;
	t_stack			b_stack;
	t_list			*operations;
	t_so			so;
	int				options;

	if (ac < 2)
		return (0);
	options = parse_options(ac, av, &so);
	if (options == -1)
		return (return_error());
	if (ac == options + 1)
		return (0);
	a_stack = parse_stack(ac, av, options);
	if (a_stack.size == 0 || stack_has_duplicates(a_stack) == true)
		return (return_error());
	operations = parse_operations(so.options.input);
	if (so.options.input != 0)
		close(so.options.input);
	init_so(&so, &a_stack, &b_stack, &operations);
	execute_all_operations(&so);
	checker_result(&so);
	free_list(&operations);
	free_stack(a_stack);
	free_stack(b_stack);
	return (0);
}
