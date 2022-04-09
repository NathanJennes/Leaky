/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:58:07 by njennes           #+#    #+#             */
/*   Updated: 2022/04/08 19:11:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

t_gc	*gc(int mode, void *param)
{
	static t_gc	allocator = {0};

	if (!allocator.pointers)
		gc_init(&allocator, NULL, NULL);
	if (mode == GC_SET_CALLBACK)
		allocator.callback = param;
	if (mode == GC_SET_CALLBACK_PARAM)
		allocator.param = param;
	if (mode == GC_GET)
		return (&allocator);
	return (NULL);
}
