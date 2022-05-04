/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_freed.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/05/04 18:18:26 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

static void	free_childs(int64_t ptr);
static void	free_ptr(int64_t ptr);
static void	update_parents(int64_t ptr);

int	gc_free(void *ptr)
{
	t_gc	*allocator;
	int64_t	internal_ptr;

	allocator = gc_get();
	if (allocator->capacity == 0)
		return (LK_FAILURE);
	internal_ptr = gc_get_internal_ptr(ptr);
	if (!gc_is_valid_ptr_index(internal_ptr))
		return (LK_FAILURE);
	free_childs(internal_ptr);
	update_parents(internal_ptr);
	free_ptr(internal_ptr);
	return (LK_SUCCESS);
}

void	gct_free(void)
{
	t_gc	*allocator;
	int64_t	i;

	allocator = gc_get();
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].temporary)
		{
			free_childs(i);
			update_parents(i);
			free_ptr(i);
		}
		i++;
	}
}

static void	free_childs(int64_t ptr)
{
	t_gc	*allocator;
	size_t	i;

	if (!gc_ptr(ptr)->childs)
		return ;
	allocator = gc_get();
	i = 0;
	while (i < gc_ptr(ptr)->child_capacity)
	{
		if (gc_ptr(ptr)->childs[i] != -1)
			gc_free(allocator->pointers[gc_ptr(ptr)->childs[i]].address);
		i++;
	}
}

static void	update_parents(int64_t ptr)
{
	t_gc	*allocator;
	size_t	i;

	if (!gc_ptr(ptr)->parents)
		return ;
	allocator = gc_get();
	i = 0;
	while (i < gc_ptr(ptr)->parent_capacity)
	{
		if (gc_ptr(ptr)->parents[i] != -1)
			gc_remove_child(gc_ptr(ptr)->parents[i], ptr);
		i++;
	}
}

static void	free_ptr(int64_t ptr)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (ptr < allocator->first_free)
		allocator->first_free = ptr;
	allocator->ptrs_count--;
	free(gc_ptr(ptr)->address);
	if (gc_ptr(ptr)->childs)
		gc_free(gc_ptr(ptr)->childs);
	if (gc_ptr(ptr)->parents)
		gc_free(gc_ptr(ptr)->parents);
	*gc_ptr(ptr) = gc_null_ptr();
}
