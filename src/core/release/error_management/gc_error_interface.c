/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error_interface.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:43:34 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 15:45:34 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "src/core/Release/core.h"
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
