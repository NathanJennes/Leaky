/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 18:58:07 by njennes           #+#    #+#             */
/*   Updated: 2022/04/12 19:09:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

t_gc	*gc_get(void)
{
	static t_gc	allocator = {0};

	if (!allocator.pointers)
		gc_init(&allocator, NULL, NULL);
	return (&allocator);
}
