/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:54:56 by njennes           #+#    #+#             */
/*   Updated: 2022/04/09 16:30:57 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
#include "leaky.h"

int	gc_error(void)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	if (allocator->new_ptr)
		free(allocator->new_ptr);
	if (allocator->callback)
		allocator->callback(allocator->param);
	return (0);
}
