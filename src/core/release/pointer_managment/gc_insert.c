/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:42:25 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:50:30 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/release/core.h"
#include "leaky.h"

int	gc_can_insert(void *ptr)
{
	t_gc	*allocator;

	if (!ptr)
		return (LK_FALSE);
	if (gc_contains_ptr(ptr))
		return (LK_FALSE);
	allocator = gc_get();
	allocator->new_ptr = ptr;
	if (gc_must_grow() && !gc_grow())
		return (LK_FALSE);
	return (LK_TRUE);
}

void	gc_insert_ptr(t_ptr ptr)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	i = allocator->first_free;
	allocator->pointers[i] = ptr;
	while (i < allocator->capacity && allocator->pointers[i].address)
		i++;
	allocator->first_free = i;
	allocator->ptrs_count++;
}
