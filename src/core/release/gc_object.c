/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:00:50 by njennes           #+#    #+#             */
/*   Updated: 2022/04/15 11:08:05 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

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
	allocator->current_parent = NULL;
}
