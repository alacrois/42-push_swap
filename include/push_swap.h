/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/09 18:56:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"
# define DISPLAY_INFOS true
# define ENABLE_PRE_SORT true
# define SMALL_STACK_THRESHOLD 12

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

typedef struct	s_so
{
	t_stack		*a_stack;
	t_stack		*b_stack;
	t_list		**operations;
	t_list		**pending_b_operations;
	int			*ordered_numbers;
	int			*numbers_isolation;
	float		average_isolation;
	float		max_isolation;
}				t_so;

void			add_operation(t_list **operations, t_operation o);
t_list			*parse_operations();
t_stack			parse_stack(int ac, char **av);
t_bool			stack_has_duplicates(t_stack a_stack);
void			free_list(t_list **list);
t_bool			stack_is_ordered(t_stack stack);
void			display_infos(t_stack a_stack, t_stack b_stack, \
				t_list *operations);
t_bool			is_int(char *s);
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
void			execute_and_save_operation(t_stack *a_stack, t_stack *b_stack, \
				t_list **operations, t_operation o);
int				get_element_index(t_stack *stack, int to_find);
void			all_b_to_a(t_stack *a_stack, t_stack *b_stack, \
				t_list **operations);
int				get_minimum(t_stack *stack, int *nextmin);
void			get_ordered_numbers_in_array(t_stack *a_stack, int numbers[]);

void			pre_sort_stack(t_so *so);
void			sort_small(t_so *so);

void			trim_operations(t_list **operations);
t_bool			check_order(t_so *so);
int				out_of_order(t_so *so);
void			optimise_last_rotations(t_list **operations, int stack_size);
void			inverse_order(t_so *so);
void			undo_all_operations(t_so *so);
int				nb_at_index_mod(t_stack *stack, int index, int size);

void			put_indexed_element_on_top(t_so so, int order_index, int index);
void			check_swap_b(t_so *so);
void			undo_all_operations(t_so *so);
int				get_index_distance(int a, int b, int size);
void			free_stack(t_stack s);
void			quicksort(t_so *so);

#endif
