/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:05:46 by                   #+#    #+#             */
/*   Updated: 2022/04/09 14:23:58 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "leaky.h"

static int	gc_grow(t_gc *gc)
{
	void	**new_ptr;

	if (!gc)
		return (0);
	new_ptr = ft_calloc(gc->capacity * 2, sizeof (void *));
	if (!new_ptr)
	{
		if (gc->callback)
			gc->callback(gc->param);
		return (0);
	}
	ft_memmove(new_ptr, gc->pointers, gc->capacity * sizeof(void *));
	free(gc->pointers);
	gc->pointers = new_ptr;
	gc->capacity *= 2;
	return (1);
}

static void	insert_ptr(t_gc *gc, void *ptr)
{
	size_t	i;

	if (!gc)
		return ;
	i = gc->first_free;
	gc->pointers[i] = ptr;
	while (i < gc->capacity && gc->pointers[i])
		i++;
	gc->first_free = i;
	gc->ptrs_count++;
}

void	*gc_calloc(size_t count, size_t size)
{
	t_gc	*allocator;
	void	*ptr;

	allocator = gc(GC_GET, NULL);
	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		if (allocator->callback)
			allocator->callback(allocator->param);
		return (NULL);
	}
	if (allocator->ptrs_count >= allocator->capacity)
	{
		if (!gc_grow(allocator))
		{
			free(ptr);
			if (allocator->callback)
				allocator->callback(allocator->param);
			return (NULL);
		}
	}
	insert_ptr(allocator, ptr);
	return (ptr);
}
