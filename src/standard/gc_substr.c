/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:27:03 by njennes           #+#    #+#             */
/*   Updated: 2021/11/05 17:29:38 by njennes          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

static int	ft_min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (gc_strdup(""));
	new = gc_calloc(ft_min(ft_strlen(s) - start, len) + 1, sizeof(char));
	ft_strlcpy(new, &s[start], ft_min(ft_strlen(s) - start, len) + 1);
	return (new);
}

char	*gc_substrt(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (gc_strdupt(""));
	new = gc_calloct(ft_min(ft_strlen(s) - start, len) + 1, sizeof(char));
	ft_strlcpy(new, &s[start], ft_min(ft_strlen(s) - start, len) + 1);
	return (new);
}
