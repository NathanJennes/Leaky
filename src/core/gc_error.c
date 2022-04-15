/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:54:56 by njennes           #+#    #+#             */
/*   Updated: 2022/04/13 15:57:39 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "core.h"
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
	if (allocator->clean_on_error)
		gc_clean();
	if (allocator->callback)
		allocator->callback(allocator->param);
	if (msg != gc_error_errors_overflow())
		gc_add_error(gc_error_no_exit_callback());
	return (0);
}

int	gc_add_error(const char *msg)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->ignore_warnings)
		return (1);
	if (gc_strarray_size(allocator->errors) >= LK_MAX_ERRORS)
		return (gc_error(gc_error_errors_overflow()));
	allocator->errors = gc_strarray_append(allocator->errors, msg);
	return (1);
}
