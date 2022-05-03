/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_attach.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:21:49 by njennes           #+#    #+#             */
/*   Updated: 2022/05/03 15:33:38 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"
#include "leaky.h"

int	gc_attach(void *ptr, void *parent)
{
	t_ptr	*internal_ptr;
	t_ptr	*internal_parent;

	internal_ptr = gc_get_internal_ptr(ptr);
	internal_parent = gc_get_internal_ptr(parent);
	if (!internal_parent)
		return (LK_FAILURE);
	if (!internal_ptr)
		return (LK_FAILURE);
	gc_add_child(internal_parent, internal_ptr);
	return (LK_SUCCESS);
}

int	gc_detach(void *ptr, void *parent)
{
	t_ptr	*internal_ptr;
	t_ptr	*internal_parent;

	internal_ptr = gc_get_internal_ptr(ptr);
	internal_parent = gc_get_internal_ptr(parent);
	if (!internal_parent)
		return (LK_FAILURE);
	if (!internal_ptr)
		return (LK_FAILURE);
	gc_remove_child(internal_parent, internal_ptr);
	return (LK_SUCCESS);
}
