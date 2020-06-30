/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alacrois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 00:10:50 by alacrois          #+#    #+#             */
/*   Updated: 2017/09/28 00:13:46 by alacrois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat_free(char *s1, char *s2)
{
	s1 = ft_strcat(s1, s2);
	if (s2 != NULL)
		free(s2);
	return (s1);
}
