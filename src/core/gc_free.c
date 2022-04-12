/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/04/12 19:14:35 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

int	gc_free(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	if (allocator->capacity == 0)
		return (0);
	i = 0;
	while (i < allocator->capacity && allocator->pointers[i].address != ptr)
		i++;
	if (i >= allocator->capacity || allocator->pointers[i].address == NULL)
		return (0);
	else
		allocator->pointers[i] = gc_null_ptr();
	if (i < allocator->first_free)
		allocator->first_free = i;
	allocator->ptrs_count--;
	free(ptr);
	return (1);
}

void	gct_free(void)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].temporary)
		{
			free(allocator->pointers[i].address);
			allocator->pointers[i] = gc_null_ptr();
		}
		i++;
	}
}
