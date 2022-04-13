/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:34:20 by njennes           #+#    #+#             */
/*   Updated: 2022/04/13 16:14:24 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

static void	check_for_warnings(t_gc *allocator);

void	gc_clean(void)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	check_for_warnings(allocator);
	i = 0;
	while (i < allocator->capacity)
	{
		if (allocator->pointers[i].address)
			free(allocator->pointers[i].address);
		i++;
	}
	free(allocator->pointers);
	gc_memset(allocator, 0, sizeof (t_gc));
}

static void	check_for_warnings(t_gc *allocator)
{
	if (allocator->ptrs_count == 0)
		gc_add_error(gc_error_clean_empty());
	if (allocator->current_scope)
		gc_add_error(gc_error_clean_scope_left());
}
