/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error_interfaced.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:43:34 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:29:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "src/core/debug/cored.h"
#include "leaky.h"

int	gc_failed(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->last_error)
		return (LK_TRUE);
	return (LK_FALSE);
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
