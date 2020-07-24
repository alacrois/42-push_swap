/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 15:52:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# include "libft.h"
# define DISPLAY_STACKS false
# define DEBUG false
# define SMALL_SORT_THRESHOLD 20

// # define DISPLAY_INFOS true
// # define ENABLE_PRE_SORT true
// # define SMALL_STACK_THRESHOLD 12
// # define DEBUG_CHECKER false
// # define DEBUG_MIDSORT false
// # define DEBUG_SIMPLE_SORT false
// # define SIMPLE_SORT_THRESHOLD 15
// # define SECTION_SMALL_SORT_THRESHOLD 7
// # define DEBUG_OPTIMIZE false

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

typedef struct	s_to_switch
{
	int			elem;
	int			relative_index;
}				t_to_switch;

typedef struct	s_so
{
	t_stack		*a_stack;
	t_stack		*b_stack;
	t_list		**operations;
	// t_list		**pending_b_operations;
	int			*ordered_numbers;
	int			*numbers_isolation;
	float		average_isolation;
	float		max_isolation;
	t_to_switch	*quicksort_less;
	t_to_switch	*quicksort_more;
}				t_so;

typedef struct	s_options
{
	t_bool		color;
	int			details;
}				t_options;

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
t_bool			is_int(char *s);
void			free_list(t_list **list);
void			get_ordered_numbers_in_array(t_stack *a_stack, \
					int numbers[]);
int				out_of_order(t_so *so);
int				nb_at_index_mod(t_stack *stack, int index);
int				get_element_index(t_stack *stack, int to_find);
t_bool			check_order(t_so *so);
void			delete_next_n_elem(t_list *start, int n);

t_stack			new_stack(int size);
void			add_top(t_stack *s, int n);
void			remove_top(t_stack *s);
void			stack_swap(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_push(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_rotate(t_stack *a_stack, t_stack *b_stack, t_operation o);
void			stack_reverse_rotate(t_stack *a_stack, t_stack *b_stack, \
					t_operation o);
void			inverse_order(t_so *so);
void			rotate_elem_on_top(t_so *so, t_bool a_stack, int elem);


int				number_at_index(t_stack s, int index);
t_bool			stack_is_ordered(t_stack stack);
t_bool			stack_has_duplicates(t_stack a_stack);

void			add_operation(t_list **operations, t_operation o);
t_list			*parse_operations(void);
t_stack			parse_stack(int ac, char **av);

void			display_infos(t_stack a_stack, t_stack b_stack, \
					t_list *operations);
void			display_operations(t_list *operations);
void			operation(t_so *so, t_operation o);
void			execute_all_operations(t_stack *a_stack, \
					t_stack *b_stack, t_list *operations);
void			undo_all_operations(t_so *so);

t_sequence		new_sequence(t_operation s[], int size);
void			free_sequences(t_sequence *so, t_sequence *sr);
void			optimize_operations_sequences(t_list **operations);


void			optimize_last_rotations(t_list **operations, int stack_size);
void			optimize_operations(t_list **operations);
void			optimize_rotations(t_list **operations);

// void			get_unsorted(t_to_sort *elements, int size, t_bool in_order);
void			sort_small(t_so *so);
int				get_max(t_to_sort *elems, int size, t_bool used);
int				get_min(t_to_sort *elems, int size);
void			put_in_ordered_stack(t_so *so, t_bool b, t_section *section);
void			insert_back(t_so *so, t_bool a, int unsorted_count, \
					int *rotations_count);
void			simple_sort(t_so *so, t_section *section, t_bool a);


/* MISSING :
				do_operation
				midsort
*/
#endif
