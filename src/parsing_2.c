/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/27 19:48:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				parse_options(int ac, char **av, t_so *so)
{
	int			i;
	int			options;

	options = 0;
	i = 1;
	so->options.color = false;
	so->options.details = false;
	so->options.display_stacks = false;
	so->options.fast = false;
	while (i < ac && av[i][0] == '-')
	{
		if (ft_strlen(av[i]) == 2 && av[i][1] == 'v')
			so->options.display_stacks = true;
		else if (ft_strlen(av[i]) == 2 && av[i][1] == 'f')
			so->options.fast = true;
		else if (ft_strlen(av[i]) == 2 && av[i][1] == 'c')
			so->options.color = true;
		else if (ft_strlen(av[i]) == 2 && av[i][1] == 'd')
			so->options.details = true;
		else
			return (options);
		i++;
		options++;
	}
	return (options);
}
