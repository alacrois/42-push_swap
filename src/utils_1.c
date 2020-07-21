/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/21 03:32:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_bool		is_int(char *s)
{
	long long	value;
	int			sign;
	int			i;

	i = 0;
	sign = 1;
	value = 0;
	if (s[0] == '-')
	{
		sign = -1;
		i++;
	}
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (false);
		value = value * 10 + (int)(s[i] - '0');
		if (value * sign < -2147483648 || value * sign > 2147483647)
			return (false);
		i++;
	}
	return (true);
}

static int	nb_len(int n)
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

void		display_infos(t_stack a_stack, t_stack b_stack, t_list *operations)
{
	int			n;
	int			i;

	// if (DEBUG_SIMPLE_SORT == true && ft_lstlen(operations) < 250)
	// 	return ;
	ft_putendl("A		B\n");
	i = 0;
	while (++i <= a_stack.max_size)
	{
		if (i <= a_stack.size)
		{
			n = number_at_index(a_stack, i);
			ft_putnbr(n);
			ft_putnchar(' ', 16 - nb_len(n));
		}
		else
			ft_putnchar(' ', 16);
		if (i <= b_stack.size)
		{
			n = number_at_index(b_stack, i);
			ft_putnbr(n);
		}
		ft_putchar('\n');
	}
	ft_putstr("\nTotal number of operations : ");
	ft_putnbr(ft_lstlen(operations));
	ft_putchar('\n');
	
	// if (DEBUG_SIMPLE_SORT == true && ft_lstlen(operations) >= 350)
	// 	ft_exit("After 342 operations.");
}

static void	display_operation(t_operation o)
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

void		display_operations(t_list *operations)
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
