/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/25 22:17:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			move_cursor_back_n_lines(int n)
{
	ft_putstr("\033[");
	ft_putnbr(n);
	ft_putstr("A");
}

void			display_operation(t_operation o, int fd)
{
	if (o == SA)
		ft_putstr_fd("sa", fd);
	else if (o == SB)
		ft_putstr_fd("sb", fd);
	else if (o == SS)
		ft_putstr_fd("ss", fd);
	else if (o == PA)
		ft_putstr_fd("pa", fd);
	else if (o == PB)
		ft_putstr_fd("pb", fd);
	else if (o == RA)
		ft_putstr_fd("ra", fd);
	else if (o == RB)
		ft_putstr_fd("rb", fd);
	else if (o == RR)
		ft_putstr_fd("rr", fd);
	else if (o == RRA)
		ft_putstr_fd("rra", fd);
	else if (o == RRB)
		ft_putstr_fd("rrb", fd);
	else if (o == RRR)
		ft_putstr_fd("rrr", fd);
}

static void		display_details(t_so *so, int number_of_operations, \
					t_operation o)
{
	ft_putstr("\nOperation : ");
	if (so->options.color == true)
		ft_putstr("\e[1;33m");
	display_operation(o, 1);
	if (so->options.color == true)
		ft_putstr("\e[0m");
	ft_putstr("   \nTotal number of operations : ");
	if (so->options.color == true)
		ft_putstr("\e[1;33m");
	ft_putnbr(number_of_operations);
	if (so->options.color == true)
		ft_putstr("\e[0m");
	ft_putstr("\nTotal number of elements : ");
	ft_putnbr(so->a_stack->max_size);
	ft_putchar('\n');
	so->printed_lines += 4;
}

void			display_infos(t_so *so, int number_of_operations, \
					t_operation o, t_bool before)
{
	if (so->printed_lines > 0)
	{
		move_cursor_back_n_lines(so->printed_lines);
		so->printed_lines = 0;
	}
	else if (so->options.display_stacks == true)
		ft_putchar('\n');
	if (so->options.display_stacks == true && \
		so->a_stack->max_size <= DISPLAY_STACK_MAX_SIZE)
	{
		display_stacks(so, o, before);
		so->printed_lines += 2 + so->a_stack->max_size;
	}
	if (so->options.details == true)
		display_details(so, number_of_operations, o);
	if (so->options.display_stacks == true && \
		so->a_stack->max_size <= DISPLAY_STACK_MAX_SIZE)
		usleep((unsigned int)((float)1000000 * \
			(so->options.fast == false ? DISPLAY_SLEEP_INTERVAL_NORMAL : \
			DISPLAY_SLEEP_INTERVAL_FAST)));
}

void			display_operations(t_list *operations, int fd)
{
	t_list		*elem;
	t_operation	o;

	elem = operations;
	while (elem != NULL)
	{
		o = *(t_operation *)elem->content;
		display_operation(o, fd);
		ft_putchar_fd('\n', fd);
		elem = elem->next;
	}
}
