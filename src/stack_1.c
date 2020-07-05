/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/05 20:17:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"

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

void		add_bottom(t_stack *s, int n)
{
	int		index;

	if (s->size >= s->max_size)
		ft_exit("Error in 'add_bottom' : stack already full !");
	index = s->size;
	while (index > 0)
	{
		s->data[index] = s->data[index - 1];
		index--;
	}
	s->data[0] = n;
	s->size++;
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
