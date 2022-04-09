/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:52:10 by njennes           #+#    #+#             */
/*   Updated: 2022/04/08 19:19:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static int	ft_get_words(char *str, int count, char **tab)
{
	int	i;

	i = 0;
	while (i < count)
	{
		while (!*str)
			str++;
		tab[i] = gc_strdup(str);
		str += ft_strlen(str);
		i++;
	}
	tab[i] = NULL;
	return (1);
}

char	**gc_split(char const *s, char c)
{
	char	*sdup;
	char	**tab;

	if (!s)
		return (NULL);
	tab = gc_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	sdup = gc_strdup(s);
	ft_chop(sdup, c);
	ft_get_words(sdup, ft_count_words(s, c), tab);
	gc_free(sdup);
	return (tab);
}
