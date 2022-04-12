/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:54:56 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 15:12:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

int	gc_error(const char *msg)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	allocator->error = msg;
	if (allocator->new_ptr)
	{
		free(allocator->new_ptr);
		allocator->new_ptr = NULL;
	}
	if (allocator->callback)
		allocator->callback(allocator->param);
	return (0);
}

int	gc_failed(void)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	if (allocator->error)
		return (1);
	return (0);
}

const char	*gc_get_error(void)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	return (allocator->error);
}
