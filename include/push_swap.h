/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/08/25 22:44:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"
# define DISPLAY_STACKS true
# define DISPLAY_COLOR true
# define DISPLAY_STACK_MAX_SIZE 25
# define SMALL_SORT_THRESHOLD 20
# define DISPLAY_SLEEP_INTERVAL_NORMAL 0.66
# define DISPLAY_SLEEP_INTERVAL_FAST 0.25

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

typedef struct	s_options
{
	t_bool		color;
	t_bool		details;
	t_bool		display_stacks;
	t_bool		fast;
	int			input;
}				t_options;

typedef struct	s_so
{
	t_stack		*a_stack;
	t_stack		*b_stack;
	t_list		**operations;
	int			*ordered_numbers;
	t_options	options;
	int			printed_lines;
	t_bool		checker;
}				t_so;

typedef struct	s_to_sort
{
	int			value;
	int			ooo;
	t_bool		used;
}				t_to_sort;

typedef struct	s_section
{
	int			first_elem;
	int			last_elem;
	int			size;
}				t_section;

typedef struct	s_sequence
{
	t_operation	*o;
	int			size;
}				t_sequence;

typedef struct	s_simple_sort
{
	int			unsorted_count;
	int			rotations;
	t_section	unsorted;
	t_bool		a;
	t_to_sort	*elems;
}				t_simple_sort;

int				return_error(void);
void			exit_error(void);
t_bool			is_int(char *s);
void			free_list(t_list **list);
void			get_ordered_numbers_in_array(t_stack *a_stack, \
					int numbers[]);
int				out_of_order(t_so *so);
int				nb_at_index_mod(t_stack *stack, int index);
int				get_element_index(t_stack *stack, int to_find);
t_bool			check_order(t_so *so);
void			delete_next_n_elem(t_list *start, int n);
void			set_unsorted(t_to_sort *elements, int size, t_bool in_order);
int				remove_first_most_unsorted(t_to_sort *elements, int size);
int				count_unsorted(int *elements, int size, t_bool in_order);

void			move_cursor_back_n_lines(int n);
void			display_infos(t_so *so, int number_of_operations, \
					t_operation o, t_bool before);
void			display_stacks(t_so *so, t_operation o, \
					t_bool before);

void			display_operation(t_operation o, int fd);
void			display_operations(t_list *operations, int fd);

t_stack			new_stack(int size);
void			free_stack(t_stack s);
void			add_top(t_stack *s, int n);
void			remove_top(t_stack *s);
void			stack_swap(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_push(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_rotate(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_reverse_rotate(t_stack *a_stack, t_stack *b_stack, \
					t_operation o);
void			inverse_order(t_so *so);
void			rotate_elem_on_top(t_so *so, t_bool a_stack, int elem);
int				stack_minimum(t_stack *s);
int				set_median(t_stack *s, int size);
int				number_at_index(t_stack s, int index);
t_bool			stack_is_ordered(t_stack stack);
t_bool			stack_has_duplicates(t_stack a_stack);

void			add_operation(t_list **operations, t_operation o);
t_list			*parse_operations(int fd);
t_stack			parse_stack(int ac, char **av, int options);
int				parse_options(int ac, char **av, t_so *so);

void			operation(t_so *so, t_operation o);
void			execute_all_operations(t_so *so);
void			undo_all_operations(t_so *so);

t_sequence		new_sequence(int size, t_operation o1, \
					t_operation o2, t_operation o3);
void			free_sequences(t_sequence *so, t_sequence *sr);
void			optimize_operations_sequences(t_list **operations);
void			optimize_last_rotations(t_list **operations, int stack_size);
void			optimize_operations(t_list **operations);
void			optimize_rotations(t_list **operations);

t_bool			section_sorted(t_so *so, t_section section, t_bool is_a);
void			sort_small(t_so *so);
int				get_max(t_to_sort *elems, int size, t_bool used);
int				get_min(t_to_sort *elems, int size);
void			put_in_ordered_stack(t_so *so, t_bool b, t_section *section);
void			insert_back(t_so *so, t_bool a, int unsorted_count, \
					int *rotations_count);
void			simple_sort(t_so *so, t_section *section, t_bool a);
void			midsort(t_so *so);
t_bool			b_in_a(t_so *so, t_section *section);
t_bool			check_simple_sort(t_so *so, t_section *section, t_bool a);
int				sort_by_median(t_so *so, t_bool a_to_b, int size, int median);
void			indexed_on_top(t_so *so, int index, t_bool a);
void			recursive_sort_section(t_so *so, t_section section);

t_list			*generate_operations(t_stack *a_stack);

#endif
