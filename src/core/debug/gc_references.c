/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_references.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:27:03 by njennes           #+#    #+#             */
/*   Updated: 2022/04/18 15:34:37 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <stdint.h>
#endif
#include <stdlib.h>
#include "core.h"
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
	while (i < ptr->child_capacity && ptr->childs[i])
		i++;
	ptr->childs[i] = child;
	ptr->child_count++;
	return (LK_SUCCESS);
}

int	gc_remove_child(t_ptr *ptr, t_ptr *child)
{
	size_t	i;

	if (!has_child(ptr, child))
		return (gc_add_error(gc_error_detach_not_parent()));
	if (!ptr->childs)
		return (gc_add_error(gc_error_detach_not_parent()));
	i = 0;
	while (i < ptr->child_capacity && ptr->childs[i] != child)
		i++;
	if (i < ptr->child_capacity)
	{
		ptr->childs[i] = NULL;
		ptr->child_count--;
	}
	return (LK_SUCCESS);
}

static int	init_childs(t_ptr *ptr)
{
	ptr->childs = gc_icalloc(5, sizeof (t_ptr *));
	if (!ptr->childs)
		return (gc_error(gc_error_allocation()));
	ptr->child_capacity = 5;
	return (LK_SUCCESS);
}

static int	grow_childs(t_ptr *ptr)
{
	t_ptr	**new;
	size_t	new_parent_capacity;

	if (ptr->child_capacity >= UINT64_MAX - 100)
		return (gc_error(gc_error_too_much_parents()));
	if (ptr->child_capacity > 100)
		new_parent_capacity = ptr->child_capacity + 100;
	else
		new_parent_capacity = ptr->child_capacity * 2;
	new = gc_icalloc(new_parent_capacity, sizeof (t_ptr *));
	if (!new)
		return (gc_error(gc_error_allocation()));
	gc_memmove(new, ptr->childs, ptr->child_capacity * sizeof (t_ptr *));
	ptr->child_capacity = new_parent_capacity;
	gc_free(ptr->childs);
	ptr->childs = new;
	return (LK_SUCCESS);
}

static int	has_child(t_ptr *ptr, t_ptr *child)
{
	size_t	i;

	if (!ptr->childs)
		return (LK_FALSE);
	i = 0;
	while (i < ptr->child_capacity)
	{
		if (ptr->childs[i] == child)
			return (LK_TRUE);
		i++;
	}
	return (LK_FALSE);
}
