/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_settings2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:26:03 by njennes           #+#    #+#             */
/*   Updated: 2022/04/13 16:27:41 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/release/core.h"
#include "leaky.h"

int	can_change_settings(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->ptrs_count)
		return (LK_FALSE);
	return (LK_TRUE);
}
