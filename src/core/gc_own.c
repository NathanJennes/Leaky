/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_own.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:52 by njennes           #+#    #+#             */
/*   Updated: 2022/04/15 10:39:26 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

static t_ptr	create_ptr(
		t_gc *allocator, void *ptr, char temporary, size_t scope);
static void		insert_ptr(t_gc *gc, t_ptr ptr);

int	gc_own(void *ptr)
{
	t_gc	*allocator;

	if (!ptr || gc_contains_ptr(ptr))
		return (0);
	allocator = gc_get();
	allocator->new_ptr = ptr;
	if (gc_must_grow() && !gc_grow())
		return (0);
	insert_ptr(allocator, create_ptr(allocator, ptr,
			LK_FALSE, allocator->current_scope));
	return (1);
}

int	gct_own(void *ptr)
{
	t_gc	*allocator;

	if (!ptr || gc_contains_ptr(ptr))
		return (0);
	allocator = gc_get();
	allocator->new_ptr = ptr;
	if (gc_must_grow() && !gc_grow())
		return (0);
	insert_ptr(allocator, create_ptr(allocator, ptr,
			LK_TRUE, allocator->current_scope));
	return (1);
}

static t_ptr	create_ptr(
		t_gc *allocator, void *ptr,char temporary, size_t scope)
{
	t_ptr	new_ptr;

	new_ptr = gc_null_ptr();
	new_ptr.address = ptr;
	new_ptr.temporary = temporary;
	new_ptr.scope = scope;
	new_ptr.parent = allocator->current_parent;
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
