/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:27:03 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 14:37:09 by njennes          ###   ########.fr       */
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
	if (!new)
		return (NULL);
	ft_strlcpy(new, &s[start], ft_min(ft_strlen(s) - start, len) + 1);
	return (new);
}

char	*gct_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (gct_strdup(""));
	new = gct_calloc(ft_min(ft_strlen(s) - start, len) + 1, sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, &s[start], ft_min(ft_strlen(s) - start, len) + 1);
	return (new);
}
