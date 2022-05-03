/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_own.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:52 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 18:33:59 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/core.h"
#include "leaky.h"

static t_ptr	create_ptr(void *ptr, char temporary, size_t scope);
static void		insert_ptr(t_gc *gc, t_ptr ptr);

int	gc_own(void *ptr)
{
	t_gc	*allocator;

	if (!gc_can_insert(ptr))
		return (LK_FAILURE);
	allocator = gc_get();
	insert_ptr(allocator, create_ptr(ptr, LK_FALSE, allocator->current_scope));
	if (allocator->current_parent)
		gc_attach(ptr, allocator->current_parent->address);
	return (LK_SUCCESS);
}

int	gct_own(void *ptr)
{
	t_gc	*allocator;

	if (!gc_can_insert(ptr))
		return (LK_FAILURE);
	allocator = gc_get();
	insert_ptr(allocator, create_ptr(ptr, LK_TRUE, allocator->current_scope));
	if (allocator->current_parent)
		gc_attach(ptr, allocator->current_parent->address);
	return (LK_SUCCESS);
}

int	gc_iown(void *ptr)
{
	t_gc	*allocator;

	if (!gc_can_insert(ptr))
		return (LK_FAILURE);
	allocator = gc_get();
	insert_ptr(allocator, create_ptr(ptr, LK_FALSE, 0));
	return (LK_SUCCESS);
}

static t_ptr	create_ptr(void *ptr, char temporary, size_t scope)
{
	t_gc	*allocator;
	t_ptr	new_ptr;

	allocator = gc_get();
	new_ptr = gc_null_ptr();
	new_ptr.address = ptr;
	new_ptr.temporary = temporary;
	new_ptr.scope = scope;
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
