/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/08 03:10:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
