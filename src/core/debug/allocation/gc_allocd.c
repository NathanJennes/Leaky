/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_allocd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 16:41:41 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:29:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

static void	*alloc(size_t size);

void	*gc_alloc(size_t size)
{
	void	*ptr;

	ptr = alloc(size);
	if (!ptr)
		return (ptr);
	if (!gc_own(ptr))
		return (NULL);
	return (ptr);
}

void	*gct_alloc(size_t size)
{
	void	*ptr;

	ptr = alloc(size);
	if (!ptr)
		return (ptr);
	if (!gct_own(ptr))
		return (NULL);
	return (ptr);
}

void	*gc_ialloc(size_t size)
{
	void	*ptr;

	ptr = alloc(size);
	if (!ptr)
		return (ptr);
	if (!gc_iown(ptr))
		return (NULL);
	return (ptr);
}

static void	*alloc(size_t size)
{
	t_gc	*allocator;
	void	*ptr;

	allocator = gc_get();
	ptr = malloc(size);
	if (!ptr)
	{
		gc_error(gc_error_allocation());
		return (NULL);
	}
	allocator->malloc_calls++;
	return (ptr);
}
