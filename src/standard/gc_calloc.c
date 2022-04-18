/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:05:46 by                   #+#    #+#             */
/*   Updated: 2022/04/11 14:44:45 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "leaky.h"

void	*gc_ialloc(size_t size);

void	*gc_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = gc_alloc(count * size);
	if (!ptr)
		return (NULL);
	gc_memset(ptr, 0, count * size);
	return (ptr);
}

void	*gct_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = gct_alloc(count * size);
	if (!ptr)
		return (NULL);
	gc_memset(ptr, 0, count * size);
	return (ptr);
}


void	*gc_icalloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = gc_ialloc(count * size);
	if (!ptr)
		return (NULL);
	gc_memset(ptr, 0, count * size);
	return (ptr);
}
