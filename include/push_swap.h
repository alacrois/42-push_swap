/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/24 10:08:27 by marvin           ###   ########.fr       */
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

int				return_error(void);
t_bool			is_int(char *s);
void			free_list(t_list **list);

t_stack			new_stack(int size);
void			add_top(t_stack *s, int n);
void			remove_top(t_stack *s);
int				number_at_index(t_stack s, int index);
t_bool			stack_is_ordered(t_stack stack);
t_bool			stack_has_duplicates(t_stack a_stack);

void			add_operation(t_list **operations, t_operation o);
t_list			*parse_operations(void);
t_stack			parse_stack(int ac, char **av);

void			display_infos(t_stack a_stack, t_stack b_stack, \
					t_list *operations);
void			display_operations(t_list *operations);

void			execute_all_operations(t_stack *a_stack, \
					t_stack *b_stack, t_list *operations);

/* MISSING :
				out_of_order
				sort_small
				undo_all_operations
				inverse_order
				optimize_operations
				optimize_rotations
				midsort
				nb_at_index_mod
				simple_sort
				get_ordered_numbers_in_array
				rotate_elem_on_top
*/
#endif
