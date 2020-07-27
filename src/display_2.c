/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/27 16:51:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			move_cursor_back_n_lines(int n)
{
	ft_putstr("\033[");
	ft_putnbr(n);
	ft_putstr("A");
}

void			display_details(t_so *so, int number_of_operations, \
					t_operation last_o)
{
	ft_putstr("\nLast operation : ");
	display_operation(last_o);
	ft_putstr("   \nTotal number of operations : ");
	ft_putnbr(number_of_operations);
	ft_putstr("\nTotal number of elements : ");
	ft_putnbr(so->a_stack->max_size);
	ft_putchar('\n');
	so->printed_lines += 4;
}
