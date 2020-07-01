/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/01 22:54:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# define DISPLAY_STACKS true

typedef	enum	e_operation
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR
}				t_operation;

void			add_operation(t_list **operations, t_operation o);
t_list			*parse_operations();
t_list			*parse_stack(int ac, char **av);
t_bool			stack_has_duplicates(t_list *a_stack);
void			free_list(t_list **list);
void			execute_operations(t_list **a_stack, \
				t_list **b_stack, t_list *operations);
t_bool			is_ordered(t_list *stack);
void			display_stacks(t_list *a_stack, t_list *b_stack);
void			swap(t_list **a_stack, t_list **b_stack, t_operation o);
void			push(t_list **a_stack, t_list **b_stack, t_operation o);
void			rotate(t_list **a_stack, t_list **b_stack, t_operation o);
void			reverse_rotate(t_list **a_stack, t_list **b_stack, \
				t_operation o);
t_bool			is_int(char *s);
t_list			*generate_operations(t_list **a_stack);
void			display_operations(t_list *operations);
#endif
