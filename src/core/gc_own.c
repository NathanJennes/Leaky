/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_own.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:52 by njennes           #+#    #+#             */
/*   Updated: 2022/04/09 16:37:10 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

static t_ptr	create_ptr(void *ptr, char temporary);
static void		insert_ptr(t_gc *gc, t_ptr ptr);

int	gc_own(void *ptr)
{
	t_gc	*allocator;

	if (!ptr)
		return (0);
	allocator = gc(GC_GET, NULL);
	allocator->new_ptr = ptr;
	if (gc_must_grow() && !gc_grow())
		return (0);
	insert_ptr(allocator, create_ptr(ptr, FALSE));
	return (1);
}

int	gc_ownt(void *ptr)
{
	t_gc	*allocator;

	if (!ptr)
		return (0);
	allocator = gc(GC_GET, NULL);
	allocator->new_ptr = ptr;
	if (gc_must_grow() && !gc_grow())
		return (0);
	insert_ptr(allocator, create_ptr(ptr, TRUE));
	return (1);
}

static t_ptr	create_ptr(void *ptr, char temporary)
{
	t_ptr	new_ptr;

	new_ptr.address = ptr;
	new_ptr.temporary = temporary;
	return (new_ptr);
}

static void	insert_ptr(t_gc *gc, t_ptr ptr)
{
	size_t	i;

	i = gc->first_free;
	gc->pointers[i] = ptr;
	while (i < gc->capacity && gc->pointers[i].address)
		i++;
	gc->first_free = i;
	gc->ptrs_count++;
}
