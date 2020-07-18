/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/18 20:24:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"
# define DISPLAY_INFOS true
# define ENABLE_PRE_SORT true
# define SMALL_STACK_THRESHOLD 12
# define DEBUG_CHECKER false
# define DEBUG_MIDSORT true

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

typedef struct s_to_switch
{
	int			elem;
	int			relative_index;
}				t_to_switch;

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
	t_to_switch	*quicksort_less;
	t_to_switch	*quicksort_more;
}				t_so;

typedef struct	s_to_sort
{
	int			value;
	int			ooo;
	t_bool		used;
}				t_to_sort;




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
// int				nb_at_index_mod(t_stack *stack, int index, int size);
int				nb_at_index_mod(t_stack *stack, int index);

void			put_indexed_element_on_top(t_so so, int order_index, int index);
void			check_swap_b(t_so *so);
void			undo_all_operations(t_so *so);
int				get_index_distance(int a, int b, int size);
void			free_stack(t_stack s);
// void			quicksort(t_so *so, float median_ratio, int div);
void			rotate_minimum_on_top(t_so *so);

void			new_quicksort(t_so *so);
void			new_sort_section(t_so *so, int relative_min_index, int relative_max_index);
void			do_operation(t_so *so, t_operation o);

int				real_to_relative_index(t_so *so, int real_index);
int				relative_to_real_index(t_so *so, int relative_index);
void			put_indexed_on_top(t_so so, int index);
void			select_elements_to_remove(t_so *so, int size, int *selected);

void			optimize_rotations(t_list **operations);
int				next_rotation_to_delete(t_list *start, t_operation o);
void			replace_next_rotations(t_list *start, t_operation o, int n);
int				count_unsorted(int *elements, int size);
void			put_in_ordered_b(t_so *so);
void			check_swap(t_so *so);

void			midsort(t_so *so);
t_bool			section_is_sorted(t_so *so, int size, t_bool from_a);
int				set_median(t_stack *s, int size);
#endif
