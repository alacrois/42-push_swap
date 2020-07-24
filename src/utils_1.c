/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 09:30:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				return_error(void)
{
	ft_putstr_fd("Error\n", 2);
	return (0);
}

t_bool			is_int(char *s)
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
