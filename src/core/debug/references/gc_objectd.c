/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_objectd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 11:00:50 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:29:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"

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
