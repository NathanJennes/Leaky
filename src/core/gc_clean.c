/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:34:20 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 19:11:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

void	gc_clean(void)
{
	t_gc	*allocator;
	size_t	i;

	allocator = gc_get();
	if (allocator->capacity == 0)
		return ;
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
