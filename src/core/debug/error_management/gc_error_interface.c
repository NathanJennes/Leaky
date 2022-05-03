/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:43:34 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 14:39:37 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "src/core/Release/core.h"

int	gc_failed(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->last_error)
		return (1);
	return (0);
}

const char	*gc_get_last_error(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	return (allocator->last_error);
}

const char	**gc_get_errors(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	return ((const char **)(allocator->errors));
}
