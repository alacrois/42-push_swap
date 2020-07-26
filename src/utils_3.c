/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 14:26:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

void			rotate_elem_on_top(t_so *so, t_bool a_stack, int elem)
{
	t_stack		*s;
	int			len;
	int			index;
	t_operation	rotate_op;

	s = a_stack == true ? so->a_stack : so->b_stack;
	len = s->size;
	index = get_element_index(s, elem);
	if (a_stack == true)
		rotate_op = index - 1 <= len / 2 ? RA : RRA;
	else
		rotate_op = index - 1 <= len / 2 ? RB : RRB;
	while (number_at_index(*s, 1) != elem)
		operation(so, rotate_op);
}

t_sequence		new_sequence(int size, t_operation o1, \
					t_operation o2, t_operation o3)
{
	t_sequence	seq;

	seq.o = (t_operation *)ft_malloc(sizeof(t_operation) * size);
	seq.size = size;
	if (size >= 1)
		seq.o[0] = o1;
	if (size >= 2)
		seq.o[1] = o2;
	if (size >= 3)
		seq.o[2] = o3;
	return (seq);
}

void			free_sequences(t_sequence *so, t_sequence *sr)
{
	int			i;

	i = -1;
	while (++i < 4)
	{
		free(so[i].o);
		free(sr[i].o);
	}
}

t_bool			section_sorted(t_so *so, t_section section, t_bool is_a)
{
	int			i;
	int			a;
	int			b;
	int			start_index;
	t_stack		*s;

	s = is_a == true ? so->a_stack : so->b_stack;
	start_index = get_element_index(s, section.first_elem);
	i = -1;
	while (++i < section.size - 1)
	{
		a = nb_at_index_mod(s, i + start_index + 0);
		b = nb_at_index_mod(s, i + start_index + 1);
		if ((is_a == true && a > b) || (is_a == false && a < b))
			return (false);
	}
	return (true);
}
