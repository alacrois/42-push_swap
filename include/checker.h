/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/02 22:27:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "libft.h"
# define DISPLAY_INFOS true

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

typedef struct	s_stack
{
	int			*data;
	int			size;
	int			max_size;
}				t_stack;


void			add_operation(t_list **operations, t_operation o);
t_list			*parse_operations();
// t_list			*parse_stack(int ac, char **av);
t_stack			parse_stack(int ac, char **av);
// t_bool			stack_has_duplicates(t_list *a_stack);
t_bool			stack_has_duplicates(t_stack a_stack);
void			free_list(t_list **list);
void			execute_operations(t_list **a_stack, \
				t_list **b_stack, t_list *operations);
t_bool			is_ordered(t_list *stack);
t_bool			stack_is_ordered(t_stack stack);
// void			display_infos(t_list *a_stack, t_list *b_stack, t_list *operations);
void			display_infos(t_stack a_stack, t_stack b_stack, \
				t_list *operations);
void			swap(t_list **a_stack, t_list **b_stack, t_operation o);
void			push(t_list **a_stack, t_list **b_stack, t_operation o);
void			rotate(t_list **a_stack, t_list **b_stack, t_operation o);
void			reverse_rotate(t_list **a_stack, t_list **b_stack, \
				t_operation o);
t_bool			is_int(char *s);
// t_list			*generate_operations(t_list **a_stack);
t_list			*generate_operations(t_stack *a_stack);
void			display_operations(t_list *operations);

void			stack_swap(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_push(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_rotate(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_reverse_rotate(t_stack *a_stack, t_stack *b_stack, \
				t_operation o);
int				number_at_index(t_stack s, int index);
void			remove_top(t_stack *s);
void			add_top(t_stack *s, int n);
void			add_bottom(t_stack *s, int n);
t_stack			new_stack(int size);
void			execute_stack_operations(t_stack *a_stack, t_stack *b_stack, \
				t_list *operations);

#endif
