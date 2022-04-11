/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_scope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:29:25 by njennes           #+#    #+#             */
/*   Updated: 2022/04/11 16:44:14 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static void	free_scope(t_gc *allocator, size_t scope);

void	gc_scope_start(void)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	allocator->current_scope++;
}

void	gc_scope_end(void)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	free_scope(allocator, allocator->current_scope);
	allocator->current_scope--;
}

static void	free_scope(t_gc *allocator, size_t scope)
{
	size_t	i;

	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].scope == scope)
		{
			free(allocator->pointers[i].address);
			allocator->pointers[i] = gc_null_ptr();
			if (i < allocator->first_free)
				allocator->first_free = i;
			allocator->ptrs_count--;
		}
		i++;
	}
}
