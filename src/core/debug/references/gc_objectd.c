/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_objectd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:00:50 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 15:00:40 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"

//TODO: add a warning for setting a global object that doesn't belong to Leaky
void	gc_object_start(void *ptr)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->current_parent = gc_get_internal_ptr(ptr);
}

void	gc_object_end(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->current_parent = -1;
}
