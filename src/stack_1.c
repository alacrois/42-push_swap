/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 13:44:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack		new_stack(int size)
{
	t_stack	s;

	s.data = (int *)malloc(sizeof(int) * size);
	if (s.data == NULL)
		ft_exit("Malloc error in 'new_stack'");
	s.size = size;
	s.max_size = size;
	return (s);
}

void		free_stack(t_stack s)
{
	if (s.data != NULL)
		free(s.data);
	s.data = NULL;
	s.size = 0;
}

void		add_top(t_stack *s, int n)
{
	if (s->size >= s->max_size)
		ft_exit("Error in 'add_top' : stack already full !");
	s->data[s->size] = n;
	s->size++;
}

void		remove_top(t_stack *s)
{
	if (s->size > 0)
	{
		s->data[s->size - 1] = 0;
		s->size--;
	}
}

int			number_at_index(t_stack s, int index)
{
	index = s.size - index;
	if (index < 0 || index >= s.size)
		ft_exit("Error in 'number_at_index' : index out of range !");
	return (s.data[index]);
}
