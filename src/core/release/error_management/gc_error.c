/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:54:56 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 15:29:21 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "src/core/Release/core.h"
#include "leaky.h"

int	gc_error(const char *msg)
{
	t_gc	*allocator;

	allocator = gc_get();
	allocator->last_error = msg;
	if (allocator->new_ptr)
	{
		free(allocator->new_ptr);
		allocator->new_ptr = NULL;
	}
	if (allocator->callback)
		allocator->callback(allocator->param);
	if (allocator->clean_on_error)
		gc_clean();
	return (LK_FAILURE);
}
