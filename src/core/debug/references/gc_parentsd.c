/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_parentsd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:03:28 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 15:57:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <stdint.h>
#endif
#include <stdlib.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

static int	init_parents(t_ptr *ptr);
static int	grow_parents(t_ptr *ptr);
static int	has_parent(t_ptr *ptr, t_ptr *parent);

int	gc_add_parent(t_ptr *ptr, t_ptr *parent)
{
	size_t	i;

	if (has_parent(ptr, parent))
		return (gc_add_error(gc_error_attach_same_parent()));
	if (!ptr->parents && !init_parents(ptr))
		return (LK_FAILURE);
	if (ptr->parent_capacity == ptr->parent_count && !grow_parents(ptr))
		return (LK_FAILURE);
	i = 0;
	while (i < ptr->parent_capacity && ptr->parents[i] != -1)
		i++;
	ptr->parents[i] = gc_get_internal_ptr_index(parent->address);
	ptr->parent_count++;
	return (LK_SUCCESS);
}

int	gc_remove_parent(t_ptr *ptr, t_ptr *parent)
{
	size_t	i;
	int64_t	parent_index;

	if (!ptr->parents || !has_parent(ptr, parent))
		return (gc_add_error(gc_error_detach_not_parent()));
	parent_index = gc_get_internal_ptr_index(parent->address);
	i = 0;
	while (i < ptr->parent_capacity && ptr->parents[i] != parent_index)
		i++;
	if (i < ptr->parent_capacity)
	{
		ptr->parents[i] = -1;
		ptr->parent_count--;
	}
	return (LK_SUCCESS);
}

static int	init_parents(t_ptr *ptr)
{
	ptr->parents = gc_icalloc(5, sizeof (int64_t));
	if (!ptr->parents)
		return (gc_error(gc_error_allocation()));
	gc_memsetl(ptr->parents, -1, 5);
	ptr->parent_capacity = 5;
	return (LK_SUCCESS);
}

static int	grow_parents(t_ptr *ptr)
{
	int64_t	*new;
	size_t	new_parent_capacity;

	if (ptr->parent_capacity >= UINT64_MAX - 100)
		return (gc_error(gc_error_too_much_parents()));
	if (ptr->parent_capacity > 100)
		new_parent_capacity = ptr->parent_capacity + 100;
	else
		new_parent_capacity = ptr->parent_capacity * 2;
	new = gc_icalloc(new_parent_capacity, sizeof (int64_t));
	if (!new)
		return (gc_error(gc_error_allocation()));
	gc_memsetl(new, -1, new_parent_capacity);
	gc_memmove(new, ptr->parents, ptr->parent_capacity * sizeof (int64_t));
	ptr->parent_capacity = new_parent_capacity;
	gc_free(ptr->parents);
	ptr->parents = new;
	return (LK_SUCCESS);
}

static int	has_parent(t_ptr *ptr, t_ptr *parent)
{
	size_t	i;
	int64_t	parent_index;

	if (!ptr->parents)
		return (LK_FALSE);
	parent_index = gc_get_internal_ptr_index(parent->address);
	if (parent_index == -1)
		return (LK_FALSE);
	i = 0;
	while (i < ptr->parent_capacity)
	{
		if (ptr->parents[i] == parent_index)
			return (LK_TRUE);
		i++;
	}
	return (LK_FALSE);
}
