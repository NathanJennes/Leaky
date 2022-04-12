/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:39:01 by njennes           #+#    #+#             */
/*   Updated: 2022/04/11 16:27:25 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

t_ptr	gc_null_ptr(void)
{
	t_ptr	new;

	ft_memset(&new, 0, sizeof (t_ptr));
	return (new);
}

int	gc_contains_ptr(void *ptr)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc(GC_GET, NULL);
	if (allocator->capacity == 0)
		return (0);
	i = 0;
	while (i < allocator->capacity && allocator->pointers[i].address != ptr)
		i++;
	if (i >= allocator->capacity || allocator->pointers[i].address == NULL)
		return (0);
	return (1);
}
