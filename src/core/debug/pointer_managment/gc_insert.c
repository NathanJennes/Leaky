/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_insert.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 18:38:40 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 18:48:28 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/core.h"
#include "leaky.h"

int	gc_can_insert(void *ptr)
{
	t_gc	*allocator;

	if (!ptr)
		return (LK_FALSE);
	if (gc_contains_ptr(ptr))
		return (gc_add_error(gc_error_own_twice()));
	allocator = gc_get();
	allocator->new_ptr = ptr;
	if (gc_must_grow() && !gc_grow())
		return (LK_FALSE);
	return (LK_TRUE);
}
