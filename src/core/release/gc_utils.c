/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:39:01 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 14:51:42 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "core.h"
#include "leaky.h"

t_ptr	gc_null_ptr(void)
{
	t_ptr	new;

	gc_memset(&new, 0, sizeof(t_ptr));
	return (new);
}

t_ptr	*gc_get_internal_ptr(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	if (!ptr)
		return (NULL);
	allocator = gc_get();
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].address == ptr)
			return (&allocator->pointers[i]);
		i++;
	}
	return (NULL);
}

int	gc_contains_ptr(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	if (!ptr)
		return (LK_FALSE);
	allocator = gc_get();
	if (allocator->capacity == 0)
		return (LK_FALSE);
	i = 0;
	while (i < allocator->capacity && allocator->pointers[i].address != ptr)
		i++;
	if (i >= allocator->capacity || allocator->pointers[i].address == NULL)
		return (LK_FALSE);
	return (LK_TRUE);
}

int64_t	gc_get_internal_ptr_index(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	if (!ptr)
		return (-1);
	allocator = gc_get();
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].address == ptr)
			return (i);
		i++;
	}
	return (-1);
}

t_ptr	*gc_get_current_parent(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (!gc_has_global_parent())
		return (NULL);
	return (&allocator->pointers[allocator->current_parent]);
}
