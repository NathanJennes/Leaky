/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_ptr_factory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:50:07 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:50:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/release/core.h"
#include "leaky.h"

t_ptr	gc_create_generic_ptr(void *address)
{
	t_ptr	ptr;
	t_gc	*allocator;

	allocator = gc_get();
	ptr = gc_null_ptr();
	ptr.address = address;
	ptr.scope = allocator->current_scope;
	return (ptr);
}

t_ptr	gc_create_temporary_ptr(void *address)
{
	t_ptr	ptr;
	t_gc	*allocator;

	allocator = gc_get();
	ptr = gc_null_ptr();
	ptr.address = address;
	ptr.scope = allocator->current_scope;
	ptr.temporary = LK_TRUE;
	return (ptr);
}

t_ptr	gc_create_internal_ptr(void *address)
{
	t_ptr	ptr;

	ptr = gc_null_ptr();
	ptr.address = address;
	return (ptr);
}
