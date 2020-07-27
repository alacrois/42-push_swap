/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/27 20:33:17 by marvin           ###   ########.fr       */
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
	while (n >= 10)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

static void		put_nbr_color(int n, t_bool color)
{
	if (color == true)
		ft_putstr("\e[1;33m");
	ft_putnbr(n);
	if (color == true)
		ft_putstr("\e[0m");
	ft_putnchar(' ', 16 - nb_len(n));
}

static void		display_elem_a(t_so *so, int index, t_operation o, \
								t_bool before)
{
	t_bool		color;

	color = false;
	if (so->options.color == true)
	{
		if (index == 1 || index == 2)
		{
			if (o == SS || o == SA)
				color = true;
			if ((before == false && index == 1 && o == PA) || \
				(before == true && index == 1 && o == PB))
				color = true;
			if ((before == false && index == 1 && (o == RRA || o == RRR)) || \
				(before == true && index == 1 && (o == RA || o == RR)))
				color = true;
		}
		if (index == so->a_stack->size)
		{
			if ((before == false && (o == RR || o == RA)) || \
				(before == true && (o == RRR || o == RRA)))
				color = true;
		}
	}
	put_nbr_color(number_at_index(*so->a_stack, index), color);
}

static void		display_elem_b(t_so *so, int index, t_operation o, \
								t_bool before)
{
	t_bool		color;

	color = false;
	if (so->options.color == true)
	{
		if (index == 1 || index == 2)
		{
			if (o == SS || o == SB)
				color = true;
			if ((before == false && index == 1 && o == PB) || \
				(before == true && index == 1 && o == PA))
				color = true;
			if ((before == false && index == 1 && (o == RRB || o == RRR)) || \
				(before == true && index == 1 && (o == RB || o == RR)))
				color = true;
		}
		if (index == so->b_stack->size)
		{
			if ((before == false && (o == RR || o == RB)) || \
				(before == true && (o == RRR || o == RRB)))
				color = true;
		}
	}
	put_nbr_color(number_at_index(*so->b_stack, index), color);
}

void			display_stacks(t_so *so, t_operation o, t_bool before)
{
	int			i;

	ft_putendl("A		B\n");
	i = 0;
	while (++i <= so->a_stack->max_size)
	{
		if (i <= so->a_stack->size)
			display_elem_a(so, i, o, before);
		else
			ft_putnchar(' ', 16);
		if (i <= so->b_stack->size)
			display_elem_b(so, i, o, before);
		else
			ft_putnchar(' ', 16);
		ft_putchar('\n');
	}
}
