/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_attachd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 13:21:49 by njennes           #+#    #+#             */
/*   Updated: 2022/05/04 18:31:47 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/core/debug/cored.h"
#include "leaky.h"

int	gc_attach(void *ptr, void *parent)
{
	int64_t	internal_ptr;
	int64_t	internal_parent;

	internal_ptr = gc_get_internal_ptr(ptr);
	internal_parent = gc_get_internal_ptr(parent);
	if (!gc_is_valid_ptr_index(internal_ptr))
		return (gc_add_error(gc_error_attach_wrong_parent()));
	if (!gc_is_valid_ptr_index(internal_parent))
		return (gc_add_error(gc_error_attach_wrong_pointer()));
	gc_add_child(internal_parent, internal_ptr);
	gc_add_parent(internal_ptr, internal_parent);
	return (LK_SUCCESS);
}

//TODO: check this
int	gc_detach(void *ptr, void *parent)
{
	int64_t	internal_ptr;
	int64_t	internal_parent;

	internal_ptr = gc_get_internal_ptr(ptr);
	internal_parent = gc_get_internal_ptr(parent);
	if (!gc_is_valid_ptr_index(internal_parent))
		return (gc_add_error(gc_error_detach_not_parent()));
	if (!gc_is_valid_ptr_index(internal_ptr))
		return (gc_add_error(gc_error_detach_wrong_pointer()));
	gc_remove_child(internal_parent, internal_ptr);
	gc_remove_parent(internal_ptr, internal_parent);
	return (LK_SUCCESS);
}
