/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:48:09 by                   #+#    #+#             */
/*   Updated: 2022/04/09 17:02:49 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int	gc_init(t_gc *allocator, int (*callback)(void *), void *param)
{
	if (!allocator)
		return (0);
	ft_memset(allocator, 0, sizeof(t_gc));
	allocator->pointers = ft_calloc(allocator->capacity, sizeof(t_ptr));
	if (!allocator->pointers)
		return (gc_error());
	allocator->malloc_calls = 1;
	allocator->callback = callback;
	allocator->param = param;
	allocator->capacity = 10;
	return (1);
}

size_t	gc_getfootprint()
{
	int		footprint;
	size_t	i;
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	i = 0;
	footprint = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].address)
			footprint++;
		i++;
	}
	return (footprint);
}

size_t	gc_get_malloc_calls()
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	return (allocator->malloc_calls);
}
