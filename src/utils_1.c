/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 14:28:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				return_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (1);
}

void			exit_error(void)
{
	ft_putstr_fd("Error\n", 2);
	exit(1);
}

void			free_list(t_list **list)
{
	t_list		*elem;
	t_list		*next_elem;

	elem = list != NULL ? *list : NULL;
	while (elem != NULL)
	{
		next_elem = elem->next;
		if (elem->content != NULL)
			free(elem->content);
		free(elem);
		elem = next_elem;
	}
	if (list != NULL)
		*list = NULL;
}

static int		get_minimum(t_stack *stack, int *nextmin)
{
	int			tmp;
	int			n;
	int			i;

	tmp = 2147483647;
	i = -1;
	while (++i < stack->size)
	{
		n = stack->data[i];
		if (n <= tmp && (nextmin == NULL || n >= *nextmin))
			tmp = n;
	}
	if (nextmin != NULL && tmp < *nextmin)
	{
		ft_putstr("get_minimum error ! tmp = ");
		ft_putnbr(tmp);
		ft_putstr(" & *nextmin = ");
		ft_putnbr(*nextmin);
		ft_exit(0);
	}
	return (tmp);
}

void			get_ordered_numbers_in_array(t_stack *a_stack, int numbers[])
{
	int			i;
	int			len;
	int			nextmin;

	if (a_stack->size == 0)
		return ;
	len = a_stack->size;
	numbers[0] = get_minimum(a_stack, NULL);
	nextmin = numbers[0] + 1;
	i = 0;
	while (++i < len)
	{
		numbers[i] = get_minimum(a_stack, &nextmin);
		nextmin = numbers[i] + 1;
	}
}
