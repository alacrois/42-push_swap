/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 19:31:06 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/26 16:30:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		move_cursor_back_n_lines(int n)
{
	// ft_putstr("\033[7A BASH\n");
	ft_putstr("\033[");
	ft_putnbr(n);
	ft_putstr("A");
}

void	display_test(void)
{
	int		i;
	int		max;

	i = -1;
	max = 400;
	while (++i < max)
	{
		ft_putendl("Lorem ipsum dolor sit amet, consectetur adipiscing elit.");
		ft_putendl("Nulla libero metus, vulputate ac tempor vitae, ullamcorper eu eros.");
		ft_putstr("i = ");
		ft_putnbr(i);
		ft_putchar('\n');
		ft_putendl("Sed porttitor tristique efficitur.");
		ft_putendl("Suspendisse cursus eros id lectus finibus, ut posuere lectus interdum.");
		if (i < max - 1)
			move_cursor_back_n_lines(5);
	}
}
