/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_destroy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:33:45 by njennes           #+#    #+#             */
/*   Updated: 2022/04/11 14:33:55 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

void	gc_destroy(void **ptr)
{
	t_gc	*allocator;

	allocator = gc(GC_GET, NULL);
	if (!ptr)
		return ;
	gc_free(*ptr);
	*ptr = NULL;
}
