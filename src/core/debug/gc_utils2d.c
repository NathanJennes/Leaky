/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:54:10 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 17:39:34 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cored.h"
#include "leaky.h"

int	gc_has_global_parent(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->current_parent == -1)
		return (LK_FALSE);
	return (LK_TRUE);
}

t_ptr	*gc_ptr(int64_t index)
{
	t_gc	*allocator;

	if (index == -1)
		return (NULL);
	allocator = gc_get();
	return (&allocator->pointers[index]);
}
