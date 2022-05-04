/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_utils2d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 14:54:10 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 14:54:17 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cored.h"
#include "leaky.h"

int	gc_has_global_parent(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->current_parent == -1)
		return (LK_FALSE);
	return (LK_TRUE);
}
