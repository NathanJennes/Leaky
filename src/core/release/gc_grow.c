/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_grow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:42:44 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 15:37:36 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static size_t	get_new_size(t_gc *allocator);

int	gc_grow(void)
{
	t_gc	*allocator;
	t_ptr	*new_ptr;
	size_t	new_size;

	allocator = gc_get();
	new_size = get_new_size(allocator);
	new_ptr = ft_calloc(new_size, sizeof (t_ptr));
	if (!new_ptr)
	{
		gc_error(gc_error_allocation());
		return (LK_FAILURE);
	}
	gc_memmove(new_ptr, allocator->pointers,
		allocator->capacity * sizeof(t_ptr));
	free(allocator->pointers);
	allocator->pointers = new_ptr;
	allocator->capacity = new_size;
	allocator->malloc_calls++;
	return (LK_SUCCESS);
}

int	gc_must_grow(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->ptrs_count >= allocator->capacity)
		return (LK_SUCCESS);
	return (LK_FAILURE);
}

static size_t	get_new_size(t_gc *allocator)
{
	if (allocator->capacity >= 1000)
		return (allocator->capacity + 1000);
	return (allocator->capacity * 2);
}
