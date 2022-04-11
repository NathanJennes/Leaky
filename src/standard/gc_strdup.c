/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:25:27 by njennes           #+#    #+#             */
/*   Updated: 2021/11/04 17:56:20 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

char	*gc_strdup(const char *s1)
{
	char	*newstr;

	if (!s1)
		return (NULL);
	newstr = gc_calloc(ft_strlen(s1) + 1, sizeof(char));
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	return (newstr);
}

char	*gc_strdupt(const char *s1)
{
	char	*newstr;

	if (!s1)
		return (NULL);
	newstr = gc_calloct(ft_strlen(s1) + 1, sizeof(char));
	ft_strlcpy(newstr, s1, ft_strlen(s1) + 1);
	return (newstr);
}
