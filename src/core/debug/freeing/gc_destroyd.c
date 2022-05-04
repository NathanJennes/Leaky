/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_destroyd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:33:45 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:29:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"
#include "leaky.h"

void	gc_destroy(void **ptr)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (!ptr)
		return ;
	gc_free(*ptr);
	*ptr = NULL;
}
