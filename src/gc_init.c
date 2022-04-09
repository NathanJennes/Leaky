/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:48:09 by                   #+#    #+#             */
/*   Updated: 2022/04/08 19:17:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"

void	gc_init(t_gc *gc, int (*callback)(void *), void *param)
{
	if (!gc)
		return ;
	gc->callback = callback;
	gc->param = param;
	gc->capacity = 10;
	gc->ptrs_count = 0;
	gc->first_free = 0;
	gc->pointers = ft_calloc(gc->capacity, sizeof(void *));
	if (!gc->pointers)
		gc->capacity = 0;
}

int	gc_getfootprint()
{
	int		footprint;
	size_t	i;
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	i = 0;
	footprint = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i])
			footprint++;
		i++;
	}
	return (footprint);
}
