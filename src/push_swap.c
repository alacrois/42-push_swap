/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/25 22:35:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				get_output_file(int ac, char **av, int *file)
{
	*file = 1;
	if (ft_strcmp((const char *)av[1], "-w") == 0)
	{
		if (ac < 4)
			return (-1);
		*file = open(av[2], O_CREAT | O_WRONLY | O_TRUNC);
		if (*file == -1)
			exit_error();
	}
	return (0);
}

int				main(int ac, char **av)
{
	t_stack		a_stack;
	t_list		*operations;
	int			output;

	if (ac < 2 || get_output_file(ac, av, &output) == -1)
		return (0);
	a_stack = parse_stack(ac, av, output != 1 ? 2 : 0);
	if (a_stack.size == 0 || stack_has_duplicates(a_stack) == true)
		return (return_error());
	operations = generate_operations(&a_stack);
	display_operations(operations, output);
	if (output != 1)
		close(output);
	free_list(&operations);
	free_stack(a_stack);
	return (0);
}
