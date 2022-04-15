/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/04/15 11:03:15 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static void	free_childs(t_ptr *ptr);

int	gc_free(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	if (allocator->capacity == 0 || !gc_contains_ptr(ptr) || ptr == NULL)
		return (0);
	i = 0;
	while (i < allocator->capacity && allocator->pointers[i].address != ptr)
		i++;
	if (i >= allocator->capacity || allocator->pointers[i].address == NULL)
		return (0);
	free_childs(&allocator->pointers[i]);
	if (allocator->pointers[i].parent)
		allocator->pointers[i].parent->child_count--;
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
			if (allocator->pointers[i].child_count)
				free_childs(&allocator->pointers[i]);
			free(allocator->pointers[i].address);
			if (allocator->pointers[i].parent)
				allocator->pointers[i].parent->child_count--;
			allocator->pointers[i] = gc_null_ptr();
			if (i < allocator->first_free)
				allocator->first_free = i;
			allocator->ptrs_count--;
		}
		i++;
	}
}

static void	free_childs(t_ptr *ptr)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].parent == ptr)
		{
			if (allocator->pointers[i].child_count)
				free_childs(&allocator->pointers[i]);
			free(allocator->pointers[i].address);
			if (allocator->pointers[i].parent)
				allocator->pointers[i].parent->child_count--;
			allocator->pointers[i] = gc_null_ptr();
			if (i < allocator->first_free)
				allocator->first_free = i;
			allocator->ptrs_count--;
		}
		i++;
	}
}
