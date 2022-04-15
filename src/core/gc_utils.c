/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:39:01 by njennes           #+#    #+#             */
/*   Updated: 2022/04/15 11:06:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return (0);
	allocator = gc_get();
	if (allocator->capacity == 0)
		return (0);
	i = 0;
	while (i < allocator->capacity && allocator->pointers[i].address != ptr)
		i++;
	if (i >= allocator->capacity || allocator->pointers[i].address == NULL)
		return (0);
	return (1);
}
