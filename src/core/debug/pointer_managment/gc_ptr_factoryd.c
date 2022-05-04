/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_ptr_factoryd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 12:41:43 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 19:38:48 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"
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
	ptr.internal = LK_TRUE;
	return (ptr);
}
