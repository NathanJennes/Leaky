/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:41:41 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 19:13:31 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

void	*gc_alloc(size_t size)
{
	t_gc	*allocator;
	void	*ptr;

	allocator = gc_get();
	ptr = malloc(size);
	if (!ptr)
	{
		gc_error("Leaky: memory allocation error!");
		return (NULL);
	}
	allocator->malloc_calls++;
	if (!gc_own(ptr))
		return (NULL);
	return (ptr);
}

void	*gct_alloc(size_t size)
{
	t_gc	*allocator;
	void	*ptr;

	allocator = gc_get();
	ptr = malloc(size);
	if (!ptr)
	{
		gc_error("Leaky: memory allocation error!");
		return (NULL);
	}
	allocator->malloc_calls++;
	if (!gct_own(ptr))
		return (NULL);
	return (ptr);
}
