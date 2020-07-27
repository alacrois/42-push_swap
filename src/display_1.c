/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/27 16:51:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			display_operation(t_operation o)
{
	if (o == SA)
		ft_putstr("sa");
	else if (o == SB)
		ft_putstr("sb");
	else if (o == SS)
		ft_putstr("ss");
	else if (o == PA)
		ft_putstr("pa");
	else if (o == PB)
		ft_putstr("pb");
	else if (o == RA)
		ft_putstr("ra");
	else if (o == RB)
		ft_putstr("rb");
	else if (o == RR)
		ft_putstr("rr");
	else if (o == RRA)
		ft_putstr("rra");
	else if (o == RRB)
		ft_putstr("rrb");
	else if (o == RRR)
		ft_putstr("rrr");
}

static int		nb_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n > 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void		display_stacks(t_so *so)
{
	int			n;
	int			i;

	ft_putendl("A		B\n");
	i = 0;
	while (++i <= so->a_stack->max_size)
	{
		if (i <= so->a_stack->size)
		{
			n = number_at_index(*so->a_stack, i);
			ft_putnbr(n);
			ft_putnchar(' ', 16 - nb_len(n));
		}
		else
			ft_putnchar(' ', 16);
		if (i <= so->b_stack->size)
		{
			n = number_at_index(*so->b_stack, i);
			ft_putnbr(n);
			ft_putnchar(' ', 16 - nb_len(n));
		}
		else
			ft_putnchar(' ', 16);
		ft_putchar('\n');
	}
}

void			display_infos(t_so *so, int number_of_operations, \
					t_operation last_o)
{
	if (so->printed_lines > 0)
	{
		move_cursor_back_n_lines(so->printed_lines);
		so->printed_lines = 0;
	}
	else if (so->options.display_stacks == 1)
		ft_putchar('\n');
	if (so->options.display_stacks == 1 && \
		so->a_stack->max_size <= DISPLAY_STACK_MAX_SIZE)
	{
		display_stacks(so);
		so->printed_lines += 2 + so->a_stack->max_size;
		usleep((unsigned int)((float)1000000 * DISPLAY_SLEEP_INTERVAL));
	}
	if (so->options.details == 1)
		display_details(so, number_of_operations, last_o);
}

void			display_operations(t_list *operations)
{
	t_list		*elem;
	t_operation	o;

	elem = operations;
	while (elem != NULL)
	{
		o = *(t_operation *)elem->content;
		display_operation(o);
		ft_putchar('\n');
		elem = elem->next;
	}
}
