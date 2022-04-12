/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 14:36:13 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include "basics.h"

char	*gc_strjoin(char *s1, char *s2, int to_free)
{
	size_t	new_len;
	size_t	copied;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	new = gc_calloc(new_len, sizeof (char));
	if (!new)
		return (NULL);
	copied = ft_strlcpy(new, s1, new_len);
	ft_strlcpy(&new[copied], s2, new_len - copied);
	if (to_free == FREE_FIRST || to_free == FREE_BOTH)
		gc_free(s1);
	if (to_free == FREE_SECOND || to_free == FREE_BOTH)
		gc_free(s2);
	return (new);
}

char	*gct_strjoin(char *s1, char *s2, int to_free)
{
	size_t	new_len;
	size_t	copied;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new_len = (ft_strlen(s1) + ft_strlen(s2) + 1);
	new = gct_calloc(new_len, sizeof(char));
	if (!new)
		return (NULL);
	copied = ft_strlcpy(new, s1, new_len);
	ft_strlcpy(&new[copied], s2, new_len - copied);
	if (to_free == FREE_FIRST || to_free == FREE_BOTH)
		gc_free(s1);
	if (to_free == FREE_SECOND || to_free == FREE_BOTH)
		gc_free(s2);
	return (new);
}
