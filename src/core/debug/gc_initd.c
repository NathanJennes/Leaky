/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_initd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:48:09 by                   #+#    #+#             */
/*   Updated: 2022/05/04 18:09:50 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cored.h"
#include "leaky.h"

int	gc_init(t_gc *allocator, int (*callback)(void *), void *param)
{
	if (!allocator)
		return (LK_FAILURE);
	gc_memset(allocator, 0, sizeof(t_gc));
	allocator->capacity = 100;
	allocator->current_parent = -1;
	allocator->pointers = ft_calloc(allocator->capacity, sizeof(t_ptr));
	if (!allocator->pointers)
		return (gc_error(gc_error_allocation()));
	allocator->malloc_calls = 1;
	allocator->callback = callback;
	allocator->param = param;
	return (LK_SUCCESS);
}

size_t	gc_getfootprint(void)
{
	int		footprint;
	t_gc	*allocator;
	int64_t	i;

	allocator = gc_get();
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

size_t	gc_get_malloc_calls(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	return (allocator->malloc_calls);
}
