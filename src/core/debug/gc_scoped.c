/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_scoped.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:29:25 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 13:35:44 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __linux__
# include <stdint.h>
#endif

#include <stdlib.h>
#include "cored.h"
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
			gc_free(allocator->pointers[i].address);
		i++;
	}
}

static int	is_legal_scope(t_gc *allocator, int mode)
{
	if (mode == SCOPE_START)
	{
		if (allocator->current_scope == UINT64_MAX)
			return (gc_error(gc_error_scope_overflow()));
		return (LK_TRUE);
	}
	if (allocator->current_scope <= 0)
		return (gc_error(gc_error_scope_underflow()));
	return (LK_TRUE);
}
