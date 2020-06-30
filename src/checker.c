/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/06/30 17:00:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

int		main(int ac, char **av)
{
	t_list		*operations;
	t_operation	*o;

	if (ac == 1 && av == NULL)
		return (0);
	operations = parse_operations();
	if (operations == NULL)
		ft_putendl("No valid operation given !\n");
	else
	{
		while (operations != NULL)
		{
			o = (t_operation *)operations->content;
			printf("%i\n", (int)*o);
			operations = operations->next;
		}
	}
	return(0);
}