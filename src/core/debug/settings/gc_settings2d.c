/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_settings2d.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 16:26:03 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 12:29:53 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"
#include "leaky.h"

int	can_change_settings(void)
{
	t_gc	*allocator;

	allocator = gc_get();
	if (allocator->ptrs_count)
	{
		gc_add_error(gc_error_settings_after_allocation());
		return (LK_FALSE);
	}
	return (LK_TRUE);
}
