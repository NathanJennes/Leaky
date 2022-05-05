/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_parentsd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:03:28 by njennes           #+#    #+#             */
/*   Updated: 2022/05/05 12:58:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <stdint.h>
#endif
#include <stdlib.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

static int	init_parents(int64_t ptr);
static int	grow_parents(int64_t ptr);
static int	has_parent(int64_t ptr, int64_t parent);

int	gc_add_parent(int64_t ptr, int64_t parent)
{
	size_t	i;

	if (has_parent(ptr, parent))
		return (gc_add_error(gc_error_attach_same_parent()));
	if (!gc_ptr(ptr)->parents && !init_parents(ptr))
		return (LK_FAILURE);
	if (gc_ptr(ptr)->parent_capacity == gc_ptr(ptr)->parent_count
		&& !grow_parents(ptr))
		return (LK_FAILURE);
	i = 0;
	while (i < gc_ptr(ptr)->parent_capacity && gc_ptr(ptr)->parents[i] != -1)
		i++;
	gc_ptr(ptr)->parents[i] = parent;
	gc_ptr(ptr)->parent_count++;
	return (LK_SUCCESS);
}

int	gc_remove_parent(int64_t ptr, int64_t parent)
{
	size_t	i;

	if (!gc_ptr(ptr)->parents || !has_parent(ptr, parent))
		return (gc_add_error(gc_error_detach_not_parent()));
	i = 0;
	while (i < gc_ptr(ptr)->parent_capacity
		&& gc_ptr(ptr)->parents[i] != parent)
		i++;
	if (i < gc_ptr(ptr)->parent_capacity)
	{
		gc_ptr(ptr)->parents[i] = -1;
		gc_ptr(ptr)->parent_count--;
	}
	return (LK_SUCCESS);
}

static int	init_parents(int64_t ptr)
{
	t_ptr	*internal_ptr;

	internal_ptr = gc_ptr(ptr);
	internal_ptr->parents = gc_icalloc(5, sizeof (int64_t));
	if (!gc_ptr(ptr)->parents)
		return (gc_error(gc_error_allocation()));
	gc_memsetl(gc_ptr(ptr)->parents, -1, 5);
	gc_ptr(ptr)->parent_capacity = 5;
	return (LK_SUCCESS);
}

static int	grow_parents(int64_t ptr)
{
	int64_t	*new;
	size_t	new_parent_capacity;

	if (gc_ptr(ptr)->parent_capacity >= UINT64_MAX - 100)
		return (gc_error(gc_error_too_much_parents()));
	if (gc_ptr(ptr)->parent_capacity > 100)
		new_parent_capacity = gc_ptr(ptr)->parent_capacity + 100;
	else
		new_parent_capacity = gc_ptr(ptr)->parent_capacity * 2;
	new = gc_icalloc(new_parent_capacity, sizeof (int64_t));
	if (!new)
		return (gc_error(gc_error_allocation()));
	gc_memsetl(new, -1, new_parent_capacity);
	gc_memmove(new, gc_ptr(ptr)->parents,
		gc_ptr(ptr)->parent_capacity * sizeof (int64_t));
	gc_ptr(ptr)->parent_capacity = new_parent_capacity;
	gc_free(gc_ptr(ptr)->parents);
	gc_ptr(ptr)->parents = new;
	return (LK_SUCCESS);
}

static int	has_parent(int64_t ptr, int64_t parent)
{
	size_t	i;

	if (!gc_ptr(ptr)->parents)
		return (LK_FALSE);
	i = 0;
	while (i < gc_ptr(ptr)->parent_capacity)
	{
		if (gc_ptr(ptr)->parents[i] == parent)
			return (LK_TRUE);
		i++;
	}
	return (LK_FALSE);
}
