/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strarray_from.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:26:44 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 15:23:56 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

static char	**free_array(char **array, size_t size);

char	**gc_strarray_from(char **other, size_t size)
{
	size_t	i;
	char	**array;

	if (!other)
		return (gc_strarray_init());
	array = gc_calloc(size + 1, sizeof (char *));
	if (!array)
		return (NULL);
	gc_memmove(array, other, size * sizeof(char *));
	i = 0;
	while (i < size)
	{
		array[i] = gc_strdup(other[i]);
		if (!array[i])
			return (free_array(array, size));
		i++;
	}
	return (array);
}

char	**gct_strarray_from(char **other, size_t size)
{
	size_t	i;
	char	**array;

	if (!other)
		return (gct_strarray_init());
	array = gct_calloc(size + 1, sizeof(char *));
	if (!array)
		return (NULL);
	gc_memmove(array, other, size * sizeof(char *));
	i = 0;
	while (i < size)
	{
		array[i] = gct_strdup(other[i]);
		if (!array[i])
			return (free_array(array, size));
		i++;
	}
	return (array);
}

static char	**free_array(char **array, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && array[i])
	{
		gc_free(array[i]);
		i++;
	}
	gc_free(array);
	return (NULL);
}
