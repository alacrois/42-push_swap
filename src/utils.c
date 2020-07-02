/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/02 19:52:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

t_bool	is_int(char *s)
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

void	free_list(t_list **list)
{
	t_list	*elem;
	t_list	*next_elem;

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

void	display_b_stack(t_list *b_stack)
{
	int	*n;

	if (b_stack != NULL)
	{
		n = (int *)b_stack->content;
		ft_putnbr(*n);
		ft_putchar('\n');
	}
	else
		ft_putchar('\n');
}

int		nb_len(int n)
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

void	display_infos(t_list *a_stack, t_list *b_stack, t_list *operations)
{
	int			*n;

	// ft_putstr("Total number of operations : ");
	// ft_putnbr(ft_lstlen(operations));
	ft_putendl("A		B\n");
	while (a_stack != NULL || b_stack != NULL)
	{
		if (a_stack != NULL)
		{
			n = (int *)a_stack->content;
			ft_putnbr(*n);
			ft_putnchar(' ', 16 - nb_len(*n));
		}
		else
			ft_putnchar(' ', 16);
		display_b_stack(b_stack);
		a_stack = a_stack != NULL ? a_stack->next : NULL;
		b_stack = b_stack != NULL ? b_stack->next : NULL;
	}
	ft_putchar('\n');
	ft_putstr("Total number of operations : ");
	ft_putnbr(ft_lstlen(operations));
	ft_putchar('\n');
}
