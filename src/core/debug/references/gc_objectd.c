/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_objectd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:00:50 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 12:29:27 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"
#include "leaky.h"

void	gc_object_start(void *ptr)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->current_parent = gc_get_internal_ptr(ptr);
	if (!gc_is_valid_ptr_index(allocator->current_parent))
		gc_add_error(gc_error_wrong_object());
}

void	gc_object_end(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->current_parent = -1;
}
