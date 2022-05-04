/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_ownd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:43:52 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:49:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"
#include "leaky.h"

int				gc_can_insert(void *ptr);
void			gc_insert_ptr(t_ptr ptr);

int	gc_own(void *ptr)
{
	t_gc	*allocator;

	if (!gc_can_insert(ptr))
		return (LK_FAILURE);
	allocator = gc_get();
	gc_insert_ptr(gc_create_generic_ptr(ptr));
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
	gc_insert_ptr(gc_create_temporary_ptr(ptr));
	if (allocator->current_parent)
		gc_attach(ptr, allocator->current_parent->address);
	return (LK_SUCCESS);
}

int	gc_iown(void *ptr)
{
	if (!gc_can_insert(ptr))
		return (LK_FAILURE);
	gc_insert_ptr(gc_create_internal_ptr(ptr));
	return (LK_SUCCESS);
}
