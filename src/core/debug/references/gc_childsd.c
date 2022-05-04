/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_childsd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:27:03 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 15:13:31 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <stdint.h>
#endif
#include <stdlib.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

static int	init_childs(t_ptr *ptr);
static int	grow_childs(t_ptr *ptr);
static int	has_child(t_ptr *ptr, t_ptr *child);

int	gc_add_child(t_ptr *ptr, t_ptr *child)
{
	size_t	i;

	if (has_child(ptr, child))
		return (gc_add_error(gc_error_attach_same_parent()));
	if (!ptr->childs && !init_childs(ptr))
		return (LK_FAILURE);
	if (ptr->child_capacity == ptr->child_count && !grow_childs(ptr))
		return (LK_FAILURE);
	i = 0;
	while (i < ptr->child_capacity && ptr->childs[i] != -1)
		i++;
	ptr->childs[i] = gc_get_internal_ptr_index(child->address);
	ptr->child_count++;
	return (LK_SUCCESS);
}

int	gc_remove_child(t_ptr *ptr, t_ptr *child)
{
	size_t	i;
	int64_t	child_index;

	if (!ptr->childs || !has_child(ptr, child))
		return (gc_add_error(gc_error_detach_not_parent()));
	child_index = gc_get_internal_ptr_index(child->address);
	i = 0;
	while (i < ptr->child_capacity && ptr->childs[i] != child_index)
		i++;
	if (i < ptr->child_capacity)
	{
		ptr->childs[i] = -1;
		ptr->child_count--;
	}
	return (LK_SUCCESS);
}

static int	init_childs(t_ptr *ptr)
{
	ptr->childs = gc_icalloc(5, sizeof (int64_t));
	if (!ptr->childs)
		return (gc_error(gc_error_allocation()));
	ptr->child_capacity = 5;
	return (LK_SUCCESS);
}

static int	grow_childs(t_ptr *ptr)
{
	int64_t	*new;
	size_t	new_child_capacity;

	if (ptr->child_capacity >= UINT64_MAX - 100)
		return (gc_error(gc_error_too_much_parents()));
	if (ptr->child_capacity > 100)
		new_child_capacity = ptr->child_capacity + 100;
	else
		new_child_capacity = ptr->child_capacity * 2;
	new = gc_icalloc(new_child_capacity, sizeof (int64_t));
	if (!new)
		return (gc_error(gc_error_allocation()));
	gc_memmove(new, ptr->childs, ptr->child_capacity * sizeof (int64_t));
	ptr->child_capacity = new_child_capacity;
	gc_free(ptr->childs);
	ptr->childs = new;
	return (LK_SUCCESS);
}

static int	has_child(t_ptr *ptr, t_ptr *child)
{
	size_t	i;
	int64_t	child_index;

	if (!ptr->childs)
		return (LK_FALSE);
	child_index = gc_get_internal_ptr_index(child->address);
	if (child_index == -1)
		return (LK_FALSE);
	i = 0;
	while (i < ptr->child_capacity)
	{
		if (ptr->childs[i] == child_index)
			return (LK_TRUE);
		i++;
	}
	return (LK_FALSE);
}
