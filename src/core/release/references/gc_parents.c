/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_parents.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:31:44 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 13:32:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <stdint.h>
#endif
#include <stdlib.h>
#include "src/core/release/core.h"
#include "leaky.h"

static int	init_parents(t_ptr *ptr);
static int	grow_parents(t_ptr *ptr);
static int	has_parent(t_ptr *ptr, t_ptr *parent);

int	gc_add_parent(t_ptr *ptr, t_ptr *parent)
{
	size_t	i;

	if (has_parent(ptr, parent))
		return (LK_FAILURE);
	if (!ptr->parents && !init_parents(ptr))
		return (LK_FAILURE);
	if (ptr->parent_capacity == ptr->parent_count && !grow_parents(ptr))
		return (LK_FAILURE);
	i = 0;
	while (i < ptr->parent_capacity && ptr->parents[i])
		i++;
	ptr->parents[i] = parent;
	ptr->parent_count++;
	return (LK_SUCCESS);
}

int	gc_remove_parent(t_ptr *ptr, t_ptr *parent)
{
	size_t	i;

	if (!ptr->parents || !has_parent(ptr, parent))
		return (LK_FAILURE);
	i = 0;
	while (i < ptr->parent_capacity && ptr->parents[i] != parent)
		i++;
	if (i < ptr->parent_capacity)
	{
		ptr->parents[i] = NULL;
		ptr->parent_count--;
	}
	return (LK_SUCCESS);
}

static int	init_parents(t_ptr *ptr)
{
	ptr->parents = gc_icalloc(5, sizeof (t_ptr *));
	if (!ptr->parents)
		return (gc_error(gc_error_allocation()));
	ptr->parent_capacity = 5;
	return (LK_SUCCESS);
}

static int	grow_parents(t_ptr *ptr)
{
	t_ptr	**new;
	size_t	new_parent_capacity;

	if (ptr->parent_capacity >= UINT64_MAX - 100)
		return (gc_error(gc_error_too_much_parents()));
	if (ptr->parent_capacity > 100)
		new_parent_capacity = ptr->parent_capacity + 100;
	else
		new_parent_capacity = ptr->parent_capacity * 2;
	new = gc_icalloc(new_parent_capacity, sizeof (t_ptr *));
	if (!new)
		return (gc_error(gc_error_allocation()));
	gc_memmove(new, ptr->parents, ptr->parent_capacity * sizeof (t_ptr *));
	ptr->parent_capacity = new_parent_capacity;
	gc_free(ptr->parents);
	ptr->parents = new;
	return (LK_SUCCESS);
}

static int	has_parent(t_ptr *ptr, t_ptr *parent)
{
	size_t	i;

	if (!ptr->parents)
		return (LK_FALSE);
	i = 0;
	while (i < ptr->parent_capacity)
	{
		if (ptr->parents[i] == parent)
			return (LK_TRUE);
		i++;
	}
	return (LK_FALSE);
}
