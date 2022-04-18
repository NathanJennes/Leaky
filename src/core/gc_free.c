/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:13:47 by                   #+#    #+#             */
/*   Updated: 2022/04/18 13:39:11 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static void	free_childs(t_ptr *ptr);
static void	free_ptr(t_ptr *ptr);

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
			free_childs(&allocator->pointers[i]);
			free_ptr(&allocator->pointers[i]);
		}
		i++;
	}
}

static void	free_childs(t_ptr *ptr)
{
	t_gc	*allocator;
	size_t	i;

	if (!ptr->childs)
		return ;
	allocator = gc_get();
	i = 0;
	while (i < ptr->child_capacity)
	{
		if (ptr->childs[i])
		{
			free_childs(ptr->childs[i]);
			free_ptr(ptr->childs[i]);
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
	if (ptr->childs)
		gc_free(ptr->childs);
	*ptr = gc_null_ptr();
}
