/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_scope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:29:25 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 19:32:12 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static void	free_scope(t_gc *allocator, size_t scope);
static int	is_legal_scope(t_gc *allocator, int mode);

void	gc_scope_start(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (!is_legal_scope(allocator, SCOPE_START))
		return ;
	allocator->current_scope++;
}

void	gc_scope_end(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (!is_legal_scope(allocator, SCOPE_END))
		return ;
	free_scope(allocator, allocator->current_scope);
	allocator->current_scope--;
}

static void	free_scope(t_gc *allocator, size_t scope)
{
	size_t	i;

	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].scope == scope)
		{
			free(allocator->pointers[i].address);
			allocator->pointers[i] = gc_null_ptr();
			if (i < allocator->first_free)
				allocator->first_free = i;
			allocator->ptrs_count--;
		}
		i++;
	}
}

static int	is_legal_scope(t_gc *allocator, int mode)
{
	if (mode == SCOPE_START)
	{
		if (allocator->current_scope == UINT64_MAX)
			return (gc_error(gc_error_scope_overflow()));
		return (1);
	}
	if (allocator->current_scope <= 0)
		return (gc_error(gc_error_scope_underflow()));
	return (1);
}
