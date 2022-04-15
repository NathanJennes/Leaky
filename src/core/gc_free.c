/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/04/15 16:13:32 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static void	free_childs(t_ptr *ptr);
static void	free_ptr(t_ptr *ptr);
static void	update_parents(t_ptr *ptr);

int	gc_free(void *ptr)
{
	t_gc	*allocator;
	t_ptr	*internal_ptr;

	allocator = gc_get();
	if (allocator->capacity == 0)
		return (0);
	internal_ptr = gc_get_internal_ptr(ptr);
	if (!internal_ptr)
		return (0);
	free_childs(internal_ptr);
	update_parents(internal_ptr);
	free_ptr(internal_ptr);
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

static void	free_ptr(t_ptr *ptr)
{
	t_gc	*allocator;
	size_t	ptr_index;

	allocator = gc_get();
	ptr_index = gc_get_internal_ptr_index(ptr);
	if (ptr_index < allocator->first_free)
		allocator->first_free = ptr_index;
	allocator->ptrs_count--;
	free(ptr->address);
	if (ptr->parents)
		gc_free(ptr->parents);
	*ptr = gc_null_ptr();
}

static void	update_parents(t_ptr *ptr)
{
	size_t	i;

	i = 0;
	while (i < ptr->parent_count)
	{

	}
}
