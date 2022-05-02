/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 15:54:56 by njennes           #+#    #+#             */
/*   Updated: 2022/04/18 14:53:54 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "src/core/core.h"
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
	if (!allocator->errors)
		allocator->errors = gc_istrarray_init();
	if (gc_strarray_size(allocator->errors) >= LK_MAX_ERRORS)
		return (gc_error(gc_error_errors_overflow()));
	allocator->errors = gc_istrarray_append(allocator->errors, msg);
	return (1);
}
