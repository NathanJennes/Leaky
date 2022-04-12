/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:52:10 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 14:35:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "leaky.h"

static int	ft_count_words(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			words++;
			while (*s && *s != c)
				s++;
		}
	}
	return (words);
}

static void	ft_chop(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			*str = 0;
		str++;
	}
}

static int	free_words(char *sdup, char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		gc_free(tab[i]);
		i++;
	}
	gc_free(tab);
	gc_free(sdup);
	return (0);
}

static int	ft_get_words(char *str, int count, char **tab)
{
	int	i;

	i = 0;
	while (i < count)
	{
		while (!*str)
			str++;
		tab[i] = gc_strdup(str);
		if (!tab[i])
			break ;
		str += ft_strlen(str);
		i++;
	}
	if (i < count)
		return (free_words(str, tab));
	return (1);
}

char	**gc_split(char const *s, char c)
{
	char	*sdup;
	char	**tab;

	if (!s)
		return (NULL);
	tab = gc_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	sdup = gc_strdup(s);
	if (!sdup)
		return (NULL);
	ft_chop(sdup, c);
	if (!ft_get_words(sdup, ft_count_words(s, c), tab))
		return (NULL);
	gc_free(sdup);
	return (tab);
}
