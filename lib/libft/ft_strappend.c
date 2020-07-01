/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/22 16:31:41 by alacrois          #+#    #+#             */
/*   Updated: 2020/07/01 21:26:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_strappend(char **original, char *new)
{
	char	*new_string;
	size_t	len;

	len = 0;
	if (*original != NULL)
		len += ft_strlen(*original);
	if (new != NULL)
		len += ft_strlen(new);
	new_string = ft_strnew(len + 1);
	new_string = ft_strcat(new_string, *original);
	new_string = ft_strcat(new_string, new);
	free(*original);
	*original = ft_strdup(new_string);
	free(new_string);
}
