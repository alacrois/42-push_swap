/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 14:31:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

static void		display_stacks(t_stack a, t_stack b, t_options options)
{
	int			n;
	int			i;

	if (options.details == 0 || a.max_size > DISPLAY_STACK_MAX_SIZE)
		return ;
	ft_putendl("\nA		B\n");
	i = 0;
	while (++i <= a.max_size)
	{
		if (i <= a.size)
		{
			n = number_at_index(a, i);
			ft_putnbr(n);
			ft_putnchar(' ', 16 - nb_len(n));
		}
		else
			ft_putnchar(' ', 16);
		if (i <= b.size)
		{
			n = number_at_index(b, i);
			ft_putnbr(n);
		}
		ft_putchar('\n');
	}
}

void			display_infos(t_stack a_stack, t_stack b_stack, \
								t_list *operations, t_options options)
{
	display_stacks(a_stack, b_stack, options);
	if (options.details == 0)
		return ;
	ft_putstr("\nTotal number of operations : ");
	ft_putnbr(ft_lstlen(operations));
	ft_putchar('\n');
}

static void		display_operation(t_operation o)
{
	if (o == SA)
		ft_putendl("sa");
	else if (o == SB)
		ft_putendl("sb");
	else if (o == SS)
		ft_putendl("ss");
	else if (o == PA)
		ft_putendl("pa");
	else if (o == PB)
		ft_putendl("pb");
	else if (o == RA)
		ft_putendl("ra");
	else if (o == RB)
		ft_putendl("rb");
	else if (o == RR)
		ft_putendl("rr");
	else if (o == RRA)
		ft_putendl("rra");
	else if (o == RRB)
		ft_putendl("rrb");
	else if (o == RRR)
		ft_putendl("rrr");
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
		elem = elem->next;
	}
}
