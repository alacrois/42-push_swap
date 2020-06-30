/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/06/30 20:34:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "stdlib.h"
# include "stdio.h"
# include "libft.h"

typedef	enum	e_operation
{
	SA,
	SB,
	SS
}				t_operation;

t_list		*parse_operations();
t_list		*parse_stack(int ac, char **av);
void		free_list(t_list **list);
void		execute_operations(t_list **a_stack, \
				t_list **b_stack, t_list *operations);
int			is_ordered(t_list *stack);
void		display_infos(t_list	*operations, t_list *a_stack);



#endif
