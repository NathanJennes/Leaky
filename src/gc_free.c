/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/04/09 14:27:36 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "leaky.h"
#include <stdlib.h>

void	gc_free(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc(GC_GET, NULL);
	if (allocator->capacity == 0)
		return ;
	i = 0;
	while (i < allocator->capacity && allocator->pointers[i] != ptr)
		i++;
	if (i >= allocator->capacity || allocator->pointers[i] == NULL)
		return ;
	else
		allocator->pointers[i] = NULL;
	if (i < allocator->first_free)
		allocator->first_free = i;
	allocator->ptrs_count--;
	free(ptr);
}

void	gc_destroy(void **ptr)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	if (!ptr)
		return ;
	gc_free(*ptr);
	*ptr = NULL;
}

void	gc_clean()
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc(GC_GET, NULL);
	if (allocator->capacity == 0)
		return ;
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i])
			free(allocator->pointers[i]);
		i++;
	}
	free(allocator->pointers);
	allocator->capacity = 0;
}
