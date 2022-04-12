/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/04/09 20:36:26 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"
#include <stdlib.h>

int	gc_free(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc(GC_GET, NULL);
	if (allocator->capacity == 0)
		return (0);
	i = 0;
	while (i < allocator->capacity && allocator->pointers[i].address != ptr)
		i++;
	if (i >= allocator->capacity || allocator->pointers[i].address == NULL)
		return (0);
	else
		allocator->pointers[i].address = NULL;
	if (i < allocator->first_free)
		allocator->first_free = i;
	allocator->ptrs_count--;
	free(ptr);
	return (1);
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
		if (allocator->pointers[i].address)
			free(allocator->pointers[i].address);
		i++;
	}
	free(allocator->pointers);
	allocator->capacity = 0;
}
