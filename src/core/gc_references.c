/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_references.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 15:27:03 by njennes           #+#    #+#             */
/*   Updated: 2022/04/15 16:15:08 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static int	init_parents(t_ptr *ptr);
static int	grow_parents(t_ptr *ptr);

void	gc_add_parent(t_ptr *ptr, t_ptr *parent)
{
	size_t	i;

	if (!ptr->parents && !init_parents(ptr))
		return ;
	if (ptr->parent_capacity == ptr->parent_count && !grow_parents(ptr))
		return ;
	i = 0;
	while (i < ptr->parent_capacity && ptr->parents[i])
		i++;
	ptr->parents[i] = parent;
}

static int	init_parents(t_ptr *ptr)
{
	ptr->parents = gc_icalloc(5, sizeof (t_ptr *));
	if (!ptr->parents)
		return (0);
	ptr->parent_count = 5;
	return (1);
}

static int	grow_parents(t_ptr *ptr)
{
	t_ptr	**new;
	size_t	new_parent_count;

	if (ptr->parent_count >= UINT64_MAX - 100)
		return (gc_error(gc_error_too_much_parents()));
	if (ptr->parent_count > 100)
		new_parent_count = ptr->parent_count + 100;
	else
		new_parent_count = ptr->parent_count * 2;
	new = gc_icalloc(new_parent_count, sizeof (t_ptr *));
	if (!new)
		return (0);
	gc_memmove(new, ptr->parents, ptr->parent_count * sizeof (t_ptr *));
	ptr->parent_count = new_parent_count;
	return (1);
}
